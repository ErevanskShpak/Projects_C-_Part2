#include "Menu.h"

void Menu::menuAdminAcc(AccArray& accArr) {
	bool menu = 1;
	short choice;

	while (menu) {
		cout << "\nМеню работы с аккаунтами:\n";
		cout << "1. Регистрация аккаунтов\n";
		cout << "2. Просмотр аккаунтов\n";
		cout << "3. Редактирование аккаунтов\n";
		cout << "4. Удаление аккаунтов\n";
		cout << "5. Поиск аккаунта по логину\n";
		cout << "6. Сортировка аккаунтов по роли\n";
		cout << "0. Назад\n";

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
		cout << "\nМеню работы с данными:\n";
		cout << "1. Просмотр всех записей о студентах\n";
		cout << "2. Добавить запись о студенте\n";
		cout << "3. Редактировать запись о студенте\n";
		cout << "4. Удалить запись о студенте\n";
		cout << "5. Вывести все записи о студентах c задолженностями\n";
		cout << "6. Вывести средний балл студентов определенной группы\n";
		cout << "7. Поиск записей о студентах\n";
		cout << "8. Сортировка записей о студентах\n";
		cout << "0. Назад\n";

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
		cout << "\nМеню сортировки:\n";
		cout << "1. По алфавиту\n";
		cout << "2. По убыванию среднего балла\n";
		cout << "3. По возрастанию номера группы\n";
		cout << "0. Назад\n";

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
		cout << "\nМеню поиска:\n";
		cout << "1. По ФИО\n";
		cout << "2. По минимальному среднему баллу\n";
		cout << "3. По номеру группы\n";
		cout << "0. Назад\n";

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
		cout << "\nМеню администратора:\n";
		cout << "1. Работа с данными\n";
		cout << "2. Работа с аккаунтами\n";
		cout << "0. Выйти из аккаунта\n";

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
		cout << "\nМеню пользователя:\n";
		cout << "1. Просмотр всех записей о студентах\n";
		cout << "2. Вывести все записи о студентах c задолженностями\n";
		cout << "3. Вывести средний балл студентов определенной группы\n";
		cout << "4. Поиск записей о студентах\n";
		cout << "5. Сортировка записей о студентах\n";
		cout << "0. Назад\n";

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
