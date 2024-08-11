//
// Created by kperdek8 on 21.07.2024.
//

#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <SDL3_net/SDL_net.h>
#include <atomic>
#include <thread>
#include "Connection.h"

// TODO: Add a way to specify callback function for received data

constexpr uint8_t TICKRATE = 120;

class NetworkServer {
public:
  explicit NetworkServer(Uint16 port, const std::function<Data()>& fetchFunction);

  ~NetworkServer();

  std::shared_ptr<Connection> acceptNew();

private:
  void handleConnection(SDLNet_StreamSocket *client);

  std::function<Data()> fetchData_;

  static void sendData(SDLNet_StreamSocket *client, const Data &data);

  static void recvData(SDLNet_StreamSocket *client);

  std::vector<SDLNet_StreamSocket *> sockets_;
  std::vector<std::thread> threads_;
  SDLNet_Server *server_;
  Uint16 port_;
  uint8_t tickrate_{TICKRATE};
  std::atomic<bool> running_{true};
  bool acceptingNew_{true};
};


#endif //NETWORKSERVER_H
