#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include "Person.h"
#include "Input.h"

using namespace std;

class Student: public Person {
	string group;
	map<string, short> marks;
	float avgMark;
	map<string, bool> tests;
	short debt;

public:
	Student():avgMark(0), debt(0) {}
	Student(string surname, string name, string patronymic, string group,
		map<string, short> marks, float avg,
		map<string, bool> tests, short debt) : Person(surname, name, patronymic) {
		this->group = group;
		this->marks = marks;
		this->avgMark = avg;
		this->tests = tests;
		this->debt = debt;
	}

	static string resToString(bool);

	void setGroup(string group) { this->group = group; }
	void setMarks(map<string, short> marks) { this->marks = marks; }
	void setMarks();
	void setAverage_mark(float avg) { avgMark = avg; }
	void setTests(map<string, bool> tests) { this->tests = tests; }
	void setTests();
	void setDebt(short debt) { this->debt = debt; }

	string getGroup() { return group; }
	map<string, short> getMarks() { return marks; }
	float getAverage_mark() { return avgMark; }
	map<string, bool> getTests() { return tests; }
	short getDebt() { return debt; }

	void showPerformance() override;

	friend istream& operator>>(istream&, Student& );
};
