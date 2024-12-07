#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "response.h"
#include "string_utils.h"

void Response::sendStatusHeader(const int &clientSocket)
{
    // concatenate status string and header string
    const string responseHeaders = status + "\r\n" + mapToString(headers) + "\r\n";

    // send final string to client
    send(clientSocket, responseHeaders.c_str(), responseHeaders.size(), 0);
}

void Response::sendText(const string &text, const int &clientSocket)
{
    //  TODO: better error handling with throws
    if (send(clientSocket, text.c_str(), text.size(), 0) == -1)
    {
        cerr << "Client disconnected while sending data" << endl;
        close(clientSocket);
    }
    close(clientSocket);
}

void Response::sendBinary(const vector<char> &binary, const int &clientSocket)
{
    //  TODO: better error handling with throws
    if (send(clientSocket, binary.data(), binary.size(), 0) == -1)
    {
        cerr << "Client disconnected while sending data" << endl;
        close(clientSocket);
    }
    close(clientSocket);
}

void Response::setHeader(const string &key, const string &value)
{
    headers[key] = value;
}