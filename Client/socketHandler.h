//
// Created by aniki on 8/10/23.
//

#ifndef CLIENT_SOCKETHANDLER_H
#define CLIENT_SOCKETHANDLER_H
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

class socketHandler {
public:
     explicit socketHandler(short family, uint32_t s_addr, short protocol);
     int getSock();
private:
     int sock;
};



#endif //CLIENT_SOCKETHANDLER_H
