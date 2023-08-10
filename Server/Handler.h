//
// Created by aniki on 8/10/23.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H
#include "Server.h"

class Handler: public Server {
public:
    explicit Handler(short port);
    void run();
private:
    int nbytes;
    int msg_size, size;
    char const work[11] = {"  running"};
    char *pointerbuf;
    char *msg;
};


#endif //SERVER_HANDLER_H
