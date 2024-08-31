#include "StudArray.h"

const string StudArray::filename = "C:\\My_projects\\OOP_CourseWork\\Files\\students.bin";

bool StudArray::isEmpty() const {
    bool res = arrStud.empty();
    if (res) {
        cout << "Контейнер пуст\n";
    }

    return res;
}

auto StudArray::find() {
    string surname = Input::inputFIO("фамилию");
    string name = Input::inputFIO("имя");
    string patronymic = Input::inputFIO("отчество");

    auto it = find_if(arrStud.begin(), arrStud.end(),
        [&](const unique_ptr<Student>& stud) {
            return (stud->getSurname() == surname &&
                stud->getName() == name &&
                stud->getPatronymic() == patronymic);
        });

    return it;
}

void StudArray::showTable(ostream& sout, const list<unique_ptr<Student>>& arr) const {
    string line(137, '-');
    sout << "Таблица успеваемости студентов\n";
    sout << line << endl;
    sout << "|" << setw(13) << "|" << setw(34) << "|" << setw(20) << "Оценки" << setw(12) << "|" << setw(13) << "|"
        << setw(31) << "Сведения о зачетах" << setw(13) << "|" << endl;
    sout << "|" << setw(12) << "Номер группы" << setw(1) << "|" << setw(20) << "ФИО" << setw(14) << "|"
        << string(31, '-') << "|" << setw(12) << "Средний балл" << setw(1) << "|" << string(43, '-') << "|" << endl;
    sout << "|" << setw(13) << "|" << setw(34) << "|"
        << setw(10) << "Математика" << setw(1) << "|"
        << setw(6) << "Физика" << setw(1) << "|"
        << setw(4) << "ТРПО" << setw(1) << "|"
        << setw(4) << "ОАИП" << setw(1) << "|"
        << setw(3) << "ООП" << setw(1) << "|"
        << setw(13) << "|"
        << setw(11) << "Физкультура" << setw(1) << "|"
        << setw(7) << "Логика" << setw(1) << "|"
        << setw(7) << "ДМ" << setw(1) << "|"
        << setw(7) << "ОКГ" << setw(1) << "|"
        << setw(7) << "ИКИ" << setw(1) << "|" << endl;
    sout << line << endl;

    for (auto& el : arr) {
        sout << "|" << setw(9) << el->getGroup() << setw(4) << "|"
            << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
            << setw(10) << el->getMarks()["Математика"] << setw(1) << "|"
            << setw(6) << el->getMarks()["Физика"] << setw(1) << "|"
            << setw(4) << el->getMarks()["ТРПО"] << setw(1) << "|"
            << setw(4) << el->getMarks()["ОАИП"] << setw(1) << "|"
            << setw(3) << el->getMarks()["ООП"] << setw(1) << "|"
            << setw(8) << el->getAverage_mark() << setw(5) << "|"
            << setw(11) << Student::resToString(el->getTests()["Физкультура"]) << setw(1) << "|"
            << setw(7) << Student::resToString(el->getTests()["Логика"]) << setw(1) << "|"
            << setw(7) << Student::resToString(el->getTests()["ДМ"]) << setw(1) << "|"
            << setw(7) << Student::resToString(el->getTests()["ОКГ"]) << setw(1) << "|"
            << setw(7) << Student::resToString(el->getTests()["ИКИ"]) << setw(1) << "|" << endl;
        sout << line << endl;
    }
}

void StudArray::add() {
    Student cur;
    cin >> cur;
    arrStud.push_back(make_unique<Student>(cur));

    IOFile::addStudentToFile(filename, cur);
}

void StudArray::showAll() const {
    if (isEmpty()) return;

    showTable(cout, arrStud);
}

void StudArray::del() {
    if (isEmpty()) return;
    showAll();

    auto it = find();
    if (it == arrStud.end()) {
        cout << "Нет студента с таким ФИО\n";
        return;
    }

    cout << "Вы уверены, что хотите удалить ?\n";
    cout << "1. Да\n";
    cout << "0. Нет\n";
    if (Input::inputNumber(0, 1)) {
        arrStud.erase(it);
        cout << "Удаление завершено\n";

        IOFile::writeStudentToFile(filename, arrStud);
    }
}

void StudArray::edit() {
    if (isEmpty()) return;
    showAll();

    auto it = find();
    if (it == arrStud.end()) {
        cout << "Нет студента с таким ФИО\n";
        return;
    }

    Student copy = **it;
    bool menu = 1;
    short choice;
    while (menu) {
        cout << "\nВыбор редактирования\n";
        cout << "1. Номер группы студента\n";
        cout << "2. ФИО студента\n";
        cout << "3. Оценки студента\n";
        cout << "4. Зачеты студента\n";
        cout << "0. Выйти из редактирования\n";
        
        choice = Input::inputNumber(0, 4);
        switch (choice) {
        case 1:
            copy.setGroup(Input::inputGroup());
            break;
        case 2:
            copy.setSurname(Input::inputFIO("фамилию"));
            copy.setName(Input::inputFIO("имя"));
            copy.setPatronymic(Input::inputFIO("отчество"));
            break;
        case 3:
            copy.setMarks();
            break;
        case 4:
            copy.setTests();
            break;
        case 0:
            menu = 0;
        }
    }

    cout << "Вы уверены, что хотите отредактировать?\n";
    cout << "1. Да\n";
    cout << "0. Нет\n";
    if (Input::inputNumber(0, 1)) {
        (*it).reset();
        (*it) = make_unique<Student>(copy);
        cout << "Редактирование завершено\n";

        IOFile::writeStudentToFile(filename, arrStud);
    }
}

void StudArray::sortFIO() {
    if (isEmpty()) return;

    arrStud.sort([](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
        short res = a->getSurname().compare(b->getSurname());
        if (!res) {
            res = a->getName().compare(b->getName());
            if (!res) {
                res = a->getPatronymic().compare(b->getPatronymic());
            }
        }
        return (res < 0);
        });

    showAll();
}

void StudArray::sortAvgMark() {
    if (isEmpty()) return;

    arrStud.sort([](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
        return a->getAverage_mark() > b->getAverage_mark();
        });

    showAll();
}

void StudArray::sortGroup() {
    if (isEmpty()) return;

    arrStud.sort([](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
        return a->getGroup() < b->getGroup();
        });

    showAll();
}

void StudArray::searchAvgMark() const {
    if (isEmpty()) return;

    float searchMark = Input::inputNumber(0.0f, 10.0f, "искомый минимальный средний балл");

    list<unique_ptr<Student>> listSearch;
    for (auto& el : arrStud) {
        if (el->getAverage_mark() >= searchMark) {
            listSearch.push_back(make_unique<Student>(*el));
        }
    }

    if (!listSearch.size()) {
        cout << "Нет данных с таким запросом\n";
        return;
    }

    showTable(cout, listSearch);
}

void StudArray::searchFIO() const {
    if (isEmpty()) return;

    string surname = Input::inputFIO("фамилию");
    string name = Input::inputFIO("имя");
    string patronymic = Input::inputFIO("отчество");

    auto it = arrStud.begin();
    for (; it != arrStud.end(); ++it) {
        if ((*it)->getName() == name && (*it)->getSurname() == surname &&
            (*it)->getPatronymic() == patronymic) {
            cout << **it;
            return;
        }
    }

    cout << "Данные о таком студенте не найдены\n";
}

void StudArray::searchGroup() const {
    if (isEmpty()) return;

    string group = Input::inputGroup();

    list<unique_ptr<Student>> listSearch;
    for (auto& el : arrStud) {
        if (el->getGroup() == group) {
            listSearch.push_back(make_unique<Student>(*el));
        }
    }

    if (!listSearch.size()) {
        cout << "Нет данных с таким запросом\n";
        return;
    }

    showTable(cout, listSearch);
}

void StudArray::showDebt() {
    if (isEmpty()) return;

    arrStud.sort([](const unique_ptr<Student>& a, const unique_ptr<Student>& b) {
        return a->getDebt() > b->getDebt();
        });

    unordered_map<string, short> groups;
    list<unique_ptr<Student>> listSearch;
    string curGroup;
    for (auto& el : arrStud) {
        if (el->getDebt() > 0) {
            listSearch.push_back(make_unique<Student>(*el));

            curGroup = el->getGroup();
            if (groups.count(curGroup) == 0) {
                groups[curGroup] = 1;
            } else {
                groups[curGroup]++;
            }
        } else {
            break;
        }
    }

    string groupMax;
    short maks = 0;
    for (auto& el : groups) {
        if (el.second > maks) {
            maks = el.second;
            groupMax = el.first;
        }
    }

    auto showSpecialTable{ [&](ostream& sout) {
        string line(99, '-');
        sout << "Таблица студентов с задолженностями для сдачи сессии\n";
        sout << line << endl;
        sout << "|" << setw(13) << "|" << setw(34) << "|" << setw(31) << "Сведения о зачетах" << setw(13) << "|" << setw(7) << "|" << endl;
        sout << "|" << setw(12) << "Номер группы" << setw(1) << "|" << setw(20) << "ФИО" << setw(14) << "|"
            << string(43, '-') << "|" << setw(5) << "Долг" << setw(2) << "|" << endl;
        sout << "|" << setw(13) << "|" << setw(34) << "|"
            << setw(11) << "Физкультура" << setw(1) << "|"
            << setw(7) << "Логика" << setw(1) << "|"
            << setw(7) << "ДМ" << setw(1) << "|"
            << setw(7) << "ОКГ" << setw(1) << "|"
            << setw(7) << "ИКИ" << setw(1) << "|"
            << setw(7) << "|" << endl;
        sout << line << endl;

        for (auto& el : listSearch) {
            sout << "|" << setw(9) << el->getGroup() << setw(4) << "|"
                << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
                << setw(11) << Student::resToString(el->getTests()["Физкультура"]) << setw(1) << "|"
                << setw(7) << Student::resToString(el->getTests()["Логика"]) << setw(1) << "|"
                << setw(7) << Student::resToString(el->getTests()["ДМ"]) << setw(1) << "|"
                << setw(7) << Student::resToString(el->getTests()["ОКГ"]) << setw(1) << "|"
                << setw(7) << Student::resToString(el->getTests()["ИКИ"]) << setw(1) << "|"
                << setw(5) << el->getDebt() << setw(2) << "|" << endl;
            sout << line << endl;

        }

        sout << "Количество студентов с задолженностями: " << listSearch.size() << endl;
        sout << "Группа с наибольшим количество должников: " << groupMax << endl;
        } };

    showSpecialTable(cout);

    ofstream fs("C:\\My_projects\\OOP_CourseWork\\Files\\Отчет_Задолженности.txt", ios::trunc);
    showSpecialTable(fs);
}

void StudArray::showAvgOfGroup() const {
    if (isEmpty()) return;

    string group = Input::inputGroup();

    float groupAvgMark = 0, maks = 0;
    string bestStudent;
    list<unique_ptr<Student>> listSearch;
    for (auto& el : arrStud) {
        if (el->getGroup() == group) {
            listSearch.push_back(make_unique<Student>(*el));
            groupAvgMark += el->getAverage_mark();
            if (el->getAverage_mark() > maks) {
                maks = el->getAverage_mark();
                bestStudent = el->getSurname() + " " + el->getName() + " " + el->getPatronymic();
            }
        }
    }

    if (!listSearch.size()) {
        cout << "Нет данных о студентах такой группы\n";
        return;
    }
    groupAvgMark /= listSearch.size();
    auto showSpecialTable{ [&](ostream& sout) {
        string line(93, '-');
        sout << "Таблица успеваемости студентов группы " + group << endl;
        sout << line << endl;
        sout << "|" << setw(13) << "|" << setw(34) << "|" << setw(20) << "Оценки" << setw(12) << "|" << setw(13) << "|" << endl;
        sout << "|" << setw(12) << "Номер группы" << setw(1) << "|" << setw(20) << "ФИО" << setw(14) << "|"
            << string(31, '-') << "|" << setw(12) << "Средний балл" << setw(1) << "|" << endl;
        sout << "|" << setw(13) << "|" << setw(34) << "|"
            << setw(10) << "Математика" << setw(1) << "|"
            << setw(6) << "Физика" << setw(1) << "|"
            << setw(4) << "ТРПО" << setw(1) << "|"
            << setw(4) << "ОАИП" << setw(1) << "|"
            << setw(3) << "ООП" << setw(1) << "|"
            << setw(13) << "|" << endl;
        sout << line << endl;

        for (auto& el : listSearch) {
            sout << "|" << setw(9) << el->getGroup() << setw(4) << "|"
                << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
                << setw(10) << el->getMarks()["Математика"] << setw(1) << "|"
                << setw(6) << el->getMarks()["Физика"] << setw(1) << "|"
                << setw(4) << el->getMarks()["ТРПО"] << setw(1) << "|"
                << setw(4) << el->getMarks()["ОАИП"] << setw(1) << "|"
                << setw(3) << el->getMarks()["ООП"] << setw(1) << "|"
                << setw(8) << el->getAverage_mark() << setw(5) << "|" << endl;
            sout << line << endl;
        }

        sout << "\nСредний балл всей группы: " << groupAvgMark << endl;
        sout << "Студент с самым высоким средним баллом: " << bestStudent << endl;
        } };
   
    showSpecialTable(cout);

    ofstream fs("C:\\My_projects\\OOP_CourseWork\\Files\\Отчет_группы_" + group + ".txt", ios::trunc);
    showSpecialTable(fs);
}
