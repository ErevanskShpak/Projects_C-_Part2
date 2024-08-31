#pragma once
#include "Input.h"
#include <map>

using namespace std;

class Student{
	string name;
	string surname;
	string patronymic;

	string group;
	int scholarship;
	map<string, int> marks;
public:
	Student():scholarship(0) {}
	Student(string surname, string name, string patronymic, string group, map<string, int> marks) {
		this->name = name;
		this->surname = surname;
		this->patronymic = patronymic;
		this->group = group;
		this->marks = marks;
	}

	void setName(string name) { this->name = name; }
	void setSurname(string surname) { this->surname = surname; }
	void setPatronymic(string patronymic) { this->patronymic = patronymic; }
	void setGroup(string group) { this->group = group; }
	void setMarks(map<string, int> marks) { this->marks = marks; }

	void setData(SOCKET& s);
	void setMarks(SOCKET& s);

	string getName() { return name; }
	string getSurname() { return surname; }
	string getPatronymic() { return patronymic; }
	string getGroup() { return group; }
	map<string, int> getMarks() { return marks; }
};

