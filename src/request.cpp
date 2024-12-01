#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "request.h"

using namespace std;

// TODO: implement request functions to process requests
Request Request::parseRequest(const char *requestBuffer)
{
     // spliting request into major parts; method, headers & content
     vector<string> request = splitString(string(requestBuffer), "\r\n");

     // extracting method, path and version from header
     vector<string> resource = splitString(request[0], " ");

     // constructing header map
     map<string, string> headers;
     // get index of the first newline character that has no text in same line
     size_t bodySeparatorIdx = distance(request.begin(), find(request.begin(), request.end(), "\n"));

     for (size_t idx = 1; idx < bodySeparatorIdx; idx++)
     {
          vector<string> header = splitString(request[idx], ":");
          // assign key-value pairs corresponding to header key-values
          headers[trim(header[0])] = trim(header[1]);
     }

     const string body = request[request.size() - 1];

     const Resource res = Resource(resource[0], resource[1], resource[2]);

     const Request req = Request(res, headers, body);

     return req;
};