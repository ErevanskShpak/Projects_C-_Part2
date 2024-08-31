#include <glut.h>

void backgroundSettings() {
	//glClearColor(1, 1, 1, 0); // � ��� �� ��������� ������
	glMatrixMode(GL_PROJECTION); // ������������� ���������
	gluOrtho2D(0, 100, 0, 100); //������ ������������� ���������
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // ������������ ���� ����������� ������� �����

	glShadeModel(GL_SMOOTH); //�������� �����
	glLineWidth(22);

	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2i(10, 10);

		glColor3f(1, 1, 0);
		glVertex2i(50, 10);
	glEnd();

	glFlush(); // �������� ���������� ������� OpenGl
}

void main(int argc, char** argv) {
	glutInit(&argc, argv); // ������ ������ � API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // � ��� �� ���������
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("��������� �����");
	backgroundSettings();
	glutDisplayFunc(figure);
	glutMainLoop(); // ���� �������
}
