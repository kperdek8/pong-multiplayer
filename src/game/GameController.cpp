//
// Created by kperdek8 on 25.06.2024.
//

#include "GameController.h"

#include <algorithm>
#include <format>
#include <iostream>

std::optional<std::weak_ptr<Connection> > GameController::attachLocally() {
  const int connectionId = networkManager_.isConnectionAvailable();

  // Reject connection if all slots are taken
  if (connectionId < 0) {
    std::cout << "New connection rejected" << std::endl;
    return std::nullopt;
  }

  // Prepare callback function for new connection to send data
  auto sendCallback = [this, connectionId](const Data &data) {
    auto [action, pressed] = data.readAction();
    this->processAction(action, pressed, connectionId);
  };

  // Prepare callback function for new connection to receive date (locally it's gamestate reference)
  auto recvCallback = [this]() {
    return gameState_;
  };

  auto it = Connection::create(sendCallback, recvCallback);
  networkManager_.attach(it);

  return std::weak_ptr(it);
}

/* GameController receives action, alongside it's state (some actions my produce specific result on
 deactivation) and id of connection which sent the request to manipulate correct object.

 Releasing movement keys should make paddle stop, but player may send MOVE_UP action before deactivating
 MOVE_DOWN (or vice versa) by pressing both keys at once. To fix that, deactivating MOVE_UP or MOVE_DOWN
 sets paddle's velocity to zero ONLY IF CURRENT velocity matches action's direction. This way deactivating
 actions whose effects were already overwritten is ignored.  */
void GameController::processAction(const Action action, const bool isActivated, int id) {
  std::cout << std::format("Connection [{}]: ", id);
  std::cout << (isActivated ? "Activate " : "Deactive ");
  constexpr auto speed = Paddle::MOVESPEED;
  switch (action) {
    case Action::NONE:
      std::cout << "No Actions!" << std::endl;
      break;
    case Action::MOVE_UP:
      std::cout << "Move up!" << std::endl;
      if (isActivated)
        gameState_.players[id].paddle.setVelocity(Vector2D{0, -speed});
      else if (gameState_.players[id].paddle.getVelY() < 0)
        gameState_.players[id].paddle.setVelocity(Vector2D{0, 0});
      break;
    case Action::MOVE_DOWN:
      std::cout << "Move down!" << std::endl;
      if (isActivated)
        gameState_.players[id].paddle.setVelocity(Vector2D{0, speed});
      else if (gameState_.players[id].paddle.getVelY() > 0)
        gameState_.players[id].paddle.setVelocity(Vector2D{0, 0});
      break;
    case Action::PAUSE:
      std::cout << "Pause" << std::endl;
      break;
    case Action::START:
      std::cout << "Start" << std::endl;
      if (gameState_.ball.isStopped() && gameState_.lastGoal == static_cast<Side>(id))
        gameState_.ball.start(gameState_.lastGoal);
      break;
    case Action::QUIT:
      std::cout << "Quitting" << std::endl;
      break;
  }
}

GameState &GameController::getGameState() {
  return gameState_;
}

void GameController::handleBoundsCollision(GameObject &object,
                                           Vector2D &movement) {
  if (const auto direction = object.boundsCollision(movement)) {
    const auto distance = object.distanceToBounds(direction);
    if (direction & Direction::BOTTOM)
      movement.y = std::min(movement.y, distance.y);
    else if (direction & Direction::TOP)
      movement.y = std::max(movement.y, distance.y);
    if (direction & Direction::RIGHT)
      movement.x = std::min(movement.x, distance.x);
    else if (direction & Direction::LEFT)
      movement.x = std::max(movement.x, distance.x);

    // Actions to do when object is of type 'Ball'
    if (auto *ball = dynamic_cast<Ball *>(&object)) {
      if (direction & (Direction::LEFT | Direction::RIGHT)) {
        // Goal! Reset the ball and add point
        std::cout << "Goal!." << std::endl;
        ball->resetPosition();
        if (direction & Direction::LEFT) {
          gameState_.players[1].points += 1;
          gameState_.lastGoal = Side::RIGHT;
        } else {
          gameState_.players[0].points += 1;
          gameState_.lastGoal = Side::LEFT;
        }
      } else {
        // Not a goal, bounce the ball
        std::cout << "Ball collided with bounds and bounced." << std::endl;
        ball->bounce(direction);
      }
    }
  }
}

void GameController::handleObjectCollision(GameObject &object,
                                           Vector2D &movement,
                                           const GameObject &otherObject) {
  if (const auto direction = object.objectCollision(otherObject, movement)) {
    const auto distance = object.distanceToObject(otherObject);
    if (direction & Direction::BOTTOM)
      movement.y = std::min(movement.y, distance.y);
    else if (direction & Direction::TOP)
      movement.y = std::max(movement.y, distance.y);
    if (direction & Direction::RIGHT)
      movement.x = std::min(movement.x, distance.x);
    else if (direction & Direction::LEFT)
      movement.x = std::max(movement.x, distance.x);

    // Actions to do when object is of type 'Ball'
    if (auto *ball = dynamic_cast<Ball *>(&object)) {
      std::cout << "Ball collided with paddle and bounced." << std::endl;
      ball->bounce(direction);
    }
  }
}

void GameController::update() {
  // Delta time calculation
  const auto currentFrame = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<float> deltaTime = currentFrame - lastFrame_;
  const float dt = deltaTime.count();
  lastFrame_ = currentFrame;

  // Paddles
  for (auto &player: gameState_.players) {
    auto movement = player.paddle.getVel() * dt;
    handleBoundsCollision(player.paddle, movement);
    player.paddle.move(movement);
  }

  // Ball
  auto movement = gameState_.ball.getVel() * dt;

  for (auto &player: gameState_.players) {
    handleObjectCollision(gameState_.ball, movement, player.paddle);
  }

  if (const auto direction = gameState_.ball.boundsCollision(movement)) {
    handleBoundsCollision(gameState_.ball, movement);
  }
  gameState_.ball.move(movement);

  // Other stuff
  //gameState_.debugPrint();
}

void GameController::start() {
  gameStarted_ = true;
  lastFrame_ = std::chrono::high_resolution_clock::now();
}
