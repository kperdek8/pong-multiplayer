//
// Created by kperdek8 on 21.07.2024.
//

#include "NetworkClient.h"

#include <iostream>

NetworkClient::NetworkClient(const char* address, Uint16 port) {
  if (SDLNet_Init() < 0) {
    std::cerr << "SDLNet_Init error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  SDLNet_Address* host = SDLNet_ResolveHostname(address);
  SDLNet_WaitUntilResolved(host, -1);
  if (SDLNet_GetAddressStatus(host) < 1) {
    std::cerr << "SDLNet_ResolveHostname error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  socket_ = SDLNet_CreateClient(host, port);
  SDLNet_WaitUntilConnected(socket_, -1);
  if (SDLNet_GetConnectionStatus(socket_) < 1) {
    std::cerr << "SDLNet_CreateClient error: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  connection_ = Connection::create(
  [this](const Data& data) {
    SendData(socket_, data);
  },
  [this]() {
    RecvData(socket_);
  });
  std::cout << "Connected to "<< address << " " << port << std::endl;
}

NetworkClient::~NetworkClient() {
  SDLNet_DestroyStreamSocket(socket_);
  SDLNet_Quit();
}

std::shared_ptr<Connection> NetworkClient::GetConnection() {
  return connection_;
}

void NetworkClient::Listen() {
  while(true) {
    RecvData(socket_);
  }
}

void NetworkClient::SendData(SDLNet_StreamSocket* client, const Data& data) {
  const std::string message = data.read();
  const int len = static_cast<int>(message.size());
  if (SDLNet_WriteToStreamSocket(client, message.c_str(), len)) {
    std::cerr << "Error while writing to socket: " << SDL_GetError() << std::endl;
    //TODO: Socket error handling
  } else {
    std::cout << "Sent " << message << std::endl;
  }
}

void NetworkClient::RecvData(SDLNet_StreamSocket* client) {
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