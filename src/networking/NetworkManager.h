//
// Created by kperdek8 on 01.08.2024.
//

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <memory>
#include <optional>

#include "Connection.h"
#include "NetworkClient.h"
#include "NetworkServer.h"

class NetworkManager {
public:
  explicit NetworkManager(const std::function<Data()>& stateFetchFunc) : stateFetchFunc_(stateFetchFunc) {}

  int isConnectionAvailable();

  std::size_t getConnectionCount();

  void attach(const std::shared_ptr<Connection> &connection);

  void getNewConnection(Uint16 port);

  void connect(const char *address, Uint16 port);

private:
  std::array<std::shared_ptr<Connection>, MAX_PLAYERS> connections_{};
  std::function<Data()> stateFetchFunc_;
  std::optional<NetworkClient> client_;
  std::optional<NetworkServer> server_;
};


#endif //NETWORKMANAGER_H
