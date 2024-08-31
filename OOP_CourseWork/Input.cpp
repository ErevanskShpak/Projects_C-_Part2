#include "Input.h"

bool Input::isAccDataCorrect(string& input) {
	if (!(input.size() >= 3 && input.size() <= 13)) {
		return false;
	}

	for (auto& el : input) {
		if (el == ' ') {
			return false;
		}
	}

	return true;
}

bool Input::isNumberNumeric() {
	if (cin.get() == '\n') {
		return true;
	} else {
		cin.clear();
		cin.ignore(1024, '\n');
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

bool Input::isGroupCorrect(string& input) {
	if (input.length() != 6) {
		return false;
	}

	for (auto& symbol : input) {
		if (!(symbol >= '0' && symbol <= '9')) {
			return false;
		}
	}

	return true;
}

long long Input::hashFunc(string password, string salt) {
	password += salt;

	const short p = 31;
	long long hash = 0, p_pow = 1;
	for (auto& el : password) {
		hash += (el - 'a' + 1) * p_pow;
		p_pow *= p;
	}

	return hash;
}

string Input::inputLogin(string word) {
	string login;
	while (true) {
		cout << "������� " << word << ": ";
		try {
			getline(cin, login, '\n');
			if (!isAccDataCorrect(login)) {
				throw "incorrect input";
			}
			break;
		}
		catch (...) {
			cerr << "������������ ����, ����� ������ ���� �� 3 �� 13 �������� � �� ��������� ������\n";
		}
	}

	return login;
}

string Input::inputPassword() {
	string password;
	char c;
	while (true) {
		cout << "������� ������: ";
		try {
			while ((c = _getch()) != '\r') {
				if (c == '\b') {
					if (password.length() > 0) {
						password.pop_back();
						cout << "\b \b";
					}
				} else {
					password.push_back(c);
					cout << "*";
				}
			}
			if (!isAccDataCorrect(password)) {
				throw "incorrect input";
			}
			cout << endl;
			break;
		}
		catch (...) {
			cerr << "������������ ����, ������ ������ ���� �� 3 �� 13 �������� � �� ��������� ������\n";
			password.clear();
		}
	}

	return password;
}

string Input::inputFIO(string word) {
	string input;
	while (true) {
		cout << "������� " << word << ": ";
		try {
			getline(cin, input, '\n');
			if (!isFIOCorrect(input)) {
				throw 1;
			}
			break;
		}
		catch (...) {
			cout << "������������ ����, ����� ������ �������� ������ �� ���� �������� �������� � ���������� � ���������\n";
		}
	}

	return input;
}

string Input::inputGroup() {
	string input;
	while (true) {
		cout << "������� ������: ";
		try {
			getline(cin, input, '\n');
			if (!isGroupCorrect(input)) {
				throw 1;
			}
			break;
		}
		catch (...) {
			cout << "������������ ����, ������ ������ �������� �� 6 ����\n";
		}
	}

	return input;
}
