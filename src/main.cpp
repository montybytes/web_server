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

    // infinite loop to listen for client connection and messages
    while (1)
    {
        // listen to incoming connections
        listen(serverSocket, 5);

        int clientSocket = accept(serverSocket, nullptr, nullptr);
        char buffer[1024] = {0};

        recv(clientSocket, buffer, sizeof(buffer), 0);

        // cout << "Client: " << buffer << endl;

        // HTML content to send
        std::string htmlContent =
            "<html>"
            "<head><title>Welcome</title></head>"
            "<body><h1>Hello, World!</h1></body>"
            "</html>";

        // Construct the HTTP response
        std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " +
            std::to_string(htmlContent.size()) + "\r\n"
                                                 "\r\n" +
            htmlContent;

        // Send the response
        ssize_t bytesSent = send(clientSocket, response.c_str(), response.size(), 0);
        if (bytesSent == -1)
        {
            std::cerr << "Error sending response to client\n";
        }
        else
        {
            std::cout << "Response sent successfully\n";
        }

        // if (strcmp(buffer, "exit") == 0)
        // {
        //     return 0;
        // }
    }

    // close server when process terminates
    close(serverSocket);

    return 0;
}