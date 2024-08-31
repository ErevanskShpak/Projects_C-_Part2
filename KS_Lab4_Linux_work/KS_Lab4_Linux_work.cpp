#include "Library.h"

#define PORT 5678

void reaper(int sig);

void menu(int& s, Library& studArr);

int main() {
    Library studArr;

    sockaddr_in addr;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        cerr << "Creation failed\n";
        return 1;
    }

    if (bind(serverSocket, (sockaddr*)&addr, sizeof(addr)) != 0) {
        cerr << "Binding failed\n";
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 3) != 0) {
        cerr << "Listening failed\n";
        close(serverSocket);
        return 1;
    }

    sockaddr_in addr_in;
    int size = sizeof(addr_in);
    int connectionSocket;
    signal(SIGCHLD, reaper);
    while (true) {
        connectionSocket = accept(serverSocket, (sockaddr*)&addr_in, &size);
        if (connectionSocket == 0) {
            cerr << "Acceptance failed\n";
        }
        else {
            cout << "���������� �����������\n\n";
            switch (fork()) {
            case 0:
                close(serverSocket);
                menu(connectionSocket, studArr);
                close(connectionSocket);
                return 0;
            default:
                close(connectionSocket);
            }
        }
    }

    close(serverSocket);

    return 0;
}

void reaper(int sig) {
    int status;
    while (wait3(&status, WNOHANG, (rusage*)0) >= 0);
}


void menu(int& s, Library& studArr) {
    bool menu = 1;
    int choice;
    vector<char> bufRecv(BUFF_SIZE);

    while (menu) {
        Input::bufSend += "\n���� ������ � �������:\n"
            "1. �������� ���� ����\n"
            "2. �������� ������ � �����\n"
            "3. ������������� ������ � �����\n"
            "4. ������� ������ � �����\n"
            "5. ����������� �� �������� ����\n"
            "6. ����������� �� ������ ����\n"
            "7. ����������� �� ����������� ���� �������\n"
            "8. ����� �� ��������\n"
            "9. ����� �� ������\n"
            "10. ����� �� ���� �������\n"
            "0. �����\n";

        choice = Input::inputNumber(s, 0, 10);
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
            studArr.sortName(s);
            break;
        case 6:
            studArr.sortAuthor(s);
            break;
        case 7:
            studArr.sortDate(s);
            break;
        case 8:
            studArr.searchName(s);
            break;
        case 9:
            studArr.searchAuthor(s);
            break;
        case 10:
            studArr.searchDate(s);
            break;
        case 0:
            menu = 0;
        }
    }
}
