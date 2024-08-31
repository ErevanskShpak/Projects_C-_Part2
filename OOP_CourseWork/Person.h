#pragma once
#include <iostream>
#include <string>

using namespace std;

class Person {
	string name;
	string surname;
	string patronymic;
public:
	Person() {}
	Person(string surname, string name, string patronymic):
		name(name), surname(surname), patronymic(patronymic) {}

	void setName(string word) { name = word; }
	void setSurname(string word) { surname = word; }
	void setPatronymic(string word) { patronymic = word; }

	string getName() { return name; }
	string getSurname() { return surname; }
	string getPatronymic() { return patronymic; }

	virtual void showPerformance() = 0;

	friend ostream& operator<<(ostream& sout, Person& pers) {
		cout << "\nÔÈÎ: " << pers.surname << " " << pers.name << " " << pers.patronymic << endl;
		pers.showPerformance();

		return sout;
	}
};
