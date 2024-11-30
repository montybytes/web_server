#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "request.h"
#include "string_util.h"

using namespace std;

// variables/constants
const string line_break = "\r\n";

// TODO: implement request functions to process requests
Request Request::parseRequest(const char *requestBuffer)
{
    cout << "Raw request: " << requestBuffer << endl
         << endl;

    // spliting request into major parts; method, headers & content
    vector<string> request = splitString(string(requestBuffer), line_break);

    // extracting method, path and version from header
    vector<string> resource = splitString(request[0], " ");

    cout << "The request method: " << resource[0] << endl;
    cout << "The path requested: " << resource[1] << endl;
    cout << "The http version: " << resource[2] << endl;

    // constructing header map
    map<string, string> headers;
    // get index of the first newline character that has no text in same line
    int index = distance(request.begin(), find(request.begin(), request.end(), "\n"));

    cout << "The http headers are: " << endl;
    for (int i = 1; i < index; i++)
    {
        vector<string> header = splitString(trim(request[i]), ": ");
        // assign key-value pairs corresponding to header key-values
        headers[header[0]] = header[1];
    }

    for (auto const &header : headers)
    {
        cout << header.first << ": " << header.second << endl;
    }

    const Resource res = Resource(resource[0], resource[1], resource[2]);

    const Request req = Request(&res, headers, nullptr);

    return req;
};