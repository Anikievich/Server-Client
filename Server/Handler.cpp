//
// Created by aniki on 8/10/23.
//

#include "Handler.h"

Handler::Handler(short port) : Server(port) {

}

void Handler::run() {

    int newsock = accept(socket_.getSock(), (struct sockaddr*)&addr_from,  &size);
    std::cout<<newsock<<std::endl;
    if(newsock<0){
        perror("Server: cannot connect newsocket");
        exit(EXIT_FAILURE);
    }
    nbytes = recv(newsock, (char*)&msg_size, sizeof(int), 0);
    if (nbytes < 0) {
        fprintf(stderr, "cannot send data");
        std::cerr << "Client"<<std::endl;
        exit(EXIT_FAILURE);
        //continue;
    }
    msg = new char[msg_size+1];
    msg[msg_size]= '\0';

    nbytes = recv(newsock, msg, msg_size, 0);
    std::cout<<msg<<std::endl;
    if (nbytes < 0) {
        fprintf(stderr, "cannot recv data");
        std::cerr << "Server"<<std::endl;
        exit(EXIT_FAILURE);
    }

    pointerbuf =(char*) work;
    size_t to_read = std::strlen(work);

    std::cout<<work<<std::endl;
    std::cout<<strcmp(msg,"get_status")<<std::endl;

    if(strcmp(msg,"get_status")==0){
        nbytes = send(newsock, (char*)&to_read, sizeof(int), 0);
        if (nbytes < 0) {
            fprintf(stderr, "cannot send size");
            std::cerr << "Server"<<std::endl;
            exit(EXIT_FAILURE);
        }
        while (to_read>0){
            std::cout<<"do"<<std::endl;
            nbytes = send(newsock, work, to_read, 0);
            if (nbytes < 0) {
                fprintf(stderr, "cannot send data");
                std::cerr << "Client"<<std::endl;
                continue;
            }
            std::cout<<"Sending response..."<<std::endl;
            pointerbuf += nbytes;
            to_read -= nbytes;
        }
    }else{
        std::string str = "Undefined command";
        size = str.size();
        nbytes = send(newsock, (char*)&size, sizeof(int), 0);
        if (nbytes < 0) {
            fprintf(stderr, "cannot send size");
            std::cerr << "Server"<<std::endl;
            exit(EXIT_FAILURE);
        }
        nbytes = send(newsock, str.c_str(), str.size(), 0);
        if (nbytes < 0) {
            fprintf(stderr, "cannot send data");
            std::cerr << "Server"<<std::endl;
            exit(EXIT_FAILURE);
        }
    };
    std::cout<<"Sending response..."<<std::endl;
    delete[]msg;
    //close(newsock);
    //closeScock();
}
