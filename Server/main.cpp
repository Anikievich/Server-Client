
#include "Handler.h"
#define PORT    9090

int main(int argc, char* argv[]) {
    Handler server(PORT);
    server.run();
}
