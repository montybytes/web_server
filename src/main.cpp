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

#include "file.h"
#include "request.h"
#include "response.h"

using namespace std;

const string publicDir = "./public";

sockaddr_in address;

int initializeServer(uint16_t);
void sendResponse(string, int);

int main()
{
    // initialize server
    int serverSocket = initializeServer(8080);

    // listen to incoming connections
    listen(serverSocket, 5);

    // infinite loop to listen for client connection and messages
    while (1)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        // TODO: check for appropriate size and throw error if request is over size
        char requestBuffer[1024] = {0};

        // receive request from client
        recv(clientSocket, requestBuffer, sizeof(requestBuffer), 0);

        const Request clientRequest = Request::parseRequest(requestBuffer);

        // map url to file system
        const string requestedFilePath = File::mapPathToAbsolute(clientRequest.resource.target.path);

        cout << "File path: " << requestedFilePath << endl;

        // attempt to read file at given path
        if (!File::isFileAvailable(requestedFilePath))
        {
            // throw an exception and return 404
            Response response = Response("HTTP/1.1 404 Not Found");
            // set other necessary headers
            response.sendStatusHeader(clientSocket);
            response.sendText("No file found, sorry", clientSocket);

            continue;
        }

        // file_url -> attempt to check for file -> read file if found ->

        // read file from directory
        // const File requestedFile = File();

        // TODO: construct response
        Response response = Response("HTTP/1.1 200 OK");

        response.setHeader("Content-Type", "text/html");
        // response.setHeader("Content-Length", to_string(fileSize));
        response.sendStatusHeader(clientSocket);
        response.sendText("<html><head><title>Welcome</title></head><body><h1>Hello, World!</body></html>", clientSocket);
    }

    // close server when process terminates
    close(serverSocket);

    return 0;
}

int initializeServer(uint16_t port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&address, sizeof(address));

    return sock;
}
