//
// Created by kperdek8 on 21.07.2024.
//

#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H
#include "Connection.h"
#include <SDL3_net/SDL_net.h>
#include <atomic>
#include <thread>

class NetworkClient {
public:
  NetworkClient(const char* address, Uint16 port);
  ~NetworkClient();
  std::shared_ptr<Connection> GetConnection();
  void Listen();

private:
  static void SendData(SDLNet_StreamSocket* client, const Data& data);
  static void RecvData(SDLNet_StreamSocket* client);
  SDLNet_StreamSocket* socket_;
  std::shared_ptr<Connection> connection_;
};


#endif //NETWORKCLIENT_H
