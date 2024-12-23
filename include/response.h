#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Response
{
public:
    const string status;
    unordered_map<string, string> headers;

    Response(const string &_status)
        : status(_status) {}

    void setHeader(const string &key, const string &value);

    void send(const int &socket, const string &text);

    void send(const int &socket, const vector<char> &binary);
};

#endif