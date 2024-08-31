#include <iostream>
#include <windows.h>
#include "Menu.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	AccArray accArr;
	StudArray studArr;
	if (!accArr.getArr().size()) {
		Sign::firstSign(accArr);
	}

	bool mainMenu = 1;
	short choice;
	while (mainMenu) {
		cout << "���������� ����� ������������ ���������|\n";
		cout << "----------------------------------------\n";
		cout << "������� ����:\n";
		cout << "1. �����������\n";
		cout << "2. ����\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 2);
		system("cls");
		switch (choice) {
		case 1:
			Sign::signUpUser(accArr);
			break;
		case 2: {
			Account* cur = Sign::signIn(accArr);
			if (cur) {
				if (cur->getRole() == 1) {
					accArr.setCur(*cur);
					Menu::menuAdmin(accArr, studArr);
				}
				else {
					Menu::menuUser(studArr);
				}
			}
		}
			break;
		case 0:
			mainMenu = 0;
		}
	}

	return 0;
}
