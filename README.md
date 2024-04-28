# Socket Communication using C++ and Winsock

This repository contains a simple TCP chat application implemented in C++ using the Winsock library. The application consists of two programs: a server and a client. The server listens for incoming connections from clients, receives messages from clients, and sends acknowledgment responses. The client connects to the server, sends messages to the server, and displays acknowledgment responses from the server.

## Server

### Features

- Listens for incoming connections on a specified port.
- Receives messages from connected clients.
- Stores received messages in both a linked list and a stack.
- Displays the received messages and the current stack to the console.
- Sends acknowledgment responses to clients.

### Usage

1. Compile and run the `server.cpp` program.
2. Connect one or more clients to the server.

## Client

### Features

- Connects to a specified server and port.
- Sends messages to the server.
- Displays acknowledgment responses from the server.
- Allows the user to exit the chat session by typing "exit".

### Usage

1. Compile and run the `client.cpp` program.
2. Enter messages to send to the server.
3. Type "exit" to disconnect from the server and exit the program.

## Dependencies

- This application requires the Winsock library for network communication.
- The code is written in C++ and can be compiled using a C++ compiler that supports Winsock, such as Visual Studio on Windows.

## Compatibility

- The application is designed to run on Windows operating systems due to its reliance on Winsock.

## Credits

- Created By Abdullah Khurram <https://www.github.com/Abdullah9202>
