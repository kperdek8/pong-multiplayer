//
// Created by kperdek8 on 01.08.2024.
//

#include "NetworkManager.h"

#include <algorithm>

std::size_t NetworkManager::getConnectionCount() {
  const auto connections = std::ranges::count_if(connections_, [](const auto &conn) { return conn != nullptr; });
  return connections;
}

void NetworkManager::attach(std::shared_ptr<Connection> &connection) {
  const auto it = std::ranges::find_if(connections_, [](const auto &conn) { return conn == nullptr; });
  *it = connection;
}

int NetworkManager::isConnectionAvailable() {
  // If no connection slot is available returns -1, otherwise returns id.
  const auto it = std::ranges::find_if(connections_, [](const auto &conn) { return conn == nullptr; });
  return it != connections_.end()
           ? static_cast<int>(std::distance(connections_.begin(), it))
           : -1;
}
