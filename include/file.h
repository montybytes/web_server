#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

enum ImageMime
{
    APNG,
    AVIF,
    GIF,
    PNG,
    JPEG,
    SVG_XML,
    WEBP
};

enum TextMime
{
    PLAIN,
    CSS,
    HTML,
    JAVASCRIPT
};

enum ApplicationMime
{
    OCT_STREAM
};

enum MimeType
{
    ImageMime,
    TextMime,
    ApplicationMime
};

class File
{
public:
    const size_t fileSize;
    const string fileName;
    const string fileExtension;
    const vector<char> fileContent;
    // const MimeType fileType;

    File(
        const string &_fileName,
        const string &_fileExtension,
        const vector<char> &_fileContent,
        const size_t &_fileSize
        // const MimeType &_fileType
        ) : fileName(_fileName),
            fileExtension(_fileExtension),
            fileContent(_fileContent),
            fileSize(_fileSize)
    //   fileType(_fileType)
    {
    }

    static bool isFileAvailable(const string &path);

    static string readText(const string &path);

    static vector<char> readFile(const string &path);

    static string mapPathToAbsolute(const string &path);

    static File fromPath(const fs::path &path);
};

#endif