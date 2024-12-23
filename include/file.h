#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <unordered_map>

using namespace std;
namespace fs = filesystem;

class File
{
public:
    const size_t fileSize;
    const string fileName;
    const string fileExtension;
    const vector<char> fileContent;

    File(
        const string &_fileName,
        const string &_fileExtension,
        const vector<char> &_fileContent,
        const size_t &_fileSize)
        : fileName(_fileName),
          fileExtension(_fileExtension),
          fileContent(_fileContent),
          fileSize(_fileSize) {}

    static string readText(const string &path);

    static vector<char> readFile(const string &path);

    static string mapPathToAbsolute(const string &path);

    static File fromPath(const fs::path &path);

    static string getContentType(const string &extension);

private:
    static const inline unordered_map<string, string> contentTypeMap = {
        {".html", "text/html"},
        {".txt", "text/plain"},
        {".json", "application/json"},
        {".xml", "application/xml"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".png", "image/png"},
        {".gif", "image/gif"},
        {".pdf", "application/pdf"},
        {".zip", "application/zip"},
        {".bin", "application/octet-stream"},
        {".css", "text/css"},
        {".js", "text/javascript"},
        {"form-data.txt", "application/x-www-form-urlencoded"},
    };
};

#endif