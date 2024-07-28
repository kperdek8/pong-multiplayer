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

class NetworkServer {
public:
  explicit NetworkServer(Uint16 port);
  ~NetworkServer();
  void Listen(std::vector<std::shared_ptr<Connection>>& connections);

private:
  void HandleAccept(SDLNet_StreamSocket* client, std::vector<std::shared_ptr<Connection>>& connections);
  static void SendData(SDLNet_StreamSocket* client, const Data& data);
  static void RecvData(SDLNet_StreamSocket* client);
  Uint16 port_;
  SDLNet_Server* server_;
  std::vector<SDLNet_StreamSocket*> sockets_;
  std::vector<std::thread> threads_;
  std::atomic<bool> running_{true};
};


#endif //NETWORKSERVER_H
