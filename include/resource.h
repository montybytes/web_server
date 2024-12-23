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
public:
    const HttpMethod method;
    const URL target;
    const string protocol;

    Resource(const string &_method, const string &_target, const string &_protocol)
        : method(parseMethod(_method)), target(URL::fromString(_target)), protocol(_protocol) {}

private:
    static HttpMethod parseMethod(const string &_method)
    {
        //todo: throw 501 for POST,PUT,DELETE
        if (_method == "GET")
        {
            return HttpMethod::GET;
        }
        else if (_method == "POST")
        {
            return HttpMethod::POST;
        }
        else if (_method == "PUT")
        {
            return HttpMethod::PUT;
        }
        else if (_method == "DELETE")
        {
            return HttpMethod::DELETE;
        }
        else if (_method == "HEAD" || _method == "OPTIONS" || _method == "TRACE" || _method == "PATCH" || _method == "CONNECT")
        {
            // Unsupported methods
            // todo: throw 405 for unsupported methods
            return HttpMethod::UNKNOWN;
        }
        else
        {
            // todo: throw 400: bad request error
            return HttpMethod::UNKNOWN;
        }
    }
};

#endif