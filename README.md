# A simple web server written in C++

This is a C++ project where I try to make a web server for the fun of it, plus learn more about system level C++. It is a _VERY_ barebones server so no fancy stuff like multithreading or compression...yet.

⚠️ If you come accross this, please do not use! This server uses HTTP so **no** encryption is in place! ⚠️

## Current Objectives

- [ ] Implement other error codes and general error handling

- [ ] Implement unit tests

- [ ] Implement basic logging

- [ ] Implement sessions and cookies

- [ ] Implement using a config file / cli arguments

- [ ] Implement memory caching for small files

- [ ] Implement simple authentication for REST requests

- [ ] Try ensure the following security risks are minimized:
  - [ ] directory traversal attacks
  - [ ] file disclosure
  - [ ] input based injection attacks
  - [ ] buffer overflows

## Interesting Objectives

- [ ] Multithreading

- [ ] Asynchronous processing

- [ ] HTTPS support

- [ ] Response compression for large responses
