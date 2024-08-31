// (0, 10); (20, 20); (20,40); (30,20); (20,0).
#include <stdlib.h>
#include <cmath>
#include <windows.h>
#include <glut.h>
#include <algorithm>
#include <vector>
#include <iostream>

void setLine(int, int, int, int);
int sign(int, int);
void setPixel(int, int);
void lineBrasenhem(int, int, int, int, std::vector <std::pair<int, int>>&);
void lineDraw(int, int, int, int);
void paint();
void display();
void init();

int main(int supra, char** mega) {
	glutInit(&supra, mega);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Ћаба");

	init();
	glPointSize(10);
	glutDisplayFunc(display);
	glutMainLoop();
}

void setLine(int x, int y, int x1, int y1) {
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x1, y1);
	glEnd();
	glFlush();
}

int sign(int a, int b) {
	int d = b - a;

	if (d > 0) {
		return 1;
	}
	else if (d < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void lineBrasenhem(int x0, int y0, int xend, int yend, std::vector <std::pair<int, int>>& points) {
	int dx = abs(xend - x0), dy = abs(yend - y0), err;
	int x = x0, y = y0, yk = sign(y0, yend), xk = sign(x0, xend);
	bool is_swap = false;

	if (dy > dx) {
		std::swap(dx, dy);
		is_swap = true;
	}

	err = 2 * dy - dx;

	for (int i = 0; i <= dx; i++) {
		setPixel(x, y);
		points.push_back(std::make_pair(x, y));

		while (err >= 0) {
			if (is_swap) {
				x += xk;
			}
			else {
				y += yk;
			}

			err -= 2 * dx;
		}

		if (is_swap) {
			y += yk;
		}
		else {
			x += xk;
		}

		err += 2 * dy;
	}

}

void lineDraw(int x0, int y0, int xend, int yend) {
	int startx = 0, finishx = 0;

	if (x0 > xend) {
		startx = xend;
		finishx = x0;
	}
	else {
		startx = x0;
		finishx = xend;
	}

	while (startx < finishx) {
		setPixel(startx, y0);

		startx++;
	}
}

void paint() {
	std::vector<std::pair<int, int>> vertexes = { {10, 10}, {50, 10}, {50, 30}, {40, 10}, {30, 20} };
	//std::vector <std::pair<int, int>> vertexes = { {0, 10}, {20, 20}, {20, 40}, {30, 20}, {20, 0} };
	std::vector <std::pair<int, int>> points;

	vertexes.push_back(std::make_pair(10, 10)); // вставка начальной вершины дл€ прохода по рЄбрам

	for (int i = 0; i < vertexes.size() - 1; i++) {
		lineBrasenhem(vertexes[i].first, vertexes[i].second, vertexes[i + 1].first, vertexes[i + 1].second, points);
	}

	/*for (int i = 0; i < points.size() - 1; i++) {
		setLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
	}*/

	std::sort(points.begin(), points.end(), [](auto a, auto b) { return a.second < b.second; });

	for (int i = 0; i < points.size() - 1; i++) {
		if (points[i].second == points[i + 1].second) {
			if (points[i].first >= points[i + 1].first + 1 || points[i + 1].first + 1 >= points[i].first) {
				//setLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
				lineDraw(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second);
			}
		}
	}
}

void init() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-20, 80, -20, 80);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);

	/*glBegin(GL_LINE_LOOP);
		glVertex2i(0, 10);
		glVertex2i(20, 20);
		glVertex2i(20, 40);
		glVertex2i(30, 20);
		glVertex2i(20, 0);
	glEnd();
	glFlush();*/

	paint();
}

/*
foreach( ребро (x1, y1) - (x2, y2) in ћножество–ебер )
{
	  y = ceil(y1); // ќкругление до большего
	  dx = (x2 - x1)/(y2 - y1);
	  x = x1 + dx*(y - y1);

	  while(y <= y2)
	  {
			PutToList(x, y); // поместить x в список,
								  // соответствующий данному y
			y++;
			x += dx;
	  }
}
*/