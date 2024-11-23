#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
    // initialize server
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));

    // listen to incoming connections
    listen(serverSocket, 5);

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    char buffer[1024] = {0};

    // infinite loop to listen for client connection and messages
    while (1)
    {
        recv(clientSocket, buffer, sizeof(buffer), 0);

        cout << "Client: " << buffer << endl;

        // close server when certain message is received
        if (strcmp(buffer, "exit") == 0)
        {
            close(serverSocket);
            return 0;
        }
    }

    return 0;
}