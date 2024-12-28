#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>
#include <variant>

#include "url.h"
#include "resource.h"

using namespace std;

class Request
{
public:
    const Resource resource;
    const unordered_map<string, variant<string, int>> headers;
    const string body;

    Request(const Resource &_res,
            const unordered_map<string, variant<string, int>> &_headers,
            const string &_body)
        : resource(_res), headers(_headers), body(_body) {}

    static Request parseRequest(const string &requestBuffer);
};

#endif