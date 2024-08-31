#pragma once
#include "IOFile.h"
#include <iomanip>
#include <sstream>

using namespace std;

class StudArray {
	static const string filename;
	list<unique_ptr<Student>> arrStud;

	bool isEmpty() const;
	auto find(SOCKET& s);
public:
	StudArray() {
		IOFile::readStudentFromFile(filename, arrStud);
	}

	void add(SOCKET& s);
	void showAll(SOCKET& s) const;
	void del(SOCKET& s);
	void edit(SOCKET& s);

	void ind(SOCKET& s);
};
