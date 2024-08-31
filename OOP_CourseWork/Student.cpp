#include "Student.h"

string Student::resToString(bool res) {
	return (res ? "����" : "�� ����");
}

void Student::setMarks() {
	marks["����������"] = Input::inputNumber(1, 10, "������ �� ����������");
	marks["������"] = Input::inputNumber(1, 10, "������ �� ������");
	marks["����"] = Input::inputNumber(1, 10, "������ �� ����");
	marks["����"] = Input::inputNumber(1, 10, "������ �� ����");
	marks["���"] = Input::inputNumber(1, 10, "������ �� ���");

	float avg = 0;
	for (auto el : marks) {
		avg += el.second;
	}
	avg /= 5;
	this->avgMark = avg;
}

void Student::setTests() {
	cout << "���� �������\n";
	cout << "����� - 1\n";
	cout << "������� - 0\n";

	tests["�����������"] = Input::inputNumber(0, 1, "����� �� �����������");
	tests["������"] = Input::inputNumber(0, 1, "����� �� ������");
	tests["��"] = Input::inputNumber(0, 1, "����� �� ��");
	tests["���"] = Input::inputNumber(0, 1, "����� �� ���");
	tests["���"] = Input::inputNumber(0, 1, "����� �� ���");

	short debt = 0;
	for (auto& el : tests) {
		if (!(el.second)) {
			debt++;
		}
	}
	this->debt = debt;
}

void Student::showPerformance() {
	cout << "������������� ����� ��������\n";
	string line(27, '-');
	cout << line << endl;
	cout << "|" << setw(12) << "�������" << setw(2) << "|"
		<< setw(10) << "���������" << setw(2) << "|" << endl;
	cout << line << endl;
	for (auto& mark : marks) {
		cout << "|" << setw(12) << mark.first << setw(2) << "|"
			<< setw(10) << mark.second << setw(2) << "|" << endl;
		cout << line << endl;
	}
	for (auto& test : tests) {
		cout << "|" << setw(12) << test.first << setw(2) << "|"
			<< setw(10) << (test.second ? "�����": "�������") << setw(2) << "|" << endl;
		cout << line << endl;
	}
	cout << "������� ����: " << avgMark << endl;
	cout << "���������� ������: " << debt << endl;
}

istream& operator>>(istream& cin, Student& stud) {
	stud.setSurname(Input::inputFIO("�������"));
	stud.setName(Input::inputFIO("���"));
	stud.setPatronymic(Input::inputFIO("��������"));
	stud.setGroup(Input::inputGroup());
	stud.setMarks();
	stud.setTests();

	return cin;
}
