#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1280);
    addr.sin_family = AF_INET;

    SOCKET client_socket;
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    char msg[255]{};
    if (connect(client_socket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Connection failed\n";
        return 1;
    } else {
        cout << "Connection succecced\n";
        if (recv(client_socket, msg, sizeof(msg), 0) != 0) {
            msg[strlen(msg)] = '\0';
            cout << msg << endl;
        }
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
