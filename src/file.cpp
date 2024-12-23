#include "file.h"

bool File::isFileAvailable(const string &path)
{
    return ifstream(path).good();
}

string File::readText(const string &path)
{
    ifstream requestedFile(path);

    ostringstream stringBuffer;

    // read text file data into string buffer
    stringBuffer << requestedFile.rdbuf();

    // if file is not found thrrow 404 error
    // if (!requestedFile.is_open())
    // {
    //     cerr << "Failed to open file" << endl;
    // }

    // close file
    requestedFile.close();

    return stringBuffer.str();
}

vector<char> File::readFile(const string &path)
{
    ifstream requestedFile(path, ios::binary | ios::ate);

    if (!requestedFile.is_open())
    {
        // todo: throw 404 if file doesn't exist
    }

    // getting the size of the file
    streamsize fileSize = requestedFile.tellg();
    requestedFile.seekg(0, ios::beg);

    // copy file data into buffer
    vector<char> buffer(fileSize);
    requestedFile.read(buffer.data(), fileSize);

    // close file
    requestedFile.close();

    return buffer;
}

string File::mapPathToAbsolute(const string &path)
{
    // todo: find a way to ensure current_path is always the directory the server is running from
    // path to serve files from
    fs::path currentPath = fs::current_path().append("public");

    // append request path to static file directory
    if (path == "/")
    {
        return currentPath / "index.html";
    }

    return currentPath / path.substr(1);
}

string File::getContentType(const string &extension)
{
    // todo: throw 415 if find returns string::npos
    auto itr = contentTypeMap.find(extension);

    if (itr != contentTypeMap.end())
    {
        return itr->second;
    }

    return "application/octet-stream";
}

File File::fromPath(const fs::path &path)
{
    // get file contents from system
    const vector<char> content = readFile(path);

    // create file object and return object
    return File(path.filename(), path.extension(), content, content.size());
}