#include "StudArray.h"

const string StudArray::filename = "D:\\MyProjects_C++\\KS_Lab3_Server\\students.bin";

bool StudArray::isEmpty() const {
    bool res = arrStud.empty();
    if (res) {
        Input::bufSend += "Контейнер пуст\n";
    }

    return res;
}

auto StudArray::find(SOCKET& s) {
    string surname = Input::inputFIO(s, "фамилию");
    string name = Input::inputFIO(s, "имя");
    string patronymic = Input::inputFIO(s, "отчество");

    auto it = find_if(arrStud.begin(), arrStud.end(),
        [&](const unique_ptr<Student>& stud) {
            return (stud->getSurname() == surname &&
                stud->getName() == name &&
                stud->getPatronymic() == patronymic);
        });

    return it;
}

void StudArray::add(SOCKET& s) {
    Student cur;
    cur.setData(s);
    arrStud.push_back(make_unique<Student>(cur));

    IOFile::addStudentToFile(filename, cur);
}

void StudArray::showAll(SOCKET& s) const {
    if (isEmpty()) return;

    ostringstream oss;
    string line(67, '-');
    oss << "Таблица успеваемости студентов\n";
    oss << line << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|" << setw(13) << "Оценки" << setw(6) << "|" << endl;
    oss << "|" << setw(12) << "Номер группы" << setw(1) << "|" << setw(20) << "ФИО" << setw(14) << "|"
        << string(18, '-') << "|" << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|"
        << setw(2) << "КС" << setw(1) << "|"
        << setw(2) << "БД" << setw(1) << "|"
        << setw(4) << "ТВиФ" << setw(1) << "|"
        << setw(3) << "СПЭ" << setw(1) << "|"
        << setw(3) << "ООП" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : arrStud) {
        oss << "|" << setw(9) << el->getGroup() << setw(4) << "|"
            << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
            << setw(2) << el->getMarks()["КС"] << setw(1) << "|"
            << setw(2) << el->getMarks()["БД"] << setw(1) << "|"
            << setw(4) << el->getMarks()["ТВиА"] << setw(1) << "|"
            << setw(3) << el->getMarks()["СПЭ"] << setw(1) << "|"
            << setw(3) << el->getMarks()["ООП"] << setw(1) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}

void StudArray::del(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrStud.end()) {
        Input::bufSend += "Нет студента с таким ФИО\n";
        return;
    }

    Input::bufSend += "Вы уверены, что хотите удалить ?\n"
        "1. Да\n"
        "0. Нет\n";
    if (Input::inputNumber(s, 0, 1)) {
        arrStud.erase(it);
        Input::bufSend += "Удаление завершено\n";

        IOFile::writeStudentToFile(filename, arrStud);
    }
}

void StudArray::edit(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrStud.end()) {
        Input::bufSend += "Нет студента с таким ФИО\n";
        return;
    }

    Student copy = **it;
    bool menu = 1;
    short choice;
    while (menu) {
        Input::bufSend += "\nВыбор редактирования\n"
            "1. Номер группы студента\n"
            "2. ФИО студента\n"
            "3. Оценки студента\n"
            "0. Выйти из редактирования\n";
        choice = Input::inputNumber(s, 0, 4);
        switch (choice) {
        case 1:
            copy.setGroup(Input::inputGroup(s));
            break;
        case 2:
            copy.setSurname(Input::inputFIO(s, "фамилию"));
            copy.setName(Input::inputFIO(s, "имя"));
            copy.setPatronymic(Input::inputFIO(s, "отчество"));
            break;
        case 3:
            copy.setMarks(s);
            break;
        case 0:
            menu = 0;
        }
    }

    Input::bufSend += "Вы уверены, что хотите отредактировать?\n"
        "1. Да\n"
        "0. Нет\n";
    if (Input::inputNumber(s, 0, 1)) {
        (*it).reset();
        (*it) = make_unique<Student>(copy);
        Input::bufSend += "Редактирование завершено\n";

        IOFile::writeStudentToFile(filename, arrStud);
    }
}

void StudArray::ind(SOCKET& s) {
    if (isEmpty()) return;

    char symbol = Input::inputSymbol(s);

    list<unique_ptr<Student>> listSearch;
    for (auto& el : arrStud) {
        if (el->getSurname()[0] == symbol) {
            listSearch.push_back(make_unique<Student>(*el));
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "Нет данных с таким запросом\n";
        return;
    }

    ostringstream oss;
    string line(67, '-');
    oss << "Таблица успеваемости студентов\n";
    oss << line << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|" << setw(13) << "Оценки" << setw(6) << "|" << endl;
    oss << "|" << setw(12) << "Номер группы" << setw(1) << "|" << setw(20) << "ФИО" << setw(14) << "|"
        << string(18, '-') << "|" << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|"
        << setw(2) << "КС" << setw(1) << "|"
        << setw(2) << "БД" << setw(1) << "|"
        << setw(4) << "ТВиФ" << setw(1) << "|"
        << setw(3) << "СПЭ" << setw(1) << "|"
        << setw(3) << "ООП" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : listSearch) {
        oss << "|" << setw(9) << el->getGroup() << setw(4) << "|"
            << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
            << setw(2) << el->getMarks()["КС"] << setw(1) << "|"
            << setw(2) << el->getMarks()["БД"] << setw(1) << "|"
            << setw(4) << el->getMarks()["ТВиА"] << setw(1) << "|"
            << setw(3) << el->getMarks()["СПЭ"] << setw(1) << "|"
            << setw(3) << el->getMarks()["ООП"] << setw(1) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}
