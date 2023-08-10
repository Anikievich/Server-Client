//
// Created by aniki on 8/10/23.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include "socketHandler.h"


class Server {
public:
    explicit Server(short port);
     void closeScock();
private:
    int i, err;
    unsigned int size;
    struct sockaddr_in addr_from;
    struct sockaddr_in addr_this;
    socketHandler socket_;
protected:
    int newsock;
};


#endif //SERVER_SERVER_H
