#include "AccArray.h"

const string AccArray::filename = "C:\\My_projects\\OOP_CourseWork\\Files\\accounts.bin";


auto AccArray::find(string word) {
	string loginSearch = Input::inputLogin(word);

	auto it = find_if(arrAcc.begin(), arrAcc.end(),
		[&](const unique_ptr<Account>& acc) {
			return acc->getLogin() == loginSearch;
		});

	return it;
}

void AccArray::add(bool role) {
	string login = Input::inputLogin("логин");
	for (auto& el : arrAcc) {
		if (login == el->getLogin()) {
			cout << "Аккаунт с таким логином уже существует. Регистрация провалена\n";
			return;
		}
	}

	Account cur = Account(login);
	cur.setRole(role);
	cur.setSalt();
	cur.setHashPassword(Input::hashFunc(Input::inputPassword(), cur.getSalt()));
	arrAcc.push_back(make_unique<Account>(cur));
	cout << "Регистрация успешна\n";

	IOFile::addAccountToFile(filename, cur);
}

void AccArray::showAll() const {
	string line(51, '-');

	cout << "Таблица зарегистрированных аккаунтов\n";
	cout << line << endl;
	cout << "|" << setw(13) << "Логин" << setw(2) << "|" << setw(7) << "Хешсоль" << setw(1) << "|"
		<< setw(13) << "Хеш" << setw(7) << "|" << setw(5) << "Роль" << setw(2) << "|" << endl;
	cout << line << endl;

	for (auto& el : arrAcc) {
		cout << "|" << setw(13) << el->getLogin() << setw(2) << "|" << setw(6) << el->getSalt() << setw(2) << "|"
			<< setw(18) << el->getHash() << setw(2) << "|" << setw(6) << (el->getRole()?"admin":"user") << setw(1) << "|" << endl;
		cout << line << endl;
	}
}

void AccArray::del() {
	showAll();

	auto it = find("логин для удаления");
	if (it == arrAcc.end()) {
		cout << "Нет аккаунта с таким логином\n";
		return;
	}

	if ((*it)->getLogin() == getAccount().getLogin()) {
		cout << "Вы не можете удалить собственный аккаунт\n";
		return;
	}

	cout << "Вы уверены, что хотите удалить ?\n";
	cout << "1. Да\n";
	cout << "0. Нет\n";
	if (Input::inputNumber(0, 1)) {
		(*it).reset();
		arrAcc.erase(it);
		cout << "Удаление завершено\n";

		IOFile::writeAccountToFile(filename, arrAcc);
	}
}

void AccArray::edit() {
	showAll();

	auto it = find("логин для редактирования");
	if (it == arrAcc.end()) {
		cout << "Нет аккаунта с таким логином\n";
		return;
	}
	
	Account copy = **it;
	bool menu = 1;
	short choice = 0;
	while (menu) {
		cout << "\nВыбор редактирования\n";
		cout << "1. Логин\n";
		cout << "2. Роль\n";
		cout << "0. Выйти из редактирования\n";

		choice = Input::inputNumber(0, 2);
		switch (choice) {
		case 1:
			copy.setLogin(Input::inputLogin("логин"));
			break;
		case 2:
			cout << "Выберите роль\n";
			cout << "1. Админ\n";
			cout << "0. Пользователь\n";
			copy.setRole(Input::inputNumber(0, 1));
			break;
		case 0:
			menu = 0;
		}
	}

	cout << "\nВы уверены, что хотите отредактировать?\n";
	cout << "1. Да\n";
	cout << "0. Нет\n";
	if (Input::inputNumber(0, 1)) {
		(*it).reset();
		(*it) = make_unique<Account>(copy);
		cout << "Редактирование завершено\n";

		IOFile::writeAccountToFile(filename, arrAcc);
	}
}

void AccArray::sortArr() {
	arrAcc.sort([](const unique_ptr<Account>& a, const unique_ptr<Account>& b) {
		if (a->getRole() != b->getRole()) {
			return a->getRole() > b->getRole();
		} else {
			return a->getLogin() < b->getLogin();
		}
		});

	showAll();
}

void AccArray::search() const {
	string login = Input::inputLogin("логин для поиска");

	for (auto& el: arrAcc) {
		if (login == el->getLogin()) {
			cout << *el;
		}
	}
}
