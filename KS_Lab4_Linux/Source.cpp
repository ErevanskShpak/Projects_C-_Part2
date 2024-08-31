#include "ArrayShape.h"

#define PORT 5678

void reaper(int sig);

void menu(int& s, ArrayShape& shapeArr);

int main() {
    ArrayShape shapeArr;

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

    if (listen(serverSocket, 1) != 0) {
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
            cout << "Соединение установлено\n\n";
            switch (fork()) {
            case 0:
                close(serverSocket);
                menu(connectionSocket, shapeArr); 
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


void menu(int& s, ArrayShape& shapeArr) {
    bool menu = 1;
    int choice;
    vector<char> bufRecv(BUFF_SIZE);

    while (menu) {
        Input::bufSend += "\nМеню работы с данными:\n"
            "1. Просмотр фигур\n"
            "2. Добавить фигуру\n"
            "3. Редактировать фигуру\n"
            "4. Удалить фигуру\n"
            "5. Сортировать фигуры по названию\n"
            "6. Сортировать фигуры по площади\n"
            "7. Сортировать фигуры по периметру\n"
            "8. Поиск по фигуры названию\n"
            "9. Поиск фигуры по площади\n"
            "10. Поиск фигуры по периметру\n"
            "0. Назад\n";

        choice = Input::inputNumber(s, 0, 10);
        switch (choice)
        {
        case 1:
            shapeArr.showAll(s);
            break;
        case 2:
            shapeArr.add(s);
            break;
        case 3:
            shapeArr.edit(s);
            break;
        case 4:
            shapeArr.del(s);
            break;
        case 5:
            shapeArr.sortName(s);
            break;
        case 6:
            shapeArr.sortSquare(s);
            break;
        case 7:
            shapeArr.sortPerimeter(s);
            break;
        case 8:
            shapeArr.searchName(s);
            break;
        case 9:
            shapeArr.searchSquare(s);
            break;
        case 10:
            shapeArr.searchPerimeter(s);
            break;
        case 0:
            menu = 0;
        }
    }
}
