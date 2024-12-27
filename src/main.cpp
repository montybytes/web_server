#include <csignal>
#include <iostream>

#include "server.h"

using namespace std;

void registerSignalHandlers(Server *server);
void handleSignals(int signal, siginfo_t *info, void *context);

int main()
{
    try
    {
        Server server = Server();

        registerSignalHandlers(&server);

        server.initialize(8080);
        server.start();
    }
    catch (const exception &e)
    {
        cerr << "Terminal Error: " << e.what() << endl;
    }

    return 0;
}

// Setting up signal handlers
void registerSignalHandlers(Server *server)
{
    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handleSignals;

    sigemptyset(&action.sa_mask);

    sigaction(SIGINT, &action, nullptr);
    sigaction(SIGABRT, &action, nullptr);
}

// Handle os signals
void handleSignals(int signal, siginfo_t *info, void *context)
{
    Server *server = reinterpret_cast<Server *>(info->si_value.sival_ptr);

    switch (signal)
    {
    case SIGKILL:
    case SIGTERM:
    case SIGINT:
    case SIGABRT:
        if (server)
        {
            server->stop();
        }

        cout << "Shutting down..." << endl;
        exit(0);
    default:
        cout << "Unhandled signal: " << signal << endl;
    }

    cout << endl;
}