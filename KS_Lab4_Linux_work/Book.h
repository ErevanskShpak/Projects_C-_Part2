#pragma once
#include "Input.h"

using namespace std;

class Book {
	string name;
	string author;
	int date;
public:
	Book() :date(2000) {}
	Book(string name, string author, int date) {
		this->name = name;
		this->author = author;
		this->date = date;
	}

	void setName(string name) { this->name = name; }
	void setAuthor(string author) { this->author = author; }
	void setDate(int date) { this->date = date; }

	void setData(int& s);

	string getName() const { return name; }
	string getAuthor() const { return author; }
	int getDate() const { return date; }
};

