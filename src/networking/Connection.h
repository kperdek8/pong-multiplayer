//
// Created by kperdek8 on 30.06.2024.
//

#ifndef CONNECTION_H
#define CONNECTION_H

#include "../common/Data.h"
#include <functional>
#include <memory>

//TODO: Check if changing Data into Data& is possible without breaking NetworkClient and NetworkServer

class Connection : public std::enable_shared_from_this<Connection> {
public:
  static std::shared_ptr<Connection> create(const std::function<void(Data)> &sendFunc,
                                            const std::function<void()> &recvFunc);
  ~Connection();
  void send(Data data) const;
  void recv() const;
private:
  explicit Connection(const std::function<void(Data)> &sendFunc,
                      const std::function<void()> &recvFunc);

  std::function<void(Data)> sendFunc_; // sendAction for client, sendGameState for server
  std::function<void()> recvFunc_; // readGameState for client, readAction for server
};

#endif // CONNECTION_H
