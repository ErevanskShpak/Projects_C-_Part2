#pragma once
#include "IOFile.h"
#include <iomanip>
#include <sstream>

using namespace std;

class Library {
	static const string filename;
	list<Book> arrBook;

	bool isEmpty() const;
	auto find(int& s);
	void showTable(const list<Book>&) const;
public:
	Library() {
		IOFile::readBookFromFile(filename, arrBook);
	}

	void add(int& s);
	void showAll(int& s) const;
	void del(int& s);
	void edit(int& s);

	void sortName(int&);
	void sortAuthor(int&);
	void sortDate(int&);
	//Search:
	void searchName(int&) const;
	void searchAuthor(int&) const;
	void searchDate(int&) const;
};
