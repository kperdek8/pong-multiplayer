#include <iostream>
#include "GameController.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    GameController controller;
    if (auto optConnection = controller.attach()) {
        if (auto connection = optConnection->lock()) {
            connection->sendAction(Action::MOVE_UP);
            connection->sendAction(Action::MOVE_DOWN);
            connection->sendAction(Action::PAUSE);
        } else {
            std::cerr << "Failed to lock connection" << std::endl;
        }
    } else {
        std::cerr << "Failed to attach connection" << std::endl;
    }
    return 0;
}
