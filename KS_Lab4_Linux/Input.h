#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include<sys/socket.h>
#include<sys/signal.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<netinet/in.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 1024

using namespace std;

class Input {
	static bool isNumberNumeric(string&);
	static bool isNumberRangeCorrect(int&, int&, int&);
	static bool isFIOCorrect(string&);
public:
	static string bufSend;

	static int inputNumber(int&, int = -1000, int = 1000, string = "выбор");
	static string inputFIO(int&, string);
};

