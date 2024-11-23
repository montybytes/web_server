#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main()
{
    // initialize client
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr *)&address, sizeof(address));

    // send data to server
    const char *message = "exit";
    send(clientSocket, message, strlen(message), 0);

    // close client socket
    close(clientSocket);

    return 0;
}
