#include "Account.h"

void Account::setSalt() {
	srand(time(NULL));
	for (auto& el : salt) {
		el = (char)(rand() % 26 + 97);
	}
}

istream& operator>>(istream& cin, Account& acc) {
	acc.setLogin(Input::inputLogin("�����"));
	acc.setSalt();
	acc.setHashPassword(Input::hashFunc(Input::inputPassword(), acc.getSalt()));

	return cin;
}

ostream& operator<<(ostream& cout, Account& acc) {
	cout << "�����: " << acc.login;
	cout << "\n�������: " << acc.salt;
	cout << "\n������: " << acc.hash;
	cout << "\n����: " << (acc.role == 1 ? "admin" : "user") << endl;

	return cout;
}
