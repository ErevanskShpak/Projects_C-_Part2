#include <cmath>
#include <glut.h>

void backgroundSettings();
void figure();
void setPixel(int x, int y);
int roundK(const float a);
void algorithmBrezenhema(int x0, int y0, int xE, int yE);

void main(int argc, char** argv) {
	glutInit(&argc, argv); // ������ ������ � API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // � ��� �� ���������
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1800, 1000);
	glutCreateWindow("��������� ����� �����������");
	backgroundSettings();
	glPointSize(10);
	glutDisplayFunc(figure);
	glutMainLoop(); // ���� �������
}

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // � ��� �� ��������� ������
	glMatrixMode(GL_PROJECTION); // ������������� ���������
	gluOrtho2D(-18, 18, -10, 10); //������ ������������� ���������
}

void figure() {
	//glClear(GL_COLOR_BUFFER_BIT); // �������� ����� �����
	glColor3f(1, 1, 1); // f ���������, ��� RGB �� 0 �� 1

	algorithmBrezenhema(0, 0, 3, 8);
	algorithmBrezenhema(0, 0, -3, 8);
	algorithmBrezenhema(0, 0, -3, -8);
	algorithmBrezenhema(0, 0, 3, -8);
	algorithmBrezenhema(0, 0, 8, 3);
	algorithmBrezenhema(0, 0, 8, -3);
	algorithmBrezenhema(0, 0, -8, -3);
	algorithmBrezenhema(0, 0, -8, 3);
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

void algorithmBrezenhema(int x0, int y0, int xE, int yE) {
	int dx = abs(xE - x0), dy = abs(yE - y0);
	int step = (dx > dy) ? dx : dy;
	int xInc = (xE - x0) / dx, yInc = (yE - y0) / dy;
	int x = x0, y = y0;

	int p = (dx > dy) ? (2 * dy - dx) : (2 * dx - dy);

	for (int i = 0; i < step + 1; ++i) {
		setPixel(x, y);

		if (dx > dy) {
			x += xInc;
			if (p < 0) {
				p += 2 * dy;
			}
			else {
				y += yInc;
				p += 2 * (dy - dx);
			}
		}
		else {
			y += yInc;
			if (p < 0) {
				p += 2 * dx;
			}
			else {
				x += xInc;
				p += 2 * (dx - dy);
			}
		}
	}
}