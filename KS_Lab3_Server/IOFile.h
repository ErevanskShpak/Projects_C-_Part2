#pragma once
#include "Student.h"
#include <list>
#include <memory>
#include <fstream>

using namespace std;

namespace IOFile {
	void readStudentFromFile(const string&, list<unique_ptr<Student>>&);
	void writeStudentToFile(const string&, list<unique_ptr<Student>>&);
	void addStudentToFile(const string&, Student&);
}
