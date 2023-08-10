//
// Created by aniki on 8/10/23.
//

#include "socketHandler.h"

socketHandler::socketHandler(short family, uint32_t s_addr, short protocol) {

    sock = socket(family, s_addr, protocol);
    if(sock<0) {
        perror("Server: socket was not created");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

}

int socketHandler::getSock() {
    return sock;
}
