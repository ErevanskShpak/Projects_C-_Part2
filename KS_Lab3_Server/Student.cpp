#include "Student.h"

void Student::setMarks(SOCKET& s) {
	marks["КС"] = Input::inputNumber(s, 1, 10, "оценку по КС");
	marks["БД"] = Input::inputNumber(s, 1, 10, "оценку по БД");
	marks["ТВиА"] = Input::inputNumber(s, 1, 10, "оценку по ТВиА");
	marks["СПЭ"] = Input::inputNumber(s, 1, 10, "оценку по СПЭ");
	marks["ООП"] = Input::inputNumber(s, 1, 10, "оценку по ООП");
}

void Student::setData(SOCKET& s) {
	setSurname(Input::inputFIO(s, "фамилию"));
	setName(Input::inputFIO(s, "имя"));
	setPatronymic(Input::inputFIO(s, "отчество"));
	setGroup(Input::inputGroup(s));
	setMarks(s);
}
