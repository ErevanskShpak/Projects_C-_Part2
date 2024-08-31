#pragma once
#include "Book.h"
#include <list>
#include <fstream>

using namespace std;

namespace IOFile {
	void readBookFromFile(const string&, list<Book>&);
	void writeBookToFile(const string&, list<Book>&);
	void addBookToFile(const string&, Book&);
}
