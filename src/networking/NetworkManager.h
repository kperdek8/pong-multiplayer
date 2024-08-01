//
// Created by kperdek8 on 01.08.2024.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <array>
#include <memory>

#include "Connection.h"
#include "ConnectionType.h"

class NetworkManager {
public:
  explicit NetworkManager(ConnectionType type) {};

  int isConnectionAvailable();

  std::size_t getConnectionCount();

  void attach(std::shared_ptr<Connection> &connection);

  void start();

private:
  std::array<std::shared_ptr<Connection>, MAX_PLAYERS> connections_{};
};


#endif //NETWORKMANAGER_H
