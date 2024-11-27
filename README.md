A simple web server written in C++

To-dos:

- [x] Initialize the Server:

  - [x] Create a socket, bind to a port, and listen for incoming connections.

- [x] Accept a Connection:

  - [x] Accept a single client connection
  - [x] Read the incoming HTTP request.

- [X] Parse the Request:

  - [X] Extract the HTTP method and requested path.

- [ ] Find and Serve the Resource:

  - [ ] Look for the requested file in the server's root directory.
  - [ ] If the file exists, read its contents and return it in the response.
  - [ ] If not, return a "404 Not Found" response.

- [ ] Close the Connection:
  - [ ] Send the response and close the connection.
