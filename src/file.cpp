#include "file.h"
#include "error.h"

string File::readText(const string &path)
{
    ifstream requestedFile(path);

    ostringstream stringBuffer;

    // read text file data into string buffer
    stringBuffer << requestedFile.rdbuf();

    // throw 404 if file doesn't exist
    if (!requestedFile.is_open() || !ifstream(path).good())
    {
        throw Error(ErrorCode::E404_NOT_FOUND);
    }

    // close file
    requestedFile.close();

    return stringBuffer.str();
}

vector<char> File::readFile(const string &path)
{
    ifstream requestedFile(path, ios::binary | ios::ate);

    // throw 404 if file doesn't exist
    if (!requestedFile.is_open() || !ifstream(path).good())
    {
        throw Error(ErrorCode::E404_NOT_FOUND);
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
    return fs::current_path() / path;
}

string File::getContentType(const string &extension)
{
    auto itr = contentTypeMap.find(extension);

    if (itr != contentTypeMap.end())
    {
        return itr->second;
    }
    // if find returns end of the map
    else
    {
        throw Error(ErrorCode::E415_UNSUPPORTED_MEDIA_TYPE);
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