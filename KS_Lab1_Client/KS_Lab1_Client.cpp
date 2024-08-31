#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <winsock2.h>
#include <iostream>
#include <string>

#define PORT 2077
#define ADDRESS "127.0.0.1"

using namespace std;

bool isNumberNumeric();
double inputNumber(string word);
bool isOperator(string input);
char inputOperator();

int main() {
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
        return WSAGetLastError();
    }

    if (connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        cerr << "Connection failed\n\n";
        return WSAGetLastError();
    }
    else {
        cout << "Connection succeeded\n";

        double first, second, res;
        char op;
        while (true) {
            try {
                first = inputNumber("first number");
                second = inputNumber("second number");
                op = inputOperator();
                if (op == '/' && second == 0) {
                    throw 1;
                }
                break;
            }
            catch (...) {
                cerr << "You can't divide by zero\n\n";
            }
        }

        send(clientSocket, (char*)&first, sizeof(first), 0);
        send(clientSocket, (char*)&second, sizeof(second), 0);
        send(clientSocket, &op, sizeof(op), 0);

        if (recv(clientSocket, (char*)&res, sizeof(res), 0) != 0) {
            cout << "Result: " << res << endl;
        }
        else {
            cerr << "The answer is lost\n";
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}

bool isNumberNumeric() {
    if (cin.get() == '\n') {
        return true;
    } else {
        cin.clear();
        cin.ignore(1024, '\n');
        return false;
    }
}

double inputNumber(string word) {
    cin.unsetf(ios::skipws);

    double number;
    while (true) {
        cout << "Input " << word << ": ";
        try {
            cin >> number;
            if (!isNumberNumeric()) {
                throw 1;
            }
            
            break;
        }
        catch (int) {
            cerr << "Incorrect input. Try more\n";
        }
        catch (...) {
            cerr << "Incorrect range. Try more\n";
        }
    }

    return number;
}

bool isOperator(string input) {
    if (input.length() != 1) {
        return false;
    }
    char symbol = input[0];
    if (!(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')) {
        return false;
    }

    return true;
}

char inputOperator() {
    cin.unsetf(ios::skipws);

    string input;
    while (true) {
        cout << "Input operator: ";
        try {
            getline(cin, input);
            if (!isOperator(input)) {
                throw 1;
            }

            break;
        }
        catch (...) {
            cerr << "Incorrect input. Operator must be only +, -, * or /\n";
        }
    }

    return input[0];
}