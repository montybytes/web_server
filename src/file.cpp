#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

#include "file.h"

bool File::isFileAvailable(const string &path)
{
    return ifstream(path).good();
}

string File::readText(const string &path)
{
    ifstream requestedFile(path);

    ostringstream stringBuffer;
    stringBuffer << requestedFile.rdbuf();

    // if file is not found print error and return 404
    if (!requestedFile.is_open())
    {
        cerr << "Failed to open file" << endl;
    }

    // const File file = File()

    return "";
}

void File::readBinary(const string &path)
{
    ifstream requestedFile(path, ios::binary);

    // if file is not found print error and return 404
    if (!requestedFile)
    {
        cerr << "Failed to open file" << endl;
    }

    return;
}

string File::mapPathToAbsolute(const string &path)
{
    // path to serve files from
    fs::path currentPath = fs::current_path().append("public");

    // append request path to static file directory
    if (path != "/")
    {
        return currentPath.append(path);
    }

    return currentPath.append("index.html");
}