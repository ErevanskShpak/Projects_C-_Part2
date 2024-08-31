#include <glut.h>

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // и так по умолчанию черный
	glMatrixMode(GL_PROJECTION); // ортогональная плоскость
	gluOrtho2D(0, 200, 0, 400); //размер ортогональной плоскости
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // сбросить буфер цвета
	glColor3f(1, 1, 1); // f указывает, что RGB от 0 до 1
	glBegin(GL_QUADS);
	glVertex2i(20, 20);
	glVertex2i(20, 180);
	glVertex2i(180, 180);
	glVertex2i(180, 20);
	glVertex2i(160, 140);
	glEnd();
	glFlush(); // ускоряет выполнение функций OpenGl
}

void main(int argc, char** argv) {
	glutInit(&argc, argv); // начало работы с API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // и так по умолчанию
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(200, 400);
	glutCreateWindow("Рисование линии");
	backgroundSettings();
	glutDisplayFunc(figure);
	glutMainLoop(); // цикл рендера
}
