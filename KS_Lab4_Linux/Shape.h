#pragma once
#include "Input.h"

using namespace std;

class Shape {
	string name;
	int square;
	int perimeter;
public:
	Shape() :square(2000), perimeter(200) {}
	Shape(string name, int square, int perimeter) {
		this->name = name;
		this->square = square;
		this->perimeter = perimeter;
	}

	void setName(string name) { this->name = name; }
	void setSquare(int square) { this->square = square; }
	void setPerimeter(int perimeter) { this->perimeter = perimeter; }

	void setData(int& s);

	string getName() const { return name; }
	int getSquare() const { return square; }
	int getPerimeter() const { return perimeter; }
};

