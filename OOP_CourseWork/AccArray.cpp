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
	string login = Input::inputLogin("�����");
	for (auto& el : arrAcc) {
		if (login == el->getLogin()) {
			cout << "������� � ����� ������� ��� ����������. ����������� ���������\n";
			return;
		}
	}

	Account cur = Account(login);
	cur.setRole(role);
	cur.setSalt();
	cur.setHashPassword(Input::hashFunc(Input::inputPassword(), cur.getSalt()));
	arrAcc.push_back(make_unique<Account>(cur));
	cout << "����������� �������\n";

	IOFile::addAccountToFile(filename, cur);
}

void AccArray::showAll() const {
	string line(51, '-');

	cout << "������� ������������������ ���������\n";
	cout << line << endl;
	cout << "|" << setw(13) << "�����" << setw(2) << "|" << setw(7) << "�������" << setw(1) << "|"
		<< setw(13) << "���" << setw(7) << "|" << setw(5) << "����" << setw(2) << "|" << endl;
	cout << line << endl;

	for (auto& el : arrAcc) {
		cout << "|" << setw(13) << el->getLogin() << setw(2) << "|" << setw(6) << el->getSalt() << setw(2) << "|"
			<< setw(18) << el->getHash() << setw(2) << "|" << setw(6) << (el->getRole()?"admin":"user") << setw(1) << "|" << endl;
		cout << line << endl;
	}
}

void AccArray::del() {
	showAll();

	auto it = find("����� ��� ��������");
	if (it == arrAcc.end()) {
		cout << "��� �������� � ����� �������\n";
		return;
	}

	if ((*it)->getLogin() == getAccount().getLogin()) {
		cout << "�� �� ������ ������� ����������� �������\n";
		return;
	}

	cout << "�� �������, ��� ������ ������� ?\n";
	cout << "1. ��\n";
	cout << "0. ���\n";
	if (Input::inputNumber(0, 1)) {
		(*it).reset();
		arrAcc.erase(it);
		cout << "�������� ���������\n";

		IOFile::writeAccountToFile(filename, arrAcc);
	}
}

void AccArray::edit() {
	showAll();

	auto it = find("����� ��� ��������������");
	if (it == arrAcc.end()) {
		cout << "��� �������� � ����� �������\n";
		return;
	}
	
	Account copy = **it;
	bool menu = 1;
	short choice = 0;
	while (menu) {
		cout << "\n����� ��������������\n";
		cout << "1. �����\n";
		cout << "2. ����\n";
		cout << "0. ����� �� ��������������\n";

		choice = Input::inputNumber(0, 2);
		switch (choice) {
		case 1:
			copy.setLogin(Input::inputLogin("�����"));
			break;
		case 2:
			cout << "�������� ����\n";
			cout << "1. �����\n";
			cout << "0. ������������\n";
			copy.setRole(Input::inputNumber(0, 1));
			break;
		case 0:
			menu = 0;
		}
	}

	cout << "\n�� �������, ��� ������ ���������������?\n";
	cout << "1. ��\n";
	cout << "0. ���\n";
	if (Input::inputNumber(0, 1)) {
		(*it).reset();
		(*it) = make_unique<Account>(copy);
		cout << "�������������� ���������\n";

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
	string login = Input::inputLogin("����� ��� ������");

	for (auto& el: arrAcc) {
		if (login == el->getLogin()) {
			cout << *el;
		}
	}
}
