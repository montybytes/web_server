#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Response
{
public:
    const string status;
    map<string, string> headers;

    Response(const string &_status)
        : status(_status) {}

    void setHeader(const string &key, const string &value);

    void sendStatusHeader(const int &socket);

    static void sendText(const string &text, const int &socket);

    static void sendBinary(const vector<char> &binary, const int &socket);
};

#endif