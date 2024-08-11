//
// Created by kperdek8 on 01.08.2024.
//

#include "NetworkManager.h"

#include <algorithm>
#include <cassert>
#include <iostream>

std::size_t NetworkManager::getConnectionCount() {
  const auto connections = std::ranges::count_if(connections_, [](const auto &conn) { return conn != nullptr; });
  return connections;
}

void NetworkManager::attach(const std::shared_ptr<Connection> &connection) {
  const auto it = std::ranges::find_if(connections_, [](const auto &conn) { return conn == nullptr; });
  *it = connection;
}

void NetworkManager::getNewConnection(Uint16 port) {
  if (!server_) {
    server_.emplace(port, stateFetchFunc_);
  }
  assert(getConnectionCount() <= 2 || "Do not ask for new connection when all slots are filled");
  if(getConnectionCount() <= 2) {
    attach(server_->acceptNew());
  }
  else {
    std::cerr<<"WARNING: Getting new connection won't succeed. Either previous socket was incorrectly destroyed or request"
               "should not be made."<<std::endl;
  }
}

void NetworkManager::connect(const char *address, Uint16 port) {
  if (!client_) {
    client_.emplace(address, port);
  }
}

int NetworkManager::isConnectionAvailable() {
  // If no connection slot is available returns -1, otherwise returns id.
  const auto it = std::ranges::find_if(connections_, [](const auto &conn) { return conn == nullptr; });
  return it != connections_.end()
           ? static_cast<int>(std::distance(connections_.begin(), it))
           : -1;
}
