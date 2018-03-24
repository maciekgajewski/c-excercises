#include "chat_client.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string input;

    std::string uri = "ws://localhost:9876";
    if (argc > 1)
        uri = argv[1];
    ChatClient client(uri);

    std::cout << "Enter your name" << std::endl;
    while (std::getline(std::cin, input)) {
        if (!client.is_registered)
        {
            std::cout << "Enter your name" << std::endl;
            client.set_name(input);
        }
        else
            client.send(input);
    }

    return 0;
}
