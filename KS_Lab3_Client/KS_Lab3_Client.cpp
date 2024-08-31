#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>

#define PORT 5678
#define ADDRESS "127.0.0.1"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return WSAGetLastError();
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr(ADDRESS);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    SOCKET clientSocket;
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        WSACleanup();
        return WSAGetLastError();
    }

    if (connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Connection failed\n\n";
        closesocket(clientSocket);
        WSACleanup();
        return WSAGetLastError();
    }
    else {
        cout << "Connection succeeded\n";

        vector<char> bufRecv(1024);
        string bufSend;
        int length;
        cin.unsetf(ios::skipws);
        while (recv(clientSocket, (char*)&length, sizeof(length), 0)) {
            bufRecv.resize(length+1);
            recv(clientSocket, bufRecv.data(), length, 0);
            bufRecv[length] = '\0';
            cout << bufRecv.data();
            
            do {
                getline(cin, bufSend);
            } while (bufSend.empty());
            
            send(clientSocket, bufSend.c_str(), bufSend.size(), 0);
        }

    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
