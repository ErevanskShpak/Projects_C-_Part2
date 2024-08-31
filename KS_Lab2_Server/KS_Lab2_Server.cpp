#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <string>

#define PORT 2077

using namespace std;

string process(char* orig);

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return WSAGetLastError();
    }

    SOCKADDR_IN addr;
    int l = sizeof(addr);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    SOCKET serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        cerr << "Creation failed\n";
        return WSAGetLastError();
    }

    if (bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Binding failed\n";
        return WSAGetLastError();
    }
    
    char buf[1024];
    while (true) {
        if (recvfrom(serverSocket, buf, sizeof(buf), 0, (SOCKADDR*)&addr, &l) != 0) {
            if (strlen(buf) % 3 == 0) {
                string str = process(buf);
                strcpy_s(buf, str.c_str());
            }
            
            sendto(serverSocket, buf, sizeof(buf), 0, (SOCKADDR*)&addr, l);
        }
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

string process(char* orig) {
    string res = "", temp;
    for (size_t i = 0; i < strlen(orig); ++i) {
        temp = orig[i];

        if (orig[i] >= '0' && orig[i] <= '9') {
            while (orig[i + 1] >= '0' && orig[i + 1] <= '9') {
                temp += orig[++i];
            }

            int number = atoi(temp.c_str());
            if (number % 3 == 0) {
                temp = "";
            }

        }

        res.append(temp);
    }

    return res;
}