#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "response.h"
#include "string_utils.h"

//  TODO: implement error handling

void Response::send(const int &clientSocket, const string &text)
{
    // concatenate status string and header string
    const string responseHeaders = status + "\r\n" + mapToString(headers) + "\r\n";
    // send header string to client
    ::send(clientSocket, responseHeaders.c_str(), responseHeaders.size(), 0);
    ::send(clientSocket, text.c_str(), text.size(), 0);
    close(clientSocket);
}

void Response::send(const int &clientSocket, const vector<char> &binary)
{
    // concatenate status string and header string
    const string responseHeaders = status + "\r\n" + mapToString(headers) + "\r\n";
    // send header string to client
    ::send(clientSocket, responseHeaders.c_str(), responseHeaders.size(), 0);
    ::send(clientSocket, binary.data(), binary.size(), 0);
    close(clientSocket);
}

void Response::setHeader(const string &key, const string &value)
{
    headers[key] = value;
}