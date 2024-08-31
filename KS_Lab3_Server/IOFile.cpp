#include "IOFile.h"

void IOFile::readStudentFromFile(const string& filename, list<unique_ptr<Student>>& arr) {
	ifstream fs(filename, ios::binary);
	if (!fs) {
		cout << "Íåâîçìîæíî îòêğûòü " << filename << endl;
		return;
	}
	string surname, name, patronymic, group;
	map<string, int> marks;
	marks["ÊÑ"] = 1;
	marks["ÜÄ"] = 1;
	marks["ÒÂèÀ"] = 1;
	marks["ÑÏİ"] = 1;
	marks["ÎÎÏ"] = 1;
	size_t len;
	char* buf;

	while (fs.read(reinterpret_cast<char*>(&len), sizeof(len))) {
		buf = new char[len];
		fs.read(buf, len);
		surname = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		name = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		patronymic = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&len), sizeof(len));
		buf = new char[len];
		fs.read(buf, len);
		group = buf;
		delete[] buf;

		fs.read(reinterpret_cast<char*>(&(marks["ÊÑ"])), sizeof(int));
		fs.read(reinterpret_cast<char*>(&(marks["ÁÄ"])), sizeof(int));
		fs.read(reinterpret_cast<char*>(&(marks["ÒÂèÀ"])), sizeof(int));
		fs.read(reinterpret_cast<char*>(&(marks["ÑÏİ"])), sizeof(int));
		fs.read(reinterpret_cast<char*>(&(marks["ÎÎÏ"])), sizeof(int));

		arr.push_back(make_unique<Student>(Student(surname, name, patronymic, group, marks)));
	}
}

void IOFile::writeStudentToFile(const string& filename, list<unique_ptr<Student>>& arr) {
	ofstream fs(filename, ios::trunc | ios::binary);
	string surname, name, patronymic, group;
	map<string, int> marks;
	size_t len;

	for (auto& cur : arr) {
		surname = cur->getSurname();
		name = cur->getName();
		patronymic = cur->getPatronymic();
		group = cur->getGroup();
		marks = cur->getMarks();

		len = surname.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(surname.c_str()), len);

		len = name.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(name.c_str()), len);

		len = patronymic.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(patronymic.c_str()), len);

		len = group.length() + 1;
		fs.write(reinterpret_cast<char*>(&len), sizeof(len));
		fs.write(reinterpret_cast<const char*>(group.c_str()), len);

		fs.write(reinterpret_cast<char*>(&(marks["ÊÑ"])), sizeof(int));
		fs.write(reinterpret_cast<char*>(&(marks["ÁÄ"])), sizeof(int));
		fs.write(reinterpret_cast<char*>(&(marks["ÒÂèÀ"])), sizeof(int));
		fs.write(reinterpret_cast<char*>(&(marks["ÑÏİ"])), sizeof(int));
		fs.write(reinterpret_cast<char*>(&(marks["ÎÎÏ"])), sizeof(int));
	}
}

void IOFile::addStudentToFile(const string& filename, Student& cur) {
	ofstream fs(filename, ios::binary | ios::app);
	string surname = cur.getSurname();
	string name = cur.getName();
	string patronymic = cur.getPatronymic();
	string group = cur.getGroup();
	map<string, int> marks = cur.getMarks();
	size_t len;

	len = surname.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(surname.c_str()), len);

	len = name.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(name.c_str()), len);

	len = patronymic.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(patronymic.c_str()), len);

	len = group.length() + 1;
	fs.write(reinterpret_cast<char*>(&len), sizeof(len));
	fs.write(reinterpret_cast<const char*>(group.c_str()), len);

	fs.write(reinterpret_cast<char*>(&(marks["ÊÑ"])), sizeof(int));
	fs.write(reinterpret_cast<char*>(&(marks["ÁÄ"])), sizeof(int));
	fs.write(reinterpret_cast<char*>(&(marks["ÒÂèÀ"])), sizeof(int));
	fs.write(reinterpret_cast<char*>(&(marks["ÑÏİ"])), sizeof(int));
	fs.write(reinterpret_cast<char*>(&(marks["ÎÎÏ"])), sizeof(int));
}
