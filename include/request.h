#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>

#include "url.h"
#include "resource.h"

using namespace std;

class Request
{
public:
    const Resource &resource;
    const map<string, string> &headers;
    const string &body;

    Request(const Resource &_res, const map<string, string> &_headers, const string &_body)
        : resource(_res), headers(_headers), body(_body) {}

    static Request parseRequest(const char *);
};

#endif