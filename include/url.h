#ifndef URL_H
#define URL_H

#include <string>
#include <unordered_map>
#include <vector>

#include "string_utils.h"

using namespace std;

class URL
{
public:
    const string path;
    const unordered_map<string, string> parameters;

    URL(const string &_path, const unordered_map<string, string> &_parameters)
        : path(_path), parameters(_parameters) {}

    // todo: throw 500 for failed string operations
    static URL fromString(const string &urlString)
    {
        string path = urlString;
        string params = "";

        // todo: throw 414 if path is extremely large

        const size_t paramStartIdx = urlString.find_first_of("?");

        if (paramStartIdx != string::npos)
        {
            // path is read from first character until before the param separator
            path = urlString.substr(0, paramStartIdx);
            params = urlString.substr(paramStartIdx + 1, urlString.size() - paramStartIdx);
        }

        // create map of parameters
        unordered_map<string, string> paramMap;
        vector<string> paramList = splitString(params, "&");

        for (size_t idx = 0; idx < paramList.size(); idx++)
        {
            vector<string> param = splitString(paramList[idx], "=");
            paramMap[param[0]] = param[1];
        }

        return URL(path, paramMap);
    }
};

#endif