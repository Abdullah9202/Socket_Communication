#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

// Linked List Node
struct ListNode 
{
    string message;
    ListNode* next;
};

// Stack Node
struct StackNode 
{
    string message;
    StackNode* next;
};

int main(int argc, char const *argv[]) 
{
    // Checking the OS
    #ifdef _WIN32
        cout << "Launched on Windows OS" << endl;
        // Initialize Winsock
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2); // Version (2.2 ==> Latest)
        int win_SOK = WSAStartup(ver, &wsData);
        // Checking if there is any error
        if (win_SOK != 0) 
        {
            cerr << "Error initializing Winsock! Quitting" << endl;
            return -1;
        }
    #endif
    
    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0); // AF_INET == Internet | SOCK_STREAM == Uses IP/TCP and transfers all the data at once | 0 == default transfer protocol
    // Checking for error
    if (listening == INVALID_SOCKET) // INVALID_SOCKET == build-in error checking
    {
        cerr << "Error create a socket! Quitting" << endl;
        return -1;
    }

    // Bind the socket to an IP address and port
    sockaddr_in hint;
    hint.sin_family = AF_INET; // Internet family
    hint.sin_port = htons(54000); // Using host to network short with port 54000
    hint.sin_addr.S_un.S_addr = INADDR_ANY; // Extracting the IP address of local machine
    // Binding the socket
    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Listening
    listen(listening, SOMAXCONN);

    // Wait for a connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    // Linked List Node
    ListNode* messageList = nullptr;

    // Stack Node
    StackNode* messageStack = nullptr;

    // Communication loop
    char buf[4096];
    while (true) 
    {
        // Receive data from client
        int bytesReceived = recv(clientSocket, buf, sizeof(buf), 0);
        // Checking if the client is down
        if (bytesReceived <= 0) 
        {
            cerr << "Connection closed by client." << endl;
            break;
        }

        // Linked List: Add received message to the list
        ListNode* newNode = new ListNode{ string(buf, 0, bytesReceived), nullptr };
        newNode->next = messageList;
        messageList = newNode;

        // Linked List: Display the entire list
        cout << "Messages received:" << endl;
        ListNode* current = messageList;
        // Traversing and displaying the messages
        while (current != nullptr) 
        {
            cout << current->message << endl;
            current = current->next;
        }

        // Stack: Push the received message onto the stack
        StackNode* stackNode = new StackNode{ string(buf, 0, bytesReceived), nullptr };
        stackNode->next = messageStack;
        messageStack = stackNode;

        // Stack: Display the current stack
        cout << "Current Stack:" << endl;
        StackNode* stackCurrent = messageStack;
        // Traversing and displaying the messages in stack
        while (stackCurrent != nullptr) 
        {
            cout << stackCurrent->message << endl;
            stackCurrent = stackCurrent->next;
        }

        // Send response back to client
        string responseMessage = "Server: Got your message!";
        send(clientSocket, responseMessage.c_str(), responseMessage.size() + 1, 0);

    }

    // Cleanup Winsock
    closesocket(clientSocket);
    closesocket(listening);
    WSACleanup();

    return 0;
}
