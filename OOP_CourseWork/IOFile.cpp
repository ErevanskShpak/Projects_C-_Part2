#include "IOFile.h"

void IOFile::readAccountFromFile(const string& filename, list<unique_ptr<Account>>& arr) {
	ifstream fs(filename, ios::binary);
	if (!fs) {
		cout << "���������� ������� " << filename << endl;
		return;
	}

	string login, salt;
	bool role;
	long long hash;
	size_t len;
	char* buf;
	while (fs.read(reinterpret_cast<char*>(&len), sizeof(len))) {
		buf = new char[len];
		fs.read(buf, len);
		login = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&role), sizeof(role));

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		salt = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&hash), sizeof(hash));

		arr.push_back(make_unique<Account>(Account(login, role, salt, hash)));
	}
}

void IOFile::writeAccountToFile(const string& filename, list<unique_ptr<Account>>& arr) {
	ofstream fs(filename, ios::trunc | ios::binary);
	string login, salt;
	bool role;
	long long hash;
	size_t len;

	for (auto& cur : arr) {
		login = cur->getLogin();
		role = cur->getRole();
		salt = cur->getSalt();
		hash = cur->getHash();

		len = login.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(login.c_str()), len);

		fs.write(reinterpret_cast<char*>(&role), sizeof(role));

		len = salt.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(salt.c_str()), len);

		fs.write(reinterpret_cast<char*>(&hash), sizeof(hash));
	}
}

void IOFile::addAccountToFile(const string& filename, Account& cur) {
	ofstream fs(filename, ios::binary | ios::app);
	string login = cur.getLogin();
	bool role = cur.getRole();
	string salt = cur.getSalt();
	long long hash = cur.getHash();
	size_t len;

	len = login.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(login.c_str()), len);

	fs.write(reinterpret_cast<char*>(&role), sizeof(role));
	
	len = salt.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(salt.c_str()), len);

	fs.write(reinterpret_cast<char*>(&hash), sizeof(hash));
}

void IOFile::readStudentFromFile(const string& filename, list<unique_ptr<Student>>& arr) {
	ifstream fs(filename, ios::binary);
	if (!fs) {
		cout << "���������� ������� " << filename << endl;
		return;
	}
	string surname, name, patronymic, group;
	map<string, short> marks;
	marks["����������"] = 1;
	marks["������"] = 1;
	marks["����"] = 1;
	marks["����"] = 1;
	marks["���"] = 1;
	float avg;
	map<string, bool> tests;
	tests["�����������"] = 1;
	tests["������"] = 1;
	tests["��"] = 1;
	tests["���"] = 1;
	tests["���"] = 1;
	short debt;
	size_t len;
	char* buf;

	while (fs.read(reinterpret_cast<char*>(&len), sizeof(len))) {
		buf = new char[len];
		fs.read(buf, len);
		surname = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		name = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		patronymic = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		group = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&(marks["����������"])), sizeof(short));
		fs.read(reinterpret_cast<char*>(&(marks["������"])), sizeof(short));
		fs.read(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
		fs.read(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
		fs.read(reinterpret_cast<char*>(&(marks["���"])), sizeof(short));

		fs.read(reinterpret_cast<char*>(&avg), sizeof(avg));
		
		fs.read(reinterpret_cast<char*>(&(tests["�����������"])), sizeof(bool));
		fs.read(reinterpret_cast<char*>(&(tests["������"])), sizeof(bool));
		fs.read(reinterpret_cast<char*>(&(tests["��"])), sizeof(bool));
		fs.read(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));
		fs.read(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));

		fs.read(reinterpret_cast<char*>(&debt), sizeof(debt));

		arr.push_back(make_unique<Student>(Student(surname, name, patronymic,
			group, marks, avg, tests, debt)));
	}
}

void IOFile::writeStudentToFile(const string& filename, list<unique_ptr<Student>>& arr) {
	ofstream fs(filename, ios::trunc | ios::binary);
	string surname, name, patronymic, group;
	map<string, short> marks;
	float avg;
	map<string, bool> tests;
	short debt;
	size_t len;

	for (auto& cur : arr) {
		surname = cur->getSurname();
		name = cur->getName();
		patronymic = cur->getPatronymic();
		group = cur->getGroup();
		marks = cur->getMarks();
		avg = cur->getAverage_mark();
		tests = cur->getTests();
		debt = cur->getDebt();

		len = surname.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(surname.c_str()), len);

		len = name.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(name.c_str()), len);

		len = patronymic.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(patronymic.c_str()), len);

		len = group.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(group.c_str()), len);

		fs.write(reinterpret_cast<char*>(&(marks["����������"])), sizeof(short));
		fs.write(reinterpret_cast<char*>(&(marks["������"])), sizeof(short));
		fs.write(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
		fs.write(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
		fs.write(reinterpret_cast<char*>(&(marks["���"])), sizeof(short));

		fs.write(reinterpret_cast<char*>(&avg), sizeof(avg));

		fs.write(reinterpret_cast<char*>(&(tests["�����������"])), sizeof(bool));
		fs.write(reinterpret_cast<char*>(&(tests["������"])), sizeof(bool));
		fs.write(reinterpret_cast<char*>(&(tests["��"])), sizeof(bool));
		fs.write(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));
		fs.write(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));

		fs.write(reinterpret_cast<char*>(&debt), sizeof(debt));
	}
}

void IOFile::addStudentToFile(const string& filename, Student& cur) {
	ofstream fs(filename, ios::binary | ios::app);
	string surname = cur.getSurname();
	string name = cur.getName();
	string patronymic = cur.getPatronymic();
	string group = cur.getGroup();
	map<string, short> marks = cur.getMarks();
	float avg = cur.getAverage_mark();
	map<string, bool> tests = cur.getTests();
	short debt = cur.getDebt();
	size_t len;

	len = surname.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(surname.c_str()), len);

	len = name.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(name.c_str()), len);

	len = patronymic.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(patronymic.c_str()), len);

	len = group.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(group.c_str()), len);
	
	fs.write(reinterpret_cast<char*>(&(marks["����������"])), sizeof(short));
	fs.write(reinterpret_cast<char*>(&(marks["������"])), sizeof(short));
	fs.write(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
	fs.write(reinterpret_cast<char*>(&(marks["����"])), sizeof(short));
	fs.write(reinterpret_cast<char*>(&(marks["���"])), sizeof(short));

	fs.write(reinterpret_cast<char*>(&avg), sizeof(avg));

	fs.write(reinterpret_cast<char*>(&(tests["�����������"])), sizeof(bool));
	fs.write(reinterpret_cast<char*>(&(tests["������"])), sizeof(bool));
	fs.write(reinterpret_cast<char*>(&(tests["��"])), sizeof(bool));
	fs.write(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));
	fs.write(reinterpret_cast<char*>(&(tests["���"])), sizeof(bool));

	fs.write(reinterpret_cast<char*>(&debt), sizeof(debt));
}
