#include "ArrayShape.h"

const string ArrayShape::filename = "D:\\MyProjects_C++\\KS_Lab4_Server\\shapes.bin";

bool ArrayShape::isEmpty() const {
    bool res = arrShape.empty();
    if (res) {
        Input::bufSend += "��������� ����\n";
    }

    return res;
}

auto& ArrayShape::find(SOCKET& s) {
    string name = Input::inputFIO(s, "��������");

    list<Shape>::iterator res;
    for (auto it = arrShape.begin(); it != arrShape.end(); ++it) {
        if (it->getName() == name) {
            res = it;
            break;
        }
    }

    return res;
}

void ArrayShape::add(SOCKET& s) {
    Shape cur;
    cur.setData(s);
    arrShape.push_back(cur);

    IOFile::addShapeToFile(filename, cur);
}

void ArrayShape::showTable(const list<Shape>& arr) const {
    ostringstream oss;
    string line(58, '-');
    oss << "������� �����\n";
    oss << line << endl;
    oss << "|" << setw(20) << "��������" << setw(5) << "|"
        << setw(16) << "�������" << setw(4) << "|"
        << setw(11) << "��������" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : arr) {
        oss << "|" << setw(20) << el.getName() << setw(5) << "|"
            << setw(16) << el.getSquare() << setw(4) << "|"
            << setw(8) << el.getPerimeter() << setw(4) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}

void ArrayShape::showAll(SOCKET& s) const {
    if (isEmpty()) return;

    showTable(arrShape);
}

void ArrayShape::del(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrShape.end()) {
        Input::bufSend += "��� ����� ������\n";
        return;
    }

    Input::bufSend += "�� �������, ��� ������ ������� ?\n"
        "1. ��\n"
        "0. ���\n";
    if (Input::inputNumber(s, 0, 1)) {
        arrShape.erase(it);
        Input::bufSend += "�������� ���������\n";

        IOFile::writeShapeToFile(filename, arrShape);
    }
}

void ArrayShape::edit(SOCKET& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrShape.end()) {
        Input::bufSend += "��� ����� ������\n";
        return;
    }

    Shape copy = *it;
    bool menu = 1;
    short choice;
    while (menu) {
        Input::bufSend += "\n����� ��������������\n"
            "1. �������� ������\n"
            "2. ������� ������\n"
            "3. �������� ������\n"
            "0. ����� �� ��������������\n";
        choice = Input::inputNumber(s, 0, 4);
        switch (choice) {
        case 1:
            copy.setName(Input::inputFIO(s, "�������� ������"));
            break;
        case 2:
            copy.setSquare(Input::inputNumber(s, 0, 10000, "������� ������"));
            break;
        case 3:
            copy.setPerimeter(Input::inputNumber(s, 0, 10000, "�������� ������"));
            break;
        case 0:
            menu = 0;
        }
    }

    Input::bufSend += "�� �������, ��� ������ ���������������?\n"
        "1. ��\n"
        "0. ���\n";
    if (Input::inputNumber(s, 0, 1)) {
        (*it) = copy;
        Input::bufSend += "�������������� ���������\n";

        IOFile::writeShapeToFile(filename, arrShape);
    }
}

void ArrayShape::sortName(SOCKET& s) {
    if (isEmpty()) return;

    arrShape.sort([](Shape& a, Shape& b) {
        return (a.getName().compare(b.getName()) < 0);
        });

    showAll(s);
}

void ArrayShape::sortSquare(SOCKET& s) {
    if (isEmpty()) return;

    arrShape.sort([](Shape& a, Shape& b) {
        return a.getSquare() > b.getSquare();
        });

    showAll(s);
}

void ArrayShape::sortPerimeter(SOCKET& s) {
    if (isEmpty()) return;

    arrShape.sort([](Shape& a, Shape& b) {
        return a.getPerimeter() < b.getPerimeter();
        });

    showAll(s);
}

void ArrayShape::searchName(SOCKET& s) const {
    if (isEmpty()) return;

    string searchName = Input::inputFIO(s, "�������� ������� ������");

    list<Shape> listSearch;
    for (auto& el : arrShape) {
        if (el.getName() == searchName) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "��� ������ � ����� ��������\n";
        return;
    }

    showTable(listSearch);
}

void ArrayShape::searchSquare(SOCKET& s) const {
    if (isEmpty()) return;

    int searchSquare = Input::inputNumber(s, 0, 10000, "������� ������");

    list<Shape> listSearch;
    for (auto& el : arrShape) {
        if (el.getSquare() == searchSquare) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "��� ������ � ����� ��������\n";
        return;
    }

    showTable(listSearch);
}

void ArrayShape::searchPerimeter(SOCKET& s) const {
    if (isEmpty()) return;

    int perimeter = Input::inputNumber(s, 0, 10000, "�������� ������");

    list<Shape> listSearch;
    for (auto& el : arrShape) {
        if (el.getPerimeter() == perimeter) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "��� ������ � ����� ��������\n";
        return;
    }

    showTable(listSearch);
}