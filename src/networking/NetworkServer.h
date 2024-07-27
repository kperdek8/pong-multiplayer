//
// Created by kperdek8 on 21.07.2024.
//

#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include "Connection.h"
#include <asio.hpp>

using namespace asio::ip;

class NetworkServer {
public:
  NetworkServer(asio::io_context &io_context, short port)
    : io_context_(io_context),
      acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    StartAccept();
  };

private:
  void StartAccept();
  void HandleAccept(tcp::socket& socket, const std::error_code& error);
  static void SendData(tcp::socket& socket, const Data& data) ;
  static void RecvData(tcp::socket& socket);
  asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  std::vector<std::shared_ptr<Connection>> connections_;
};


#endif //NETWORKSERVER_H
