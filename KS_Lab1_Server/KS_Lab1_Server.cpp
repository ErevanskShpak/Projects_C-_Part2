#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <iostream>
#include <winsock2.h>
#include <string>

#define PORT 2077

using namespace std;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return WSAGetLastError();
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    SOCKET serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        cerr << "Creation failed\n";
        return WSAGetLastError();
    }

    if (bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Binding failed\n";
        return WSAGetLastError();
    }

    if (listen(serverSocket, 1) != 0) {
        cerr << "Listening failed\n";
        return WSAGetLastError();
    }

    SOCKADDR_IN addr_in;
    int size = sizeof(addr_in);
    SOCKET connectionSocket;

    while (true) {
        connectionSocket = accept(serverSocket, (SOCKADDR*)&addr_in, &size);
        if (connectionSocket == INVALID_SOCKET) {
            cerr << "Acceptance failed\n";
        } else {
            cout << "Accepted\n\n";

            double first, second, res;
            char op;

            recv(connectionSocket, (char*)&first, sizeof(first), 0);
            recv(connectionSocket, (char*)&second, sizeof(second), 0);
            recv(connectionSocket, &op, sizeof(op), 0);

            switch (op) {
            case '+':
                res = first + second;
                break;
            case '-':
                res = first - second;
                break;
            case '*':
                res = first * second;
                break;
            case '/':
                res = first / second;
                break;
            default:
                res = 0;
            }

            send(connectionSocket, (char*)&res, sizeof(res), 0);
        }

        closesocket(connectionSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
