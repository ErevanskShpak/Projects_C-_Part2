#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>
//#include <sys/types.h>
//#include<sys/socket.h>
//#include<sys/signal.h>
//#include<sys/wait.h>
//#include<sys/resource.h>
//#include<netinet/in.h>

#define BUFF_SIZE 1024

using namespace std;

class Input {
	static bool isNumberNumeric(string&);
	static bool isNumberRangeCorrect(int&, int&, int&);
	static bool isFIOCorrect(string&);
public:
	static string bufSend;

	static int inputNumber(SOCKET&, int = -1000, int = 1000, string = "выбор");
	static string inputFIO(SOCKET&, string);
};

