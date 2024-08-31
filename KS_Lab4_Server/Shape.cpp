#include "Shape.h"

void Shape::setData(SOCKET& s) {
	setName(Input::inputFIO(s, "название фигуры"));
	setSquare(Input::inputNumber(s, 0, 10000, "площадь фигуры"));
	setPerimeter(Input::inputNumber(s, 0, 10000, "периметр фигуры"));
}
