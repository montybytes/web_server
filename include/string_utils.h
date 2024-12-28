#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <algorithm>

using namespace std;

// todo: throw internal error & log for failed string operations
// function to split strings
inline vector<string> splitString(const string &input, const string &delimiter)
{
    if (input.empty() || (input.size() == 1 && delimiter != ""))
    {
        return {};
    }

    vector<string> tokens;

    size_t pos = 0, start = 0;

    while ((pos = input.find(delimiter, start)) != string::npos)
    {
        if (pos > start)
        {
            tokens.push_back(input.substr(start, pos - start));
        }
        start = pos + 1;
    }

    if (start < input.length())
    {
        tokens.push_back(input.substr(start));
    }
    return tokens;
}

// todo: throw internal error & log for failed string operations
// function to remove trailing whitespace+newline+tabs chars
inline string trim(const string &str)
{
    if (str == "")
    {
        return "";
    }

    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos)
    {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}

// todo: throw internal error & log for failed string operations
// function to turn map into string
inline string mapToString(const unordered_map<string, string> &_map)
{
    if (_map.size() == 0)
    {
        return "";
    }

    ostringstream stringStream;

    for (const auto &pair : _map)
    {
        stringStream << pair.first << ":" << pair.second << "\n";
    }

    return stringStream.str();
}

// todo: throw internal error & log for failed string operations
// function to convert strings to all lowercase
inline string toLowercase(const string &str)
{
    string lowercase_str = str;

    transform(
        lowercase_str.begin(),
        lowercase_str.end(),
        lowercase_str.begin(),
        [](unsigned char c)
        { return tolower(c); });

    return lowercase_str;
}

#endif