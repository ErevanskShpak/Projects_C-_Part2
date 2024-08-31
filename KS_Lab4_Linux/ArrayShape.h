#pragma once
#include "IOFile.h"
#include <iomanip>
#include <sstream>

using namespace std;

class ArrayShape {
	static const string filename;
	list<Shape> arrShape;

	bool isEmpty() const;
	auto find(int& s);
	void showTable(const list<Shape>&) const;
public:
	ArrayShape() {
		IOFile::readShapeFromFile(filename, arrShape);
	}

	void add(int& s);
	void showAll(int& s) const;
	void del(int& s);
	void edit(int& s);

	void sortName(int&);
	void sortSquare(int&);
	void sortPerimeter(int&);
	//Search:
	void searchName(int&) const;
	void searchSquare(int&) const;
	void searchPerimeter(int&) const;
};
