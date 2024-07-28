//
// Created by kperdek8 on 21.07.2024.
//

#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <SDL3_net/SDL_net.h>
#include "Connection.h"

class NetworkServer {
public:
  explicit NetworkServer(Uint16 port);
  ~NetworkServer();

private:
  void Listen();
  void HandleAccept(SDLNet_StreamSocket* client);
  static void SendData(SDLNet_StreamSocket* client, const Data& data);
  static void RecvData(SDLNet_StreamSocket* client);
  Uint16 port_;
  SDLNet_Server* server_;
  std::vector<std::shared_ptr<Connection>> connections_;
  std::vector<SDLNet_StreamSocket*> sockets_;
};


#endif //NETWORKSERVER_H
