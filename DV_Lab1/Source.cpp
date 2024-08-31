#include <glut.h>

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // � ��� �� ��������� ������
	glMatrixMode(GL_PROJECTION); // ������������� ���������
	gluOrtho2D(0, 200, 0, 400); //������ ������������� ���������
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // �������� ����� �����
	glColor3f(1, 1, 1); // f ���������, ��� RGB �� 0 �� 1
	glBegin(GL_QUADS);
	glVertex2i(20, 20);
	glVertex2i(20, 180);
	glVertex2i(180, 180);
	glVertex2i(180, 20);
	glVertex2i(160, 140);
	glEnd();
	glFlush(); // �������� ���������� ������� OpenGl
}

void main(int argc, char** argv) {
	glutInit(&argc, argv); // ������ ������ � API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // � ��� �� ���������
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(200, 400);
	glutCreateWindow("��������� �����");
	backgroundSettings();
	glutDisplayFunc(figure);
	glutMainLoop(); // ���� �������
}
