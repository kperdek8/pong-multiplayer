//
// Created by kperdek8 on 21.07.2024.
//

#include "NetworkServer.h"

#include <iostream>

void NetworkServer::StartAccept()  {
  sockets_.emplace_back(io_context_);
  tcp::socket& socket = sockets_.front();
  acceptor_.async_accept(socket,
      [this, &socket](const std::error_code& error) {
        HandleAccept(socket, error);
      });
}
void NetworkServer::HandleAccept(tcp::socket& socket, const std::error_code& error) {
  if (!error) {
    connections_.emplace_back(Connection::create(
    [this, &socket](const Data& data) {
      SendData(socket, data);
    },
    [this, &socket]() {
      RecvData(socket);
    }
  ));
  }

  // Start accepting the next connection
  connections_.front()->send(std::string("00001111"));
  StartAccept();
}

void NetworkServer::SendData(tcp::socket &socket, const Data &data) {
  socket.async_send(asio::buffer(data.read()),
    [](const std::error_code& error, std::size_t bytes_transferred) {
      if (!error) {
        std::cout << "Successfully sent " << bytes_transferred << " bytes.\n";
      } else {
        std::cerr << "Error during send: " << error.message() << "\n";
      }
  });
}

void NetworkServer::RecvData(tcp::socket &socket) {
  std::string message;
  socket.async_receive(asio::buffer(message), [](const std::error_code& error, std::size_t bytes_transferred) {
      if (!error) {
        std::cout << "Successfully received " << bytes_transferred << " bytes.\n";
      } else {
        std::cerr << "Error during receiving: " << error.message() << "\n";
      }
  });
  std::cout<<"Received: "<<message<<std::endl;
}
