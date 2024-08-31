#include <glut.h>

using namespace std;

void background() {
	//glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1000, 0, 1000);
	//glClear(GL_COLOR_BUFFER_BIT);
}

void figure() {
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2i(0, 0);
	glVertex2i(1000, 1000);
	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Рисование линии");
	background();
	glutDisplayFunc(figure);
	glutMainLoop();
}
