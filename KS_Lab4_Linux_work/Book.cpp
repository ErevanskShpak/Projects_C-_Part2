#include "Book.h"

void Book::setData(int& s) {
	setName(Input::inputFIO(s, "�������� �����"));
	setAuthor(Input::inputFIO(s, "������ �����"));
	setDate(Input::inputNumber(s, 1800, 2025, "��� �������"));
}
