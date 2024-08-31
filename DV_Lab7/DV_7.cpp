#include <glut.h>

void backgroundSettings() {
	//glClearColor(1, 1, 1, 0); // и так по умолчанию черный
	glMatrixMode(GL_PROJECTION); // ортогональная плоскость
	gluOrtho2D(0, 100, 0, 100); //размер ортогональной плоскости
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // закрашивание окна изображения буфером цвета

	glShadeModel(GL_SMOOTH); //градация цвета
	glLineWidth(22);

	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2i(10, 10);

		glColor3f(1, 1, 0);
		glVertex2i(50, 10);
	glEnd();

	glFlush(); // ускоряет выполнение функций OpenGl
}

void main(int argc, char** argv) {
	glutInit(&argc, argv); // начало работы с API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // и так по умолчанию
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Рисование линии");
	backgroundSettings();
	glutDisplayFunc(figure);
	glutMainLoop(); // цикл рендера
}
