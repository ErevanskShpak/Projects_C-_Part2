#include "StudArray.h"

const string StudArray::filename = "D:\\MyProjects_C++\\KS_Lab3_Server\\students.bin";

bool StudArray::isEmpty() const {
    bool res = arrStud.empty();
    if (res) {
        Input::bufSend += "��������� ����\n";
    }

    return res;
}

auto StudArray::find(SOCKET& s) {
    string surname = Input::inputFIO(s, "�������");
    string name = Input::inputFIO(s, "���");
    string patronymic = Input::inputFIO(s, "��������");

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
    oss << "������� ������������ ���������\n";
    oss << line << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|" << setw(13) << "������" << setw(6) << "|" << endl;
    oss << "|" << setw(12) << "����� ������" << setw(1) << "|" << setw(20) << "���" << setw(14) << "|"
        << string(18, '-') << "|" << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|"
        << setw(2) << "��" << setw(1) << "|"
        << setw(2) << "��" << setw(1) << "|"
        << setw(4) << "����" << setw(1) << "|"
        << setw(3) << "���" << setw(1) << "|"
        << setw(3) << "���" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : arrStud) {
        oss << "|" << setw(9) << el->getGroup() << setw(4) << "|"
            << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
            << setw(2) << el->getMarks()["��"] << setw(1) << "|"
            << setw(2) << el->getMarks()["��"] << setw(1) << "|"
            << setw(4) << el->getMarks()["����"] << setw(1) << "|"
            << setw(3) << el->getMarks()["���"] << setw(1) << "|"
            << setw(3) << el->getMarks()["���"] << setw(1) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}

void StudArray::del(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrStud.end()) {
        Input::bufSend += "��� �������� � ����� ���\n";
        return;
    }

    Input::bufSend += "�� �������, ��� ������ ������� ?\n"
        "1. ��\n"
        "0. ���\n";
    if (Input::inputNumber(s, 0, 1)) {
        arrStud.erase(it);
        Input::bufSend += "�������� ���������\n";

        IOFile::writeStudentToFile(filename, arrStud);
    }
}

void StudArray::edit(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrStud.end()) {
        Input::bufSend += "��� �������� � ����� ���\n";
        return;
    }

    Student copy = **it;
    bool menu = 1;
    short choice;
    while (menu) {
        Input::bufSend += "\n����� ��������������\n"
            "1. ����� ������ ��������\n"
            "2. ��� ��������\n"
            "3. ������ ��������\n"
            "0. ����� �� ��������������\n";
        choice = Input::inputNumber(s, 0, 4);
        switch (choice) {
        case 1:
            copy.setGroup(Input::inputGroup(s));
            break;
        case 2:
            copy.setSurname(Input::inputFIO(s, "�������"));
            copy.setName(Input::inputFIO(s, "���"));
            copy.setPatronymic(Input::inputFIO(s, "��������"));
            break;
        case 3:
            copy.setMarks(s);
            break;
        case 0:
            menu = 0;
        }
    }

    Input::bufSend += "�� �������, ��� ������ ���������������?\n"
        "1. ��\n"
        "0. ���\n";
    if (Input::inputNumber(s, 0, 1)) {
        (*it).reset();
        (*it) = make_unique<Student>(copy);
        Input::bufSend += "�������������� ���������\n";

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
        Input::bufSend += "��� ������ � ����� ��������\n";
        return;
    }

    ostringstream oss;
    string line(67, '-');
    oss << "������� ������������ ���������\n";
    oss << line << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|" << setw(13) << "������" << setw(6) << "|" << endl;
    oss << "|" << setw(12) << "����� ������" << setw(1) << "|" << setw(20) << "���" << setw(14) << "|"
        << string(18, '-') << "|" << endl;
    oss << "|" << setw(13) << "|" << setw(34) << "|"
        << setw(2) << "��" << setw(1) << "|"
        << setw(2) << "��" << setw(1) << "|"
        << setw(4) << "����" << setw(1) << "|"
        << setw(3) << "���" << setw(1) << "|"
        << setw(3) << "���" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : listSearch) {
        oss << "|" << setw(9) << el->getGroup() << setw(4) << "|"
            << setw(31) << el->getSurname() + " " + el->getName() + " " + el->getPatronymic() << setw(3) << "|"
            << setw(2) << el->getMarks()["��"] << setw(1) << "|"
            << setw(2) << el->getMarks()["��"] << setw(1) << "|"
            << setw(4) << el->getMarks()["����"] << setw(1) << "|"
            << setw(3) << el->getMarks()["���"] << setw(1) << "|"
            << setw(3) << el->getMarks()["���"] << setw(1) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}
