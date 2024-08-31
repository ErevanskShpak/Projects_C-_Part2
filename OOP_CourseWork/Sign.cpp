#include "Sign.h"

Account* Sign::signIn(AccArray& accArr) {
	string login = Input::inputLogin("�����");
	string password = Input::inputPassword();

	for (auto& el:accArr.getArr()) {
		if (el->getLogin() == login) {
			long long hash = Input::hashFunc(password, el->getSalt());
			if (el->getHash() == hash) {
				return el.get();
			}
		}
	}

	cout << "�������� ����� ��� ������, ���������� ������.\n";
	return nullptr;
}

void Sign::signUpAdmin(AccArray& accArr) {
	cout << "����� ����:\n";
	cout << "1. �����\n";
	cout << "0. ������������\n";

	accArr.add(Input::inputNumber(0, 1));
}

void Sign::signUpUser(AccArray& accArr) {
	accArr.add(0);
}

void Sign::firstSign(AccArray& accArr) {
	cout << "������� ������ �� ����������. �������� ���\n";
	accArr.add(1);
}
