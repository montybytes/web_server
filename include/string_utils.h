#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// todo: throw 500 in case of failure
// function to split strings
inline vector<string> splitString(const string &input, const string &delimiter)
{
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

// todo: throw 500 in case of failure
// function to remove trailing whitespace+newline+tabs chars
inline string trim(const string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos)
    {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");

    return str.substr(start, end - start + 1);
}

// todo: throw 500 in case of failure
// function to turn map into string
inline string mapToString(const unordered_map<string, string> &_map)
{
    ostringstream stringStream;

    for (const auto &pair : _map)
    {
        stringStream << pair.first << ":" << pair.second << "\n";
    }

    return stringStream.str();
}