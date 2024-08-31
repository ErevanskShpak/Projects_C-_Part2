#pragma once
#include <iostream>
#include <string>
#include "Input.h"

using namespace std;

class Account {
	string login;
	bool role;
	string salt;
	long long hash;
public:
	Account():role(0), salt(5, ' '), hash(0) {}
	Account(string login): login(login), salt(5, ' '), hash(0), role(0) {}
	Account(string login, bool role, string salt, long long hash) : login(login), role(role), salt(salt), hash(hash) {}

	void setLogin(string login) { this->login = login; }
	void setRole(bool role) { this->role = role; }
	void setSalt();
	void setHashPassword(long long hash) { this->hash = hash; }

	string getLogin() const { return login; }
	bool getRole() const { return role; }
	string getSalt() const { return salt; }
	long long getHash() const { return hash; }

	friend istream& operator>>(istream& cin, Account& acc);
	friend ostream& operator<<(ostream& cout, Account& acc);
};
