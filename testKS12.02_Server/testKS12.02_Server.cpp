#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main() {
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET  s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s, 5);

	while (true) {
		char buf[255], res[100], b[255], * Res;
		//структура определяет удаленный адрес,
		//с которым  соединяется сокет
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET s2 = accept(s, (struct sockaddr*)&remote_addr, &size);

		char msg[100] = "HEllo ny name is Gus!";
		//recv(s2, b, sizeof(b), 0) != 0;
		//while (recv(s2, b, sizeof(b), 0) != 0) {

		//	int i = 0;
		//	for (unsigned j = 0; j <= strlen(b); j++)
		//		if (b[j] == 'a') i++;

		//	_itoa(i, res, 10);

			/*Res = new char[strlen(msg) + 1];
			strcpy(Res, msg);
			Res[strlen(msg)] = '\0';*/


		//	//Посылает данные на соединенный сокет
		//	send(s2, Res, sizeof(Res) - 2, 0);
			send(s2, msg, sizeof(msg) - 2, 0);
		//}

		closesocket(s2);
	}

	WSACleanup();
}