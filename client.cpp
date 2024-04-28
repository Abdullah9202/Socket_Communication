#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main(int argc, char const *argv[]) 
{
    // Initialize Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int win_SOK = WSAStartup(ver, &wsData);
    // Checking for error
    if (win_SOK != 0) 
    {
        cerr << "Error initializing Winsock! Quitting" << endl;
        return -1;
    }

    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    // Checking for error
    if (clientSocket == INVALID_SOCKET) 
    {
        cerr << "Error creating a socket! Quitting" << endl;
        return -1;
    }

    // Connect to the server
    sockaddr_in hint;
    hint.sin_family = AF_INET; // Internet family
    hint.sin_port = htons(54000); // Host to network with port number 54000
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr); // Connection to local address
    // Client Socket
    connect(clientSocket, (sockaddr*)&hint, sizeof(hint));

    // Communication loop
    char buf[4096];
    string userInput;

    do {
        // Send data to server
        cout << "Client: ";
        getline(cin, userInput); // Taking input from client
        send(clientSocket, userInput.c_str(), userInput.size() + 1, 0); // Sending to server

        // Receive response from server
        int bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);
        // Checking if the server is down
        if (bytesReceived <= 0) 
        {
            cerr << "Connection closed by server." << endl;
            break;
        }

        // Display received response
        cout << string(buf, 0, bytesReceived) << endl;

    } while (userInput != "exit");

    // Cleanup Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
