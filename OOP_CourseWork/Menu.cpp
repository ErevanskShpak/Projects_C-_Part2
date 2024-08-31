#include "Menu.h"

void Menu::menuAdminAcc(AccArray& accArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ������ � ����������:\n";
		cout << "1. ����������� ���������\n";
		cout << "2. �������� ���������\n";
		cout << "3. �������������� ���������\n";
		cout << "4. �������� ���������\n";
		cout << "5. ����� �������� �� ������\n";
		cout << "6. ���������� ��������� �� ����\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 6);
		system("cls");
		switch (choice)
		{
		case 1:
			Sign::signUpAdmin(accArr);
			break;
		case 2:
			accArr.showAll();
			break;
		case 3:
			accArr.edit();
			break;
		case 4:
			accArr.del();
			break;
		case 5:
			accArr.search();
			break;
		case 6:
			accArr.sortArr();
			break;
		case 0:
			menu = 0;
		}
	}
}

void Menu::menuAdminData(StudArray& studArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ������ � �������:\n";
		cout << "1. �������� ���� ������� � ���������\n";
		cout << "2. �������� ������ � ��������\n";
		cout << "3. ������������� ������ � ��������\n";
		cout << "4. ������� ������ � ��������\n";
		cout << "5. ������� ��� ������ � ��������� c ���������������\n";
		cout << "6. ������� ������� ���� ��������� ������������ ������\n";
		cout << "7. ����� ������� � ���������\n";
		cout << "8. ���������� ������� � ���������\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 8);
		system("cls");
		switch (choice)
		{
		case 1:
			studArr.showAll();
			break;
		case 2:
			studArr.add();
			break;
		case 3:
			studArr.edit();
			break;
		case 4:
			studArr.del();
			break;
		case 5:
			studArr.showDebt();
			break;
		case 6:
			studArr.showAvgOfGroup();
			break;
		case 7:
			menuSearch(studArr);
			break;
		case 8:
			menuSort(studArr);
			break;
		case 0:
			menu = 0;
		}
	}
}

void Menu::menuSort(StudArray& studArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ����������:\n";
		cout << "1. �� ��������\n";
		cout << "2. �� �������� �������� �����\n";
		cout << "3. �� ����������� ������ ������\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 3);
		system("cls");
		switch (choice) {
		case 1:
			studArr.sortFIO();
			break;
		case 2:
			studArr.sortAvgMark();
			break;
		case 3:
			studArr.sortGroup();
			break;
		case 0:
			menu = 0;
		}
	}
}

void Menu::menuSearch(StudArray& studArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ������:\n";
		cout << "1. �� ���\n";
		cout << "2. �� ������������ �������� �����\n";
		cout << "3. �� ������ ������\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 3);
		system("cls");
		switch (choice) {
		case 1:
			studArr.searchFIO();
			break;
		case 2:
			studArr.searchAvgMark();
			break;
		case 3:
			studArr.searchGroup();
			break;
		case 0:
			menu = 0;
		}
	}
}

void Menu::menuAdmin(AccArray& accArr, StudArray& studArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ��������������:\n";
		cout << "1. ������ � �������\n";
		cout << "2. ������ � ����������\n";
		cout << "0. ����� �� ��������\n";

		choice = Input::inputNumber(0, 2);
		system("cls");
		switch (choice) {
		case 1:
			menuAdminData(studArr);
			break;
		case 2:
			menuAdminAcc(accArr);
			break;
		case 0:
			menu = 0;
			break;
		}
	}
}

void Menu::menuUser(StudArray& studArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\n���� ������������:\n";
		cout << "1. �������� ���� ������� � ���������\n";
		cout << "2. ������� ��� ������ � ��������� c ���������������\n";
		cout << "3. ������� ������� ���� ��������� ������������ ������\n";
		cout << "4. ����� ������� � ���������\n";
		cout << "5. ���������� ������� � ���������\n";
		cout << "0. �����\n";

		choice = Input::inputNumber(0, 5);
		system("cls");
		switch (choice)
		{
		case 1:
			studArr.showAll();
			break;
		case 2:
			studArr.showDebt();
			break;
		case 3:
			studArr.showAvgOfGroup();
			break;
		case 4:
			menuSearch(studArr);
			break;
		case 5:
			menuSort(studArr);
			break;
		case 0:
			menu = 0;
		}
	}
}
