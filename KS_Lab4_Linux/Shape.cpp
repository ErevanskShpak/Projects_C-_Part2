#include "Shape.h"

void Shape::setData(int& s) {
	setName(Input::inputFIO(s, "�������� ������"));
	setSquare(Input::inputNumber(s, 0, 10000, "������� ������"));
	setPerimeter(Input::inputNumber(s, 0, 10000, "�������� ������"));
}
