#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
#define MATRIX_SIZE 8

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL)); //генерация случайной последовательности чисел
	vector<vector<int>> arr; //декларация исходной матрицы

	arr.resize(MATRIX_SIZE);
	for (int i = 0; i < MATRIX_SIZE; ++i) { //заполнение матрицы случайными числами от -99 до 99
		arr[i].resize(MATRIX_SIZE);
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			arr[i][j] = rand() % 199 - 99; //получение из последовательности случайного числа и приведение его к нужному диапазону
		}
	}

	int minEl = arr[MATRIX_SIZE - 1][0], minJ = 0; //инициализация минимального элемента и номера его столбца
	for (int i = MATRIX_SIZE - 2, j = 1; i >= 0; --i, ++j) { //поиск минимального элемента на побочной диагонали
		if (arr[i][j] < minEl) {
			minEl = arr[i][j];
			minJ = j;
		}
	}

	vector<vector<int>> neoarr = arr; //инициализация итоговой матрицы
	if (minJ != 0) { //проверка на то, в первом ли столбце минимальный элемент
		int buf;
		for (int i = 0; i < MATRIX_SIZE; ++i) { //замена между собой элементов первого столбца и столбца с минимальным элементом
			buf = neoarr[i][0];
			neoarr[i][0] = neoarr[i][minJ];
			neoarr[i][minJ] = buf;
		}
	}

	int maxEl = arr[0][0], maxI = 0, maxJ = 0; //инициализация максимального элемента и номеров его столбца и строки
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) { //поиск максимального элемента в матрице
			if (arr[i][j] > maxEl) {
				maxEl = arr[i][j];
				maxJ = j;
				maxI = i;
			}
		}
	}

	cout << "Максимальный элемент: " << maxEl << endl; //вывод в консоль информации о максимальном элементе
	cout << "Номер строки макс элемента: " << maxI << endl;
	cout << "Номер столбца макс элемента: " << maxJ << endl;

	cout << "\nИсходный массив\n"; //вывод в консоль исходной матрицы
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\nИтоговый массив\n"; //вывод в консоль итоговой матрицы
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		for (int j = 0; j < MATRIX_SIZE; ++j) {
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}