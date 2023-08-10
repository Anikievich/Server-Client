//
// Created by aniki on 8/10/23.
//

#include "Server.h"

Server::Server(short port): socket_( PF_INET, SOCK_STREAM, 0) {
    addr_this.sin_family = PF_INET;
    addr_this.sin_addr.s_addr = INADDR_ANY;
    addr_this.sin_port = htons(port);

    err = bind(socket_.getSock(), (struct sockaddr*)&addr_this, sizeof(addr_this));
    if(err<0){
        perror("Server: cannot connect socket");
        exit(EXIT_FAILURE);
    }
    listen(socket_.getSock(),1);
    size =sizeof(addr_from);
    std::cout<<size<<std::endl;
    std::cout<<socket_.getSock()<<std::endl;
    newsock = accept(socket_.getSock(), (struct sockaddr*)&addr_from,  &size);
    std::cout<<newsock<<std::endl;
    if(newsock<0){
        perror("Server: cannot connect newsocket");
        exit(EXIT_FAILURE);
    }
}

void Server::closeScock() {
    close(socket_.getSock());
}


