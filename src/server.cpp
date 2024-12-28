#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <csignal>

#include "server.h"
#include "request.h"
#include "response.h"
#include "file.h"
#include "error.h"
#include "string_utils.h"

// Load server's configurations from file
void Server::loadConfig()
{
    ifstream configFile("config.ini");

    if (!configFile.is_open())
    {
        cerr << "Error opening the configuration file!";
        throw;
    }

    string configLine;
    string configSectionName = "";

    while (getline(configFile, configLine))
    {
        configLine = trim(configLine);

        if (configLine == "")
        {
            continue;
        }

        size_t sectionStart = configLine.find_first_of("[");
        size_t sectionEnd = configLine.find_last_of("]");

        if (sectionStart != string::npos &&
            sectionEnd != string::npos &&
            sectionStart != sectionEnd)
        {
            configSectionName = configLine.substr(sectionStart + 1, sectionEnd - sectionStart - 1);
        }

        bool isValidConfig = configLine.find_first_of("=") != string::npos;

        if (sectionStart == string::npos && isValidConfig)
        {
            vector<string> config = splitString(configLine, "=");

            string key = trim(configSectionName) + "_" + trim(config[0]);
            string value = trim(config[1]);

            this->configs[key] = value;
        }
    }

    configFile.close();
}

// Initialize server & listen to incoming connections
void Server::initialize(const int &port)
{
    this->loadConfig();

    sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_port = htons(stoi(this->configs.at("server_port")));
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

            // read file from directory
            const File requestedFile = this->getStaticFile(clientRequest.resource.target.path.substr(1));

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

File Server::getStaticFile(const string &path)
{
    const fs::path root = this->configs["server_document_root"];

    string defaultFileName = "index.html";
    string absolutePath;

    // if the root file is requested
    if (path == "" || path == "/")
    {
        // if the root file name has been defined in the config file and is not empty set to definition
        if (this->configs.count("server_root_file") && this->configs["server_root_file"] != "")
        {
            absolutePath = File::mapPathToAbsolute(root / this->configs["server_root_file"]);
        }
        else
        {
            absolutePath = File::mapPathToAbsolute(root / "index.html");
        }
    }
    else
    {
        absolutePath = File::mapPathToAbsolute(root / path);
    }

    cout << absolutePath << endl;

    return File::fromPath(absolutePath);
}