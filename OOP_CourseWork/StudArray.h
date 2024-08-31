#pragma once
#include <list>
#include <memory>
#include <unordered_map>
#include "Student.h"
#include "Input.h"
#include "IOFile.h"

using namespace std;

class StudArray {
	static const string filename;
	list<unique_ptr<Student>> arrStud;

	bool isEmpty() const;
	auto find();
	void showTable(ostream&, const list<unique_ptr<Student>>&) const;
public:
	StudArray() {
		IOFile::readStudentFromFile(filename, arrStud);
	}

	void add();
	void showAll() const;
	void del();
	void edit();
	//Sorts:
	void sortFIO();
	void sortAvgMark();
	void sortGroup();
	//Search:
	void searchAvgMark() const;
	void searchFIO() const;
	void searchGroup() const;
	//Individual
	void showDebt();
	void showAvgOfGroup() const;
};

