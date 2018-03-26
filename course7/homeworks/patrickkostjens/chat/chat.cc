#include "chat_client.h"

#include <string>

int main(int argc, char** argv) {

    std::string uri = "ws://localhost:9876";
    if (argc > 1)
        uri = argv[1];
    ChatClient client(uri);

    client.run();

    return 0;
}
