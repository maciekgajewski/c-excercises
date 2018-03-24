#include "client_socket_connection.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string input;

    std::string uri = "ws://localhost:9876";
    if (argc > 1)
        uri = argv[1];
    ClientSocketConnection socket(uri);

    while (std::getline(std::cin, input)) {
        socket.send(input);
    }

    return 0;
}
