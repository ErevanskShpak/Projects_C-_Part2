#include "IOFile.h"

void IOFile::readShapeFromFile(const string& filename, list<Shape>& arr) {
	ifstream fs(filename, ios::binary);
	if (!fs) {
		cout << "Невозможно открыть " << filename << endl;
		return;
	}
	string name;
	int square, perimeter;
	size_t len;
	char* buf;

	while (fs.read(reinterpret_cast<char*>(&len), sizeof(len))) {
		buf = new char[len];
		fs.read(buf, len);
		name = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&square), sizeof(int));
		fs.read(reinterpret_cast<char*>(&perimeter), sizeof(int));

		arr.push_back(Shape(name, square, perimeter));
	}
}

void IOFile::writeShapeToFile(const string& filename, list<Shape>& arr) {
	ofstream fs(filename, ios::trunc | ios::binary);
	string name;
	int square, perimeter;
	size_t len;

	for (auto& cur : arr) {
		name = cur.getName();
		square = cur.getSquare();
		perimeter = cur.getPerimeter();

		len = name.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(name.c_str()), len);

		fs.write(reinterpret_cast<char*>(&square), sizeof(int));
		fs.write(reinterpret_cast<char*>(&perimeter), sizeof(int));
	}
}

void IOFile::addShapeToFile(const string& filename, Shape& cur) {
	ofstream fs(filename, ios::binary | ios::app);
	string name = cur.getName();
	int square = cur.getSquare(), perimeter = cur.getPerimeter();
	size_t len;

	len = name.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(name.c_str()), len);

	fs.write(reinterpret_cast<char*>(&square), sizeof(int));
	fs.write(reinterpret_cast<char*>(&perimeter), sizeof(int));
}
