#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include <string>
#include <variant>

#include "file.h"

using namespace std;

class Server
{
public:
    void initialize();
    void start();
    void stop();

private:
    int serverSocket;
    unordered_map<string, string> configs;

    void loadConfig();
    File getStaticFile(const string &path);
};

#endif