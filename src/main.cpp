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

using namespace std;

const string line_break = "\r\n";

sockaddr_in address;

int initializeServer(uint16_t);
string parseRequest(string);
void sendResponse(string, int);

vector<string> splitString(const string &, const string &);

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

        // spliting request into major parts; method, headers & content
        vector<string> request = splitString(string(requestBuffer), line_break);

        vector<string> method = splitString(request[0], " "); // http method line
        // constructing header map
        map<string, string> headers;
        int index = distance(request.begin(), find(request.begin(), request.end(), "\n"));

        for (int i = 1; i < index; i++)
        {
            vector<string> header = splitString(request[i], ": ");
            // assign key-value pairs corresponding to header key-values
            headers[header[0]] = header[1];
        }

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

vector<string> splitString(const string &input, const string &delimiter)
{
    vector<string> tokens;

    size_t pos = 0, start = 0;

    while ((pos = input.find(delimiter, start)) != string::npos)
    {
        if (pos > start)
        {
            tokens.push_back(input.substr(start, pos - start));
        }
        start = pos + 1;
    }

    if (start < input.length())
    {
        tokens.push_back(input.substr(start));
    }
    return tokens;
}