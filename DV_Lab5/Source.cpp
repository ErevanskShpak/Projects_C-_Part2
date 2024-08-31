#include <iostream>
#include <glut.h>

void backgroundSettings();
void figure();
void setPixels(int x, int y, int x0, int y0);
void algorithmEllipse(int x0, int y0, int rX, int rY);

void main(int argc, char** argv) {
	glutInit(&argc, argv); // начало работы с API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // и так по умолчанию
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Рисование круга");
	backgroundSettings();
	glPointSize(25);
	glutDisplayFunc(figure);
	glutMainLoop(); // цикл рендера
}

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // и так по умолчанию черный
	glMatrixMode(GL_PROJECTION); // ортогональная плоскость
	gluOrtho2D(-20, 20, -10, 30); //размер ортогональной плоскости
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // сбросить буфер цвета
	glColor3f(1, 1, 1); // f указывает, что RGB от 0 до 1

	algorithmEllipse(0, 9, 13, 6);
}

void setPixels(int x, int y, int x0, int y0) {
	glBegin(GL_POINTS);
	glVertex2i(x0 + x, y0 + y);
	glVertex2i(x0 - x, y0 + y);
	glVertex2i(x0 + x, y0 - y);
	glVertex2i(x0 - x, y0 - y);

	glEnd();
	glFlush(); // ускоряет выполнение функций OpenGl
}

void algorithmEllipse(int x0, int y0, int rY, int rX) {
	int x = 0, y = rY;
	const float c = (rY * rY) / (rX * rX);

	float p = rY * rY - rX * rX * rY + 0.25 * rX * rX;
	setPixels(x, y, x0, y0);
	while (c * x < y) {
		x++;
		if (p < 0) {
			p += rY * rY * (2 * x + 1);
		} else {
			y--;
			p += rY * rY * (2 * x + 1) - 2 * rX * rX * y;
		}
		setPixels(x, y, x0, y0);
	}

	p = rY * rY * (x + 0.5) * (x + 0.5) + rX * rX * (y - 1) * (y - 1) - rX * rX * rY * rY;
	while (y > 0) {
		y--;
		if (p > 0) {
			p += rX * rX * (1 - 2 * y);
		} else {
			x++;
			p += rX * rX * (1 - 2 * y) + 2 * rY * rY * x;
		}
		setPixels(x, y, x0, y0);
	}
}