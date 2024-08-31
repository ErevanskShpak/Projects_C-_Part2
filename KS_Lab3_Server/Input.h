#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>

#define BUFF_SIZE 1024

using namespace std;

class Input {
	static bool isNumberNumeric(string&);
	static bool isNumberRangeCorrect(int&, int&, int&);
	static bool isFIOCorrect(string&);
	static bool isGroupCorrect(string&);
	static bool isSymbolCorrect(string&);
public:
	static string bufSend;

	static int inputNumber(SOCKET&, int = -INT_MAX , int = INT_MAX, string = "выбор");
	static string inputFIO(SOCKET&, string);
	static string inputGroup(SOCKET&);
	static char inputSymbol(SOCKET&);
};

