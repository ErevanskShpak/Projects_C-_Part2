#pragma once
#include "Shape.h"
#include <list>
#include <memory>
#include <fstream>

using namespace std;

namespace IOFile {
	void readShapeFromFile(const string&, list<Shape>&);
	void writeShapeToFile(const string&, list<Shape>&);
	void addShapeToFile(const string&, Shape&);
}
