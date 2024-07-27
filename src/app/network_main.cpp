//
// Created by kperdek8 on 27.07.2024.
//

#include <iostream>

#include "NetworkServer.h"

int main() {
  try
  {
    asio::io_context io_context;
    NetworkServer server(io_context, 4444);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}