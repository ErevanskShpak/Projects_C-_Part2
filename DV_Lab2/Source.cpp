#include <glut.h>

void backgroundSettings();
void figure();
void setPixel(int x, int y);
int roundK(const float a);
void lineCDA(int x0, int y0, int xE, int yE);

void main(int argc, char** argv) {
	glutInit(&argc, argv); // ������ ������ � API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // � ��� �� ���������
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1800, 1000);
	glutCreateWindow("��������� �����");
	backgroundSettings();
	glPointSize(10);
	glutDisplayFunc(figure);
	glutMainLoop(); // ���� �������
}

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // � ��� �� ��������� ������
	glMatrixMode(GL_PROJECTION); // ������������� ���������
	gluOrtho2D(-10, 18, -10, 10); //������ ������������� ���������
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // �������� ����� �����
	glColor3f(1, 1, 1); // f ���������, ��� RGB �� 0 �� 1
	lineCDA(-5, -9, 4 ,4);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush(); // �������� ���������� ������� OpenGl
}

int absK(int a) {
	return (a < 0) ? (-1) * a : a;
}

int roundK(const float a) {
	return (a < 0) ? int(a - 0.5) : int(a + 0.5);
}

void lineCDA(int x0, int y0, int xE, int yE) {
	int dx = xE - x0, dy = yE - y0;
	int step = (absK(dx) > absK(dy)) ? absK(dx) : absK(dy);
	float xInc = float(dx) / float(step), yInc = float(dy) /float(step);
	float x = x0, y = y0;

	for (int i = 0; i < step + 1; ++i) {
		setPixel(roundK(x), roundK(y));
		x += xInc;
		y += yInc;
	}
}