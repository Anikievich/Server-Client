//
// Created by aniki on 8/10/23.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
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

class Client {
public:
    explicit Client(short const &host_port, short const &this_port, const std::string& IP);
    void closeScock();
private:
    int err;
    std::string msg;
    struct sockaddr_in addr_to{};
    struct sockaddr_in addr_from{};
    struct sockaddr_in addr_this{};
    struct hostent *hostinfo;
    socketHandler socket_;
protected:
    int sock;
};


#endif //CLIENT_CLIENT_H
