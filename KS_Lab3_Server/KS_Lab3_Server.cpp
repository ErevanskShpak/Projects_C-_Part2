#include "StudArray.h"
#include <windows.h>

using namespace std;

#define PORT 2077

class ThreadParams {
public:
    SOCKET socket;
    StudArray* studArr;

    ThreadParams(SOCKET s, StudArray* arr) {
        this->socket = s;
        this->studArr = arr;
    }
};

void menu(SOCKET& s, StudArray& studArr);

DWORD WINAPI ThreadFunc(LPVOID param);

int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    StudArray studArr;

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
        WSACleanup();
        return WSAGetLastError();
    }

    if (bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Binding failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return WSAGetLastError();
    }

    if (listen(serverSocket, 1) != 0) {
        cerr << "Listening failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return WSAGetLastError();
    }

    SOCKADDR_IN addr_in;
    int size = sizeof(addr_in);
    SOCKET connectionSocket;

    while (true) {
        connectionSocket = accept(serverSocket, (SOCKADDR*)&addr_in, &size);
        if (connectionSocket == INVALID_SOCKET) {
            cerr << "Acceptance failed\n";
        }
        else {
            cout << "Соединение установлено\n\n";

            //menu(connectionSocket, studArr);

            ThreadParams params(connectionSocket, &studArr);
            DWORD thID;
            CreateThread(NULL, NULL, ThreadFunc, &params, NULL, &thID);
            //CreateThread(NULL, NULL, ThreadFunc, &connectionSocket, NULL, &thID);
        }
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

void menu(SOCKET& s, StudArray& studArr) {
    bool menu = 1;
    int choice;
    vector<char> bufRecv(BUFF_SIZE);

    while (menu) {
        Input::bufSend += "\nМеню работы с данными:\n"
            "1. Просмотр всех записей о студентах\n"
            "2. Добавить запись о студенте\n"
            "3. Редактировать запись о студенте\n"
            "4. Удалить запись о студенте\n"
            "5. Вывести всех студентов по первой букве\n"
            "0. Назад\n";

        choice = Input::inputNumber(s, 0, 5);
        system("cls");
        switch (choice)
        {
        case 1:
            studArr.showAll(s);
            break;
        case 2:
            studArr.add(s);
            break;
        case 3:
            studArr.edit(s);
            break;
        case 4:
            studArr.del(s);
            break;
        case 5:
            studArr.ind(s);
            break;
        case 0:
            menu = 0;
        }
    }
}

DWORD WINAPI ThreadFunc(LPVOID arrS) {
    ThreadParams params = ((ThreadParams*)arrS)[0];
    SOCKET s = params.socket;
    StudArray* studArr = params.studArr;

    menu(s, *studArr);

    closesocket(s);

    return 0;
}