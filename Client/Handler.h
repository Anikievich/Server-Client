//
// Created by aniki on 8/10/23.
//

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H


#include "Client.h"

class Handler: public Client {
public:
    explicit Handler(short &host_port, short &this_port, const std::string& IP);
    void run();
private:
    int nbytes;
    int msg_size, size;
    char const work[11] = {"  running"};
    char *pointerbuf;
    std::string msg;
    char buf[512];
};


#endif //CLIENT_HANDLER_H
