#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <iostream>
#include <winsock2.h>

using namespace std;

int main() {
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(1280);
    addr.sin_family = AF_INET;

    SOCKET serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
    listen(serverSocket, 3);

    while (true) {
        SOCKADDR_IN addr_in;
        int size = sizeof(addr_in);
        SOCKET connectionSocket = accept(serverSocket, (SOCKADDR*)&addr_in, &size);
        if (connectionSocket == INVALID_SOCKET) {
            cerr << "Accept failed\n";
        } else {
            cout << "Accepted" << endl;
            char msg[100] = "Hello ny name is Gus!";
            send(connectionSocket, msg, sizeof(msg) - 2, 0); 
        }
        closesocket(connectionSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}