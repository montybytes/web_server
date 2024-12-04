#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class File
{
public:
    const size_t fileSize;
    const string fileName;
    const string fileExtension;

    File(const size_t &_fileSize, const string &_fileName, const string &_fileExtension)
        : fileSize(_fileSize), fileName(_fileName), fileExtension(_fileExtension) {}

    static bool isFileAvailable(const string &path);

    static string readText(const string &path);

    static void readBinary(const string &path);

    static string mapPathToAbsolute(const string &path);
};

#endif