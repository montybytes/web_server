#ifndef SERVER_H
#define SERVER_H

using namespace std;

class Server
{
public:
    void initialize(const int &port);
    void start();
    void stop();

private:
    int serverSocket;
};

#endif