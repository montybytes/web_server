#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>
#include <exception>
#include <map>

using namespace std;

enum ErrorCode
{
    // client errors
    E400_BAD_REQUEST = 400,
    E401_UNAUTHORIZED = 401,
    E403_FORBIDDEN = 403,
    E404_NOT_FOUND = 404,
    E405_METHOD_NOT_ALLOWED = 405,
    E408_REQUEST_TIMEOUT = 408,
    E409_CONFLICT = 40905,
    E410_GONE = 410,
    E413_PAYLOAD_TOO_LARGE = 413,
    E414_URI_TOO_LONG = 414,
    E415_UNSUPPORTED_MEDIA_TYPE = 415,
    E429_TOO_MANY_REQUESTS = 429,
    // server errors
    E500_INTERNAL_SERVER_ERROR = 500,
    E501_NOT_IMPLEMENTED = 501,
    E502_BAD_GATEWAY = 502,
    E503_SERVICE_UNAVAILABLE = 503,
    E504_GATEWAY_TIMEOUT = 504,
    E505_HTTP_VERSION_NOT_SUPPORTED = 505,
};

class Error : public exception
{
public:
    const ErrorCode code;
    const string message;

    explicit Error(const ErrorCode &_code) : code(_code), message(errorDescriptions.at(_code)) {}

    const char *what() const noexcept override
    {

        return message.c_str();
    }

private:
    static const inline map<ErrorCode, string> errorDescriptions = {
        // client error descriptions
        {E400_BAD_REQUEST, "The server cannot process the request due to client error."},
        {E401_UNAUTHORIZED, "Authentication is required and has failed or not been provided."},
        {E403_FORBIDDEN, "The client does not have access rights to the content."},
        {E404_NOT_FOUND, "The server can't find the requested resource."},
        {E405_METHOD_NOT_ALLOWED, "The request method is not supported for the requested resource."},
        {E408_REQUEST_TIMEOUT, "The server timed out waiting for the request."},
        {E409_CONFLICT, "The request could not be completed due to a conflict with the current state of the resource."},
        {E410_GONE, "The requested resource is no longer available and will not be available again."},
        {E413_PAYLOAD_TOO_LARGE, "The request is larger than the server is willing or able to process."},
        {E414_URI_TOO_LONG, "The URI requested by the client is longer than the server is willing to interpret."},
        {E415_UNSUPPORTED_MEDIA_TYPE, "The media format of the requested data is not supported by the server."},
        {E429_TOO_MANY_REQUESTS, "The user has sent too many requests in a given amount of time."},
        // server error descriptions
        {E500_INTERNAL_SERVER_ERROR, "The server encountered a situation it doesn't know how to handle."},
        {E501_NOT_IMPLEMENTED, "The server does not recognize the request method or lacks the ability to fulfill it."},
        {E502_BAD_GATEWAY, "The server received an invalid response from an upstream server."},
        {E503_SERVICE_UNAVAILABLE, "The server is not ready to handle the request, often due to maintenance."},
        {E504_GATEWAY_TIMEOUT, "The server is acting as a gateway and cannot get a response in time."},
        {E505_HTTP_VERSION_NOT_SUPPORTED, "The HTTP version used in the request is not supported by the server."}};
    ;
};

#endif