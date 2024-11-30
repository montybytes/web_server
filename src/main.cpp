#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

#include "request.h"

using namespace std;

sockaddr_in address;

int initializeServer(uint16_t);
void sendResponse(string, int);

int main()
{
    // initialize server
    int socket = initializeServer(8080);

    // infinite loop to listen for client connection and messages
    while (1)
    {
        // listen to incoming connections
        listen(socket, 5);

        int clientSocket = accept(socket, nullptr, nullptr);
        // TODO: check for appropriate size and throw error if request is over size
        char requestBuffer[1024] = {0};

        // receive request from client
        recv(clientSocket, requestBuffer, sizeof(requestBuffer), 0);

        Request clientRequest;

        clientRequest.parseRequest(requestBuffer);

        // TODO: get file requested

        // fin.open(fileName);

        // check if file exists

        // determine mime type of file

        // open and read from file

        // TODO: construct response
        // -status
        // -headers
        // -body

        // HTML content to send
        string htmlContent =
            "<html>"
            "<head><title>Welcome</title></head>"
            "<body><h1>Hello, World!</h1></body>"
            "</html>";

        // Construct the HTTP response
        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            to_string(htmlContent.size()) + "\r\n"
                                            "\r\n" +
            htmlContent;

        // send response
        sendResponse(response, clientSocket);
    }

    // close server when process terminates
    close(socket);

    return 0;
}

int initializeServer(uint16_t port)
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));

    return serverSocket;
}

void sendResponse(string response, int clientSocket)
{
    ssize_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
    if (bytesSent < 0)
    {
        throw "Error sending response to client";
    }
}
