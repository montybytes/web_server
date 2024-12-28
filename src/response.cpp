#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

#include "response.h"
#include "string_utils.h"
#include "error.h"

// todo: throw internal error & log for failed string operations
bool isSocketWritable(int socket);

void Response::send(const int &clientSocket, const string &text)
{
    try
    {
        if (!isSocketWritable(clientSocket))
        {
            std::cerr << "Client is no longer writable (disconnected)." << std::endl;
            return;
        }

        // concatenate status string and header string
        const string responseHeaders = status + "\r\n" + mapToString(headers) + "\r\n";

        // send header string to client
        ::send(clientSocket, responseHeaders.c_str(), responseHeaders.size(), 0);
        //  send body text
        ::send(clientSocket, text.c_str(), text.size(), 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    close(clientSocket);
}

void Response::send(const int &clientSocket, const vector<char> &binary)
{
    try
    {
        if (!isSocketWritable(clientSocket))
        {
            std::cerr << "Client is no longer writable (disconnected)." << std::endl;
            return;
        }

        // concatenate status string and header string
        const string responseHeaders = status + "\r\n" + mapToString(headers) + "\r\n";

        // send header string to client
        ::send(clientSocket, responseHeaders.c_str(), responseHeaders.size(), 0);
        //  send binary data
        ::send(clientSocket, binary.data(), binary.size(), 0);

        close(clientSocket);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Response::setHeader(const string &key, const string &value)
{
    headers[key] = value;
}

bool isSocketWritable(int socket)
{
    struct pollfd pfd;
    pfd.fd = socket;
    pfd.events = POLLOUT; // Check if the socket is writable

    int ret = poll(&pfd, 1, 1000); // Timeout of 1000ms (1 second)
    if (ret < 0)
    {
        perror("poll failed");
        return false;
    }
    return (pfd.revents & POLLOUT) != 0;
}