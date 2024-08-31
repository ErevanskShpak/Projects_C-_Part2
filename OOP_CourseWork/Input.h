#pragma once
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class Input {
	static bool isAccDataCorrect(string&);
	static bool isNumberNumeric();
	template <class T>
	static bool isNumberRangeCorrect(T&, T&, T&);
	static bool isFIOCorrect(string&);
	static bool isGroupCorrect(string&);

public:
	static long long hashFunc(string, string);
	template <class T>
	static float inputNumber(T, T = INT_MAX, string = "выбор");
	static string inputLogin(string);
	static string inputPassword();
	static string inputFIO(string);
	static string inputGroup();
};

template<class T>
inline bool Input::isNumberRangeCorrect(T& number, T& leftR, T& rightR){
	if ((number >= leftR) && (number <= rightR)) {
		return true;
	} else {
		return false;
	}
}

template<class T>
inline float Input::inputNumber(T leftR, T rightR, string word) {
	cin.unsetf(ios::skipws);

	T number;
	while (true) {
		cout << "Введите " << word << ": ";
		try {
			cin >> number;
			if (!isNumberNumeric()) {
				throw 1;
			}
			if (!isNumberRangeCorrect(number, leftR, rightR)) {
				throw "incorrect range";
			}
			break;
		}
		catch (int) {
			cerr << "Некорректный ввод. Повторите попытку\n";
		}
		catch (...) {
			cerr << "Некорректный диапазон ввода. Повторите попытку\n";
		}
	}

	return number;
}
