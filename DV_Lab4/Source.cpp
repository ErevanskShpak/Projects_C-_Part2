#include <glut.h>

void backgroundSettings();
void figure();
void setPixels(int x, int y, int x0, int y0);
void algorithmCircle(int x0, int y0, int r);

void main(int argc, char** argv) {
	glutInit(&argc, argv); // ������ ������ � API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // � ��� �� ���������
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("��������� �����");
	backgroundSettings();
	glPointSize(10);
	glutDisplayFunc(figure);
	glutMainLoop(); // ���� �������
}

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // � ��� �� ��������� ������
	glMatrixMode(GL_PROJECTION); // ������������� ���������
	gluOrtho2D(-20, 20, -10, 30); //������ ������������� ���������
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // �������� ����� �����
	glColor3f(1, 1, 1); // f ���������, ��� RGB �� 0 �� 1

	algorithmCircle(0, 9, 13);
}

void setPixels(int x, int y, int x0, int y0) {
	glBegin(GL_POINTS);
	glVertex2i(x0 + x, y0 + y);
	glVertex2i(x0 - x, y0 + y);
	glVertex2i(x0 + x, y0 - y);
	glVertex2i(x0 - x, y0 - y);

	glVertex2i(x0 + y, y0 + x);
	glVertex2i(x0 - y, y0 + x);
	glVertex2i(x0 + y, y0 - x);
	glVertex2i(x0 - y, y0 - x);
	glEnd();
	glFlush(); // �������� ���������� ������� OpenGl
}

void algorithmCircle(int x0, int y0, int r) {
	int p = 1 - r;
	int x = 0, y = r;
	while (x <= y) {
		setPixels(x, y, x0, y0);
		x++;
		if (p < 0) {
			p += 2 * x + 1;
		} else {
			y--;
			p += 2 * (x - y) + 1;
		}
	}
}