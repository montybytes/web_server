#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <map>

using namespace std;

class Resource
{
    string method;
    string path;
    string version;

public:
    Resource(const string &methodRef, const string &pathRef, const string &versionRef)
        : method(methodRef), path(pathRef), version(versionRef) {}
};

class Headers
{
};

class Body
{
};

// TODO: define request methods and properties
class Request
{
public:
    const Resource *resource;
    const map<string, string> headers;
    const string *body;

    Request() {}

    Request(const Resource *_res, const map<string, string> &_headers, const string *_body)
        : resource(_res), headers(_headers), body(_body) {}

    static Request parseRequest(const char *);
};

#endif