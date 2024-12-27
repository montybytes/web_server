#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>

#include "server.h"
#include "request.h"
#include "response.h"
#include "file.h"
#include "error.h"

// Initialize server & listen to incoming connections
void Server::initialize(const int &port)
{
    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    listen(serverSocket, 5);
}

// Start processing of requests on server
void Server::start()
{
    // infinite loop to handle client connection and messages
    while (1)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        // todo: find appropriate request buffer size
        char requestBuffer[1024] = {0};

        try
        {
            // receive request from client
            recv(clientSocket, requestBuffer, sizeof(requestBuffer), 0);

            const Request clientRequest = Request::parseRequest(requestBuffer);

            // map url to file system
            const string requestedFilePath = File::mapPathToAbsolute(clientRequest.resource.target.path);

            // read file from directory
            const File requestedFile = File::fromPath(requestedFilePath);

            Response response = Response("HTTP/1.1 200 OK");

            response.setHeader("Content-Type", File::getContentType(requestedFile.fileExtension));
            response.setHeader("Content-Length", to_string(requestedFile.fileSize));
            response.send(clientSocket, requestedFile.fileContent);
        }
        catch (const Error &e)
        {
            Response response = Response("HTTP/1.1 " + to_string(static_cast<int>(e.code)) + " " + e.message);

            response.send(clientSocket, e.message);

            cerr << "Custom Error [" << e.code << "]: " << e.what() << "\n";
        }
        catch (const exception &e)
        {
            Response response = Response("HTTP/1.1 " + to_string(static_cast<int>(ErrorCode::E500_INTERNAL_SERVER_ERROR)) + " Internal Server Error");

            response.send(clientSocket, "Internal Server Error");

            cerr << "Generic Error: " << e.what() << "\n";
        }
    }
}

// Stop server gracefully
void Server::stop()
{
    close(serverSocket);
}