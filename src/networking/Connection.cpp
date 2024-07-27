//
// Created by kperdek8 on 30.06.2024.
//

#include "Connection.h"
#include <format>
#include <iostream>

Connection::Connection(const std::function<void(Data)> &sendFunc,
                       const std::function<void()> &recvFunc)
  : sendFunc_(sendFunc), recvFunc_(recvFunc) {
  std::cout << std::format("Connection created") << std::endl;
}

Connection::~Connection() {
  std::cout << "Connection object destroyed" << std::endl;
}

std::shared_ptr<Connection> Connection::create(const std::function<void(Data)> &sendFunc,
                                               const std::function<void()> &recvFunc) {
  return std::shared_ptr<Connection>(new Connection(sendFunc,recvFunc));
}

void Connection::send(const Data data) const {
  sendFunc_(data);
}

void Connection::recv() const {
  recvFunc_();
}

