
#include "Client.h"
Client::Client(short const &host_port, short const &this_port, const std::string& IP):
                socket_( PF_INET, SOCK_STREAM, 0) {

    sock = socket_.getSock();
    hostinfo = gethostbyname(IP.c_str());
    if(hostinfo == NULL){
        fprintf(stderr, "Unknown host\n");
        exit(EXIT_FAILURE);
    }

    addr_to.sin_family = hostinfo->h_addrtype;
    addr_to.sin_port = htons(host_port);
    addr_to.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    addr_this.sin_family = AF_INET;
    addr_this.sin_addr.s_addr = INADDR_ANY;
    addr_this.sin_port = htons(this_port);

    err = connect(sock, (struct sockaddr*)&addr_to, sizeof(addr_to));
    if(err<0){
        std::cerr <<"Client: cannot connect socket"<<std::endl;
        exit(EXIT_FAILURE);
    }


}

void Client::closeScock() {
    close(socket_.getSock());
}