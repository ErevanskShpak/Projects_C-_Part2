#include "Student.h"

string Student::resToString(bool res) {
	return (res ? "сдал" : "не сдал");
}

void Student::setMarks() {
	marks["Математика"] = Input::inputNumber(1, 10, "оценка по математике");
	marks["Физика"] = Input::inputNumber(1, 10, "оценка по физике");
	marks["ТРПО"] = Input::inputNumber(1, 10, "оценка по ТРПО");
	marks["ОАИП"] = Input::inputNumber(1, 10, "оценка по ОАИП");
	marks["ООП"] = Input::inputNumber(1, 10, "оценка по ООП");

	float avg = 0;
	for (auto el : marks) {
		avg += el.second;
	}
	avg /= 5;
	this->avgMark = avg;
}

void Student::setTests() {
	cout << "Ввод зачетов\n";
	cout << "зачет - 1\n";
	cout << "незачет - 0\n";

	tests["Физкультура"] = Input::inputNumber(0, 1, "зачет по физкультуре");
	tests["Логика"] = Input::inputNumber(0, 1, "зачет по логике");
	tests["ДМ"] = Input::inputNumber(0, 1, "зачет по ДМ");
	tests["ОКГ"] = Input::inputNumber(0, 1, "зачет по ОКГ");
	tests["ИКИ"] = Input::inputNumber(0, 1, "зачет по ИКИ");

	short debt = 0;
	for (auto& el : tests) {
		if (!(el.second)) {
			debt++;
		}
	}
	this->debt = debt;
}

void Student::showPerformance() {
	cout << "Эффективность этого человека\n";
	string line(27, '-');
	cout << line << endl;
	cout << "|" << setw(12) << "Предмет" << setw(2) << "|"
		<< setw(10) << "Результат" << setw(2) << "|" << endl;
	cout << line << endl;
	for (auto& mark : marks) {
		cout << "|" << setw(12) << mark.first << setw(2) << "|"
			<< setw(10) << mark.second << setw(2) << "|" << endl;
		cout << line << endl;
	}
	for (auto& test : tests) {
		cout << "|" << setw(12) << test.first << setw(2) << "|"
			<< setw(10) << (test.second ? "зачет": "незачет") << setw(2) << "|" << endl;
		cout << line << endl;
	}
	cout << "Средний балл: " << avgMark << endl;
	cout << "Количество долгов: " << debt << endl;
}

istream& operator>>(istream& cin, Student& stud) {
	stud.setSurname(Input::inputFIO("фамилию"));
	stud.setName(Input::inputFIO("имя"));
	stud.setPatronymic(Input::inputFIO("отчество"));
	stud.setGroup(Input::inputGroup());
	stud.setMarks();
	stud.setTests();

	return cin;
}
