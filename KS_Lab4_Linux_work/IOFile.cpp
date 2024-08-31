#include "IOFile.h"

void IOFile::readBookFromFile(const string& filename, list<Book>& arr) {
	ifstream fs(filename, ios::binary);
	if (!fs) {
		cout << "Невозможно открыть " << filename << endl;
		return;
	}
	string name, author;
	int date;
	size_t len;
	char* buf;

	while (fs.read(reinterpret_cast<char*>(&len), sizeof(len))) {
		buf = new char[len];
		fs.read(buf, len);
		name = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		author = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&date), sizeof(int));

		arr.push_back(Book(name, author, date));
	}
}

void IOFile::writeBookToFile(const string& filename, list<Book>& arr) {
	ofstream fs(filename, ios::trunc | ios::binary);
	string name, author;
	int date;
	size_t len;

	for (auto& cur : arr) {
		name = cur.getName();
		author = cur.getAuthor();
		date = cur.getDate();

		len = name.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(name.c_str()), len);

		len = author.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(author.c_str()), len);

		fs.write(reinterpret_cast<char*>(&date), sizeof(int));
	}
}

void IOFile::addBookToFile(const string& filename, Book& cur) {
	ofstream fs(filename, ios::binary | ios::app);
	string name = cur.getName(), author = cur.getAuthor();
	int date = cur.getDate();
	size_t len;

	len = name.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(name.c_str()), len);

	len = author.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(author.c_str()), len);

	fs.write(reinterpret_cast<char*>(&date), sizeof(int));
}
