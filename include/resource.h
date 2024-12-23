#ifndef RESOURCE_H
#define RESOURCE_H

#include <vector>

#include "url.h"
#include "error.h"

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
        // throw 501 for POST,PUT,DELETE until implemented
        if (_method == "GET")
        {
            return HttpMethod::GET;
        }
        else if (_method == "POST")
        {
            throw Error(ErrorCode::E501_NOT_IMPLEMENTED);
        }
        else if (_method == "PUT")
        {
            throw Error(ErrorCode::E501_NOT_IMPLEMENTED);
        }
        else if (_method == "DELETE")
        {
            throw Error(ErrorCode::E501_NOT_IMPLEMENTED);
        }
        else if (_method == "HEAD" || _method == "OPTIONS" || _method == "TRACE" || _method == "PATCH" || _method == "CONNECT")
        {
            // Unsupported methods
            throw Error(ErrorCode::E405_METHOD_NOT_ALLOWED);
        }
        else
        {
            // non http method = bad request
            throw Error(ErrorCode::E400_BAD_REQUEST);
        }
    }
};

#endif