#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>

#include "file.h"
#include "request.h"
#include "response.h"

using namespace std;

int serverSocket;

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        cout << "Shutting down..." << endl;
        close(serverSocket);
        exit(0);
    }
}

// TODO: put server logic in a managebale class
int main()
{
    // close port gracefully
    signal(SIGINT, handleSignal);

    // initialize server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));

    // listen to incoming connections
    listen(serverSocket, 5);

    // infinite loop to handle client connection and messages
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

        // TODO: move to file.cpp
        // attempt to read file at given path
        if (!File::isFileAvailable(requestedFilePath))
        {
            // throw an exception and return 404
            Response response = Response("HTTP/1.1 404 Not Found");
            // set other necessary headers
            // response.setHeader("Content-Length", "69");
            response.send(clientSocket, "No file found, sorry");

            continue;
        }

        // read file from directory
        const File requestedFile = File::fromPath(requestedFilePath);

        Response response = Response("HTTP/1.1 200 OK");

        response.setHeader("Content-Type", File::getContentType(requestedFile.fileExtension));
        response.setHeader("Content-Length", to_string(requestedFile.fileSize));
        response.send(clientSocket, requestedFile.fileContent);
    }

    return 0;
}