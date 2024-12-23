#include <algorithm>
#include <variant>

#include "request.h"
#include "error.h"

Request Request::parseRequest(const char *requestBuffer)
{
     // spliting request into major parts; method|headers|body
     vector<string> request = splitString(string(requestBuffer), "\r\n");

     /*
          constructing resource line object
     */

     // extracting method, path and version from header
     vector<string> resource = splitString(request[0], " ");

     const Resource res = Resource(resource[0], resource[1], resource[2]);

     /*
          constructing header map
     */

     unordered_map<string, variant<string, int>> headers;

     // get index of the first newline character that has no text in same line
     size_t bodySeparatorIdx = distance(request.begin(), find(request.begin(), request.end(), "\n"));

     // todo: implement a check for header field size
     for (size_t idx = 1; idx < bodySeparatorIdx; idx++)
     {
          // error if headers do not contain ":" (malformed)
          if (request[idx].find(":") == string::npos)
          {
               throw Error(ErrorCode::E400_BAD_REQUEST);
          }

          vector<string> header = splitString(request[idx], ":");

          string key = toLowercase(trim(header[0]));
          variant<string, int> value = trim(header[1]);

          // if common standard number headers cannot be converted to integers
          if (key == "content-length" ||
              key == "retry-after" ||
              key == "age" ||
              key == "max-forwards" ||
              key == "content-range" ||
              key == "expires")
          {
               try
               {
                    value = stoi(get<string>(value));
               }
               catch (const std::exception &e)
               {
                    throw Error(ErrorCode::E400_BAD_REQUEST);

                    std::cerr << e.what() << '\n';
               }
          }

          // if header value > 8KB
          if (get<string>(value).size() > 8192)
          {
               throw Error(ErrorCode::E400_BAD_REQUEST);
          }

          // assign key-value pairs corresponding to header key-values
          headers[key] = value;
     }

     /*
          constructing request body
     */

     // body is is located at index of next item after header lines and resource line
     string body = request[headers.size() + 1];

     if (body == "\n")
     {
          body = "";
     }

     // if content-length is found, is not 0 and no body exists
     if (headers.find("content-length") != headers.end() &&
         get<int>(headers["content-length"]) > 0 &&
         body.size() == 0)
     {
          throw Error(ErrorCode::E400_BAD_REQUEST);
     }

     // if method is POST and no content-type
     if (res.method == HttpMethod::POST &&
         headers.count("content-type") == 0)
     {
          throw(ErrorCode::E400_BAD_REQUEST);
     }

     // if required headers are not found (only HTTP/1.1 spec)
     if (headers.count("host") == 0)
     {
          throw Error(ErrorCode::E400_BAD_REQUEST);
     }

     // if body length is above limit (10MB)
     if (body.size() > 1048576)
     {
          throw Error(ErrorCode::E413_PAYLOAD_TOO_LARGE);
     }

     // if content-length header not found and body present
     if (headers.find("content-length") == headers.end() &&
         body.size() != 0)
     {
          throw Error(ErrorCode::E400_BAD_REQUEST);
     }

     // extract body based on content-length header
     if (headers.find("content-length") != headers.end() &&
         body.size() != 0)
     {
          body = body.substr(0, get<int>(headers.at("content-length")));
     }

     // if http version (resource[2]) isn't supported (only 1.1)
     if (res.protocol != "HTTP/1.1")
     {
          throw Error(ErrorCode::E505_HTTP_VERSION_NOT_SUPPORTED);
     }

     const Request req = Request(res, headers, body);

     return req;
};