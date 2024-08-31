#pragma once
#include <list>
#include <memory>
#include <iomanip>
#include "Account.h"
#include "Input.h"
#include "IOFile.h"

using namespace std;

class AccArray {
	static const string filename;
	list<unique_ptr<Account>> arrAcc;
	Account current;

	auto find(string);
	Account getAccount() { return current; }
public:
	AccArray() {
		IOFile::readAccountFromFile(filename, arrAcc);
	}

	void setCur(Account current) { this->current = current; }
	list<unique_ptr<Account>>& getArr() { return arrAcc; }

	void add(bool); 
	void showAll() const; 
	void del(); 
	void edit();      
	void sortArr();
	void search() const;
};
