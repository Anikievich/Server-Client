#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <cstring>
#include <string>

#define PORT_THIS    5556
#define PORT_TO      9090
#define BUFLEN       512
char buf[BUFLEN];

void PrintAddr(const struct sockaddr_in &addr, const char *text);

int main(int argc, char* argv[]) {
    int sock;
    int nbytes, i, err;
    unsigned int size;
    std::string msg;
    struct sockaddr_in addr_to;
    struct sockaddr_in addr_from;
    struct sockaddr_in addr_this;
    struct hostent *hostinfo;

    hostinfo = gethostbyname("127.0.0.1");
    if(hostinfo == NULL){
        fprintf(stderr, "Unknown host\n");
        exit(EXIT_FAILURE);
    }

    addr_to.sin_family = hostinfo->h_addrtype;
    addr_to.sin_port = htons(PORT_TO);
    addr_to.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    addr_this.sin_family = AF_INET;
    addr_this.sin_addr.s_addr = INADDR_ANY;
    addr_this.sin_port = htons(PORT_THIS);

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock<0) {
        std::cerr <<"Client: socket was not created";
                  exit(EXIT_FAILURE);
    }
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    err = connect(sock, (struct sockaddr*)&addr_to, sizeof(addr_to));
    if(err<0){

        std::cerr <<"Client: cannot connect socket"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::getline(std::cin, msg);
    int msg_size = msg.size();

    nbytes = send(sock, (char*)&msg_size, sizeof(int), 0);
    if (nbytes < 0) {
        fprintf(stderr, "cannot recv data");
        std::cerr << "Client" << std::endl;
        exit(EXIT_FAILURE);
    }

    char* it = const_cast<char *>(msg.c_str());
    size_t to_read = std::strlen(buf)+1;
    while (msg_size>0) {
        nbytes = send(sock, it, msg_size, 0);
        if (nbytes < 0) {
            fprintf(stderr, "cannot send data");
            std::cerr << "Client"<<std::endl;
            exit(EXIT_FAILURE);
            //continue;
        }
        std::cout<<"Sending request..."<<std::endl;
        it += nbytes;
        msg_size -= nbytes;
    }
    std::cout<<"Request was sent"<<std::endl;
    std::cout<<"Server response: "<<std::endl;

int size1;
    nbytes = recv(sock, (char*)&size1, sizeof(int), 0);
    if (nbytes < 0) {
        fprintf(stderr, "cannot recv data");
        std::cerr << "Client"<<std::endl;
    }

    char *buf1 = new char[size1+1];
    buf1[size1] = '\0';
    char* pointerbuf =(char*) buf1;

     while (to_read>0){
        nbytes = recv(sock, buf1, size1, 0);
        if (nbytes < 0) {
            fprintf(stderr, "cannot recv data");
            std::cerr << "Client"<<std::endl;
            continue;
        } else if (nbytes == 0){
            break;
        }
        pointerbuf += nbytes;
        to_read -= nbytes;
    }
    std::cout<<buf1<<std::endl;
     delete[] buf1;
    return 0;
}
