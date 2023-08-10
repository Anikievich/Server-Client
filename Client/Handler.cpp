//
// Created by aniki on 8/10/23.
//

#include "Handler.h"
#include <string>
#include <iostream>
#include <cstring>


Handler::Handler(short &host_port, short &this_port, const std::string& IP):
                    Client( host_port,  this_port, IP) {

}
void Handler::run() {

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
    //char* pointerbuf =(char*) buf1;

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
    closeScock();
}