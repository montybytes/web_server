#include <algorithm>

#include "request.h"

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

     // todo: implement a check for header field size
     for (size_t idx = 1; idx < bodySeparatorIdx; idx++)
     {
          // todo: throw 400 if headers do not contain ":"
          // todo: throw 400 if number headers contain strings
          // todo: throw 400 if header value > 8KB
          // todo: throw 400 if content-length is found and no body exists
          vector<string> header = splitString(request[idx], ":");

          // assign key-value pairs corresponding to header key-values
          headers[trim(header[0])] = trim(header[1]);
     }

     // todo: throw 400 if method is POST and no content-type
     // todo: throw 400 if minimum/required headers are not found
     // todo: throw 413 if body length is above limit
     // todo: throw 411 if content-length header not found and body present

     // todo: extract body based on content-length header
     const string body = request[request.size() - 1];

     // todo: throw 505 if resource[2] isn't supported
     const Resource res = Resource(resource[0], resource[1], resource[2]);

     const Request req = Request(res, headers, body);

     return req;
};