//
// Created by kperdek8 on 21.07.2024.
//

#include "NetworkServer.h"

#include <iostream>

NetworkServer::NetworkServer(Uint16 port, const std::function<Data()>& fetchFunction) : port_(port), fetchData_
(fetchFunction) {
  if (SDLNet_Init() < 0) {
    std::cerr << "SDLNet_Init error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  server_ = SDLNet_CreateServer(nullptr, port_);
  if (!server_) {
    std::cerr << "SDLNet_CreateServer error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Server started on port " << port_ << std::endl;
}

NetworkServer::~NetworkServer() {
  stop();
}

std::shared_ptr<Connection> NetworkServer::acceptNew() {
  while (running_.load()) {
    std::cout<<"Waiting for new connection"<<std::endl;
    SDLNet_StreamSocket *client;
    SDLNet_AcceptClient(server_, &client);
    if (client) {
      std::shared_ptr<Connection> connection = Connection::create([this, &client](const Data &data) {
                                    sendData(client, data);
                                  },
                                  [this, &client]() {
                                    recvData(client);
                                  });
      std::thread client_thread(&NetworkServer::handleConnection, this, client);
      threads_.push_back(std::move(client_thread));
      return connection;
    }
    SDL_Delay(1000); // Small delay to avoid busy waiting
  }
  return nullptr;
}

void NetworkServer::handleConnection(SDLNet_StreamSocket *client) {
  sockets_.push_back(client);
  while (running_.load()) {
    SDL_Delay(1000); // For testing, cap by tickrate later
    recvData(client);
    sendData(client, fetchData_());
  }
}

void NetworkServer::sendData(SDLNet_StreamSocket *client, const Data &data) {
  const std::string message = data.read();
  const int len = static_cast<int>(message.size());
  if (SDLNet_WriteToStreamSocket(client, message.c_str(), len)) {
    std::cerr << "Error while writing to socket: " << SDL_GetError() << std::endl;
    //TODO: Socket error handling
  } else {
    std::cout << "Sent " << message << std::endl;
  }
}

void NetworkServer::recvData(SDLNet_StreamSocket *client) {
  constexpr int PACKET_SIZE = 64;
  char buffer[PACKET_SIZE];
  const int len = SDLNet_ReadFromStreamSocket(client, buffer, PACKET_SIZE);
  if (len < 0) {
    std::cerr << "Error while reading from socket: " << SDL_GetError << "\n";
    //TODO: Socket error handling
  } else if (len > 0) {
    buffer[len] = '\0';
    std::cout << "Received: " << buffer << std::endl;
  }
}

void NetworkServer::stop() {
  running_.store(false);
  for (auto &thread: threads_) {
    if (thread.joinable()) {
      thread.join();
    }
  }
  for (const auto socket: sockets_) {
    SDLNet_DestroyStreamSocket(socket);
  }
  // For some weird reason trying to correctly destroy server causes SegFault
  //SDLNet_DestroyServer(server_);
  SDLNet_Quit();
}

