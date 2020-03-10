#ifndef _SERVER_H
#define _SERVER_H

#include <string>
#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

class Server {
  private:
    int port;

  public:
    Server(int port);
    void start();

};

#endif
