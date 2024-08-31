#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <glut.h>

using namespace std;

#define SCALE 1

void backgroundSettings();
void display();
void showWhich(vector<pair<int, int>>& vertexes);
void figure(vector<pair<int, int>>& vertexes);
void algorithmBrezenhema(int x0, int y0, int xE, int yE, vector<pair<int, int>>& points);
void setPixel(int x, int y);
void drawHorizontalLine(int x0, int xE, int y);

void main(int argc, char** argv) {
	setlocale(LC_ALL, "ru");

	glutInit(&argc, argv); // начало работы с API
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // и так по умолчанию
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Рисование круга");
	backgroundSettings();
	glPointSize(10 / SCALE);
	glutDisplayFunc(display);
	glutMainLoop(); // цикл рендера
}

void backgroundSettings() {
	//glClearColor(0, 0, 0, 0); // и так по умолчанию черный
	glMatrixMode(GL_PROJECTION); // ортогональная плоскость
	gluOrtho2D((-20) * SCALE, 80 * SCALE, (-20) * SCALE, 80 * SCALE); //размер ортогональной плоскости
}

void display() {
	vector <pair<int, int>> vertexes = { {0, 0}, { 20, 20 }, { 20, 40 }, { 30, 20 }, { 20, 10 } }; // 15 вариант
	//vector<pair<int, int>> vertexes = { {10, 10}, {50, 10}, {50, 30}, {40, 10}, {30, 20} }; // 1 вариант
	//vector<pair<int, int>> vertexes = { {0, 0}, {0, 50}, {10, 0}, {10, 30}, {20, 0} }; // свой вариант

	for (auto& cur : vertexes) {
		cur.first *= SCALE;
		cur.second *= SCALE;
	}
	vertexes.push_back(vertexes[0]);

	showWhich(vertexes);

	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);

	figure(vertexes);
}

void showWhich(vector<pair<int, int>>& vertexes) {
	vector<pair<int, int>> arrEdge;
	arrEdge.resize(vertexes.size() - 1);

	for (int i = 0; i < vertexes.size() - 1; ++i) {
		arrEdge[i].first = vertexes[i + 1].first - vertexes[i].first;
		arrEdge[i].second = vertexes[i + 1].second - vertexes[i].second;
	}
	arrEdge.push_back(arrEdge[0]);

	int res = 0, temp;
	for (int i = 0; i < vertexes.size() - 1; ++i) {
		temp = arrEdge[i].first * arrEdge[i + 1].second - arrEdge[i].second * arrEdge[i + 1].first;
		res += (temp < 0 ? (-1) : 1);
	}

	if (abs(res) != vertexes.size() - 1) {
		cout << "\nМногоугольник вогнутый\n";
	}
	else {
		cout << "\nМногоугольник выпуклый\n";
	}
}

void figure(vector<pair<int, int>>& vertexes) {
	vector<pair<int, int>> points;
	points.push_back(make_pair(vertexes[0].first, vertexes[0].second));

	for (int i = 0; i < vertexes.size() - 1; ++i) {
		algorithmBrezenhema(vertexes[i].first, vertexes[i].second, vertexes[i + 1].first, vertexes[i + 1].second, points);
	}

	sort(points.begin(), points.end(), [](auto& a, auto& b) {
		return a.second < b.second || (a.second == b.second && a.first > b.first);
		});

	for (int i = 0; i < points.size() - 1; ++i) {
		if (points[i].second == points[i + 1].second) {
			if (abs(points[i].first - points[i + 1].first) > 0) {
				drawHorizontalLine(points[i].first, points[i + 1].first, points[i].second);
			}
			++i;
		}

	}
}

void algorithmBrezenhema(int x0, int y0, int xE, int yE, vector<pair<int, int>>& points) {
	int dx = abs(xE - x0), dy = abs(yE - y0);
	int step = (dx > dy) ? dx : dy;
	int xInc = (dx != 0) ? ((xE - x0) / dx) : 0,
		yInc = (dy != 0) ? ((yE - y0) / dy) : 0;
	int x = x0, y = y0;

	int p = (dx > dy) ? (2 * dy - dx) : (2 * dx - dy);

	for (int i = 0; i < step + 1; ++i) {
		setPixel(x, y);
		if (points[points.size() - 1].second != y) {
			points.push_back(make_pair(x, y));
		}

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

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();

	glFlush();
}

void drawHorizontalLine(int x0, int xE, int y) {
	int dx = abs(xE - x0),
		x = (xE > x0) ? x0 : xE;

	for (int i = 0; i < dx + 1; ++i) {
		setPixel(x++, y);
	}
}