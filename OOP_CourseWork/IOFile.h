#pragma once
#include <list>
#include <memory>
#include <fstream>
#include "Account.h"
#include "Student.h"

using namespace std;

namespace IOFile {
	void readAccountFromFile(const string&, list<unique_ptr<Account>>&);
	void writeAccountToFile(const string&, list<unique_ptr<Account>>&);
	void addAccountToFile(const string&, Account&);

	void readStudentFromFile(const string&, list<unique_ptr<Student>>&);
	void writeStudentToFile(const string&, list<unique_ptr<Student>>&);
	void addStudentToFile(const string&, Student&);
}
