#include "Input.h"

string Input::bufSend = "";

bool Input::isNumberNumeric(string& buf) {
	for (char cur : buf) {
		if (!(cur >= '0' && cur <= '9')) {
			return false;
		}
	}

	return true;
}

bool Input::isNumberRangeCorrect(int& number, int& leftR, int& rightR) {
	if ((number >= leftR) && (number <= rightR)) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::isFIOCorrect(string& input) {
	if (!(input[0] >= '�' && input[0] <= '�')) {
		return false;
	}

	for (int i = 1; i < input.size(); ++i) {
		if (!(input[i] >= '�' && input[i] <= '�')) {
			return false;
		}
	}

	return true;
}

int Input::inputNumber(SOCKET& s, int leftR, int rightR, string word) {
	int number, length;
	vector<char> bufRecv(BUFF_SIZE);
	string res;
	while (true) {
		bufSend += "������� " + word + ": ";
		length = strlen(bufSend.c_str());
		send(s, (char*)&length, sizeof(length), 0);
		send(s, bufSend.c_str(), length, 0);
		bufSend = "";
		try {
			recv(s, bufRecv.data(), bufRecv.size(), 0);
			res = bufRecv.data();
			bufRecv.clear();
			bufRecv.resize(1024);

			if (!isNumberNumeric(res)) {
				throw 1;
			}
			number = stoi(res.c_str());
			if (!isNumberRangeCorrect(number, leftR, rightR)) {
				throw "incorrect range";
			}
			break;
		}
		catch (int) {
			bufSend += "������������ ����. ��������� �������\n";
		}
		catch (...) {
			bufSend += "������������ �������� �����. ��������� �������\n";
		}
	}

	return number;
}

string Input::inputFIO(SOCKET& s, string word) {
	int length;
	string input;
	vector<char> bufRecv(BUFF_SIZE);
	while (true) {
		bufSend += "������� " + word + ": ";
		length = strlen(bufSend.c_str());
		send(s, (char*)&length, sizeof(length), 0);
		send(s, bufSend.c_str(), length, 0);
		bufSend = "";
		try {
			recv(s, bufRecv.data(), bufRecv.size(), 0);
			input = bufRecv.data();
			bufRecv.clear();
			bufRecv.resize(1024);

			if (!isFIOCorrect(input)) {
				throw 1;
			}
			break;
		}
		catch (...) {
			bufSend += "������������ ����, ����� ������ �������� ������ �� ���� �������� �������� � ���������� � ���������\n";
		}
	}

	return input;
}
