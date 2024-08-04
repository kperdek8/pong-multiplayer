//
// Created by kperdek8 on 01.08.2024.
//

#ifndef CONNECTIONTYPE_H
#define CONNECTIONTYPE_H

enum class ConnectionType {
  LOCAL,  // Two local players
  CLIENT, // Remote host, local player
  HOST,   // Local host, remote player
  SERVER  // Two remote players
};

#endif //CONNECTIONTYPE_H
