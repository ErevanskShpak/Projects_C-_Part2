#include "Student.h"

void Student::setMarks(SOCKET& s) {
	marks["��"] = Input::inputNumber(s, 1, 10, "������ �� ��");
	marks["��"] = Input::inputNumber(s, 1, 10, "������ �� ��");
	marks["����"] = Input::inputNumber(s, 1, 10, "������ �� ����");
	marks["���"] = Input::inputNumber(s, 1, 10, "������ �� ���");
	marks["���"] = Input::inputNumber(s, 1, 10, "������ �� ���");
}

void Student::setData(SOCKET& s) {
	setSurname(Input::inputFIO(s, "�������"));
	setName(Input::inputFIO(s, "���"));
	setPatronymic(Input::inputFIO(s, "��������"));
	setGroup(Input::inputGroup(s));
	setMarks(s);
}
