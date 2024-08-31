#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>
#include <iostream>
#include <string>

#define PORT 2077
#define ADDRESS "127.0.0.1"

using namespace std;

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return WSAGetLastError();
    }

    SOCKADDR_IN addr;
    int size = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(ADDRESS);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    SOCKET clientSocket;
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        return WSAGetLastError();
    }

    char buf[1024];   
    cout << "Input string: ";
    cin.getline(buf, 1024, '\n');

    sendto(clientSocket, buf, sizeof(buf), 0, (SOCKADDR*)&addr, size);

    recvfrom(clientSocket, buf, sizeof(buf), 0, (SOCKADDR*)&addr, &size);
    cout << "Result string: " << buf << endl;

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
