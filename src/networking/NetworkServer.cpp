//
// Created by kperdek8 on 21.07.2024.
//

#include "NetworkServer.h"

#include <iostream>

NetworkServer::NetworkServer(Uint16 port) : port_(port) {
  if (SDLNet_Init() < 0) {
    std::cerr << "SDLNet_Init error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  server_ = SDLNet_CreateServer(nullptr, port_);
  if (!server_) {
    std::cerr << "SDLNet_CreateServer error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  std::cout << "Server started on port "<< port_ << std::endl;
}

NetworkServer::~NetworkServer() {
  for (auto& thread : threads_) {
    if(thread.joinable()) {
      thread.join();
    }
  }
  for (const auto socket : sockets_) {
    SDLNet_DestroyStreamSocket(socket);
  }
  SDLNet_DestroyServer(server_);
  SDLNet_Quit();
}

void NetworkServer::Listen(std::vector<std::shared_ptr<Connection>>& connections)  {
  while (running_) {
    SDLNet_StreamSocket* client;
    SDLNet_AcceptClient(server_, &client);
    if (client) {
      std::thread client_thread(&NetworkServer::HandleAccept, this, client, std::ref(connections));
      threads_.push_back(std::move(client_thread));
    }
    SDL_Delay(100); // Small delay to avoid busy waiting
  }
}
void NetworkServer::HandleAccept(SDLNet_StreamSocket* client, std::vector<std::shared_ptr<Connection>>& connections) {
  connections.emplace_back(Connection::create(
  [this, &client](const Data& data) {
    SendData(client, data);
  },
  [this, &client]() {
    RecvData(client);
  }));
  sockets_.push_back(client);
  while(running_) {
    RecvData(client);
  }
}

void NetworkServer::SendData(SDLNet_StreamSocket* client, const Data& data) {
  const std::string message = data.read();
  const int len = static_cast<int>(message.size());
  if (SDLNet_WriteToStreamSocket(client, message.c_str(), len)) {
    std::cerr << "Error while writing to socket: " << SDL_GetError() << std::endl;
    //TODO: Socket error handling
  } else {
    std::cout << "Sent " << message << std::endl;
  }
}

void NetworkServer::RecvData(SDLNet_StreamSocket* client) {
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

