#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>

#include "url.h"

enum HttpMethod
{
    GET,
    POST,
    PUT,
    UPDATE,
    DELETE,
    PATCH,
    UNKNOWN
};

class Resource
{
    HttpMethod method;
    URL target;
    string protocol;

public:
    Resource(const string &methodRef, const string &targetRef, const string &protocolRef)
        : target(URL::fromString(targetRef)), protocol(protocolRef)
    {
        if (methodRef == "GET")
        {
            method = HttpMethod::GET;
        }
        else if (methodRef == "POST")
        {
            method = HttpMethod::POST;
        }
        else if (methodRef == "PUT")
        {
            method = HttpMethod::PUT;
        }
        else if (methodRef == "DELETE")
        {
            method = HttpMethod::DELETE;
        }
        else
        {
            method = HttpMethod::UNKNOWN; // Default for unsupported methods
        }
    }
};

#endif