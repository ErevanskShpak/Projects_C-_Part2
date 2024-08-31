#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main() {
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 2);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1280);
    addr.sin_family = AF_INET;

    SOCKET server_socket;
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        return 1;
    }
    bind(server_socket, (SOCKADDR*)&addr, sizeof(addr));
    listen(server_socket, 3);

    SOCKET newConnection;
    SOCKADDR_IN addr2;
    int sizeofaddr2 = sizeof(addr2);
    char* Res;
    char msg[255];
    if (newConnection = accept(server_socket, (SOCKADDR*)&addr2, &sizeofaddr2) == INVALID_SOCKET) {
        cerr << "Accept failed";
    }
    else {
        cout << "Accepted" << endl;
        cin.getline(msg, 100, '\n');
        Res = new char[strlen(msg) + 1];
        strcpy(Res, msg);
        Res[strlen(msg)] = '\0';
        send(newConnection, Res, sizeof(Res) - 2, 0);
    }

    closesocket(newConnection);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}

//int num_of_a = 0;
   //char buffer[256]{};
   //while (true) {
   //    if ((new_socket = accept(server_socket, (struct sockaddr*)&addr, &sizeofaddr)) == INVALID_SOCKET) {
   //        std::cerr << "Accept failed\n";
   //        return 1;
   //    }
   //    recv(new_socket, buffer, sizeof(buffer), 0);

   //    // Count 'a' characters
   //    for (int i = 0; buffer[i] != '\0'; ++i) {
   //        if (buffer[i] == 'a' || buffer[i] == 'A') {
   //            num_of_a++;
   //        }
   //    }

   //    // Convert count to string and send back to client
   //    char response[10];
   //    _itoa_s(num_of_a, response, 10);
   //    send(new_socket, response, strlen(response), 0);

   //    num_of_a = 0; // Reset count
   //    closesocket(new_socket);
   //}