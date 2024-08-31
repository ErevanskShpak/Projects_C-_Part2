#pragma once
#include "IOFile.h"
#include <iomanip>
#include <sstream>

using namespace std;

class ArrayShape {
	static const string filename;
	list<Shape> arrShape;

	bool isEmpty() const;
	auto& find(SOCKET& s);
	void showTable(const list<Shape>&) const;
public:
	ArrayShape() {
		IOFile::readShapeFromFile(filename, arrShape);
	}

	void add(SOCKET& s);
	void showAll(SOCKET& s) const;
	void del(SOCKET& s);
	void edit(SOCKET& s);

	void sortName(SOCKET&);
	void sortSquare(SOCKET&);
	void sortPerimeter(SOCKET&);
	//Search:
	void searchName(SOCKET&) const;
	void searchSquare(SOCKET&) const;
	void searchPerimeter(SOCKET&) const;
};
