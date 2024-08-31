#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
#define MATRIX_SIZE 8

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL)); //��������� ��������� ������������������ �����
	vector<vector<int>> arr; //���������� �������� �������

	arr.resize(MATRIX_SIZE);
	for (int i = 0; i < MATRIX_SIZE; ++i) { //���������� ������� ���������� ������� �� -99 �� 99
		arr[i].resize(MATRIX_SIZE);
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			arr[i][j] = rand() % 199 - 99; //��������� �� ������������������ ���������� ����� � ���������� ��� � ������� ���������
		}
	}

	int minEl = arr[MATRIX_SIZE - 1][0], minJ = 0; //������������� ������������ �������� � ������ ��� �������
	for (int i = MATRIX_SIZE - 2, j = 1; i >= 0; --i, ++j) { //����� ������������ �������� �� �������� ���������
		if (arr[i][j] < minEl) {
			minEl = arr[i][j];
			minJ = j;
		}
	}

	vector<vector<int>> neoarr = arr; //������������� �������� �������
	if (minJ != 0) { //�������� �� ��, � ������ �� ������� ����������� �������
		int buf;
		for (int i = 0; i < MATRIX_SIZE; ++i) { //������ ����� ����� ��������� ������� ������� � ������� � ����������� ���������
			buf = neoarr[i][0];
			neoarr[i][0] = neoarr[i][minJ];
			neoarr[i][minJ] = buf;
		}
	}

	int maxEl = arr[0][0], maxI = 0, maxJ = 0; //������������� ������������� �������� � ������� ��� ������� � ������
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) { //����� ������������� �������� � �������
			if (arr[i][j] > maxEl) {
				maxEl = arr[i][j];
				maxJ = j;
				maxI = i;
			}
		}
	}

	cout << "������������ �������: " << maxEl << endl; //����� � ������� ���������� � ������������ ��������
	cout << "����� ������ ���� ��������: " << maxI << endl;
	cout << "����� ������� ���� ��������: " << maxJ << endl;

	cout << "\n�������� ������\n"; //����� � ������� �������� �������
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\n�������� ������\n"; //����� � ������� �������� �������
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}