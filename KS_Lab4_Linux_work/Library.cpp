#include "Library.h"

const string Library::filename = "D:\\MyProjects_C++\\KS_Lab4_Server\\books.bin";

bool Library::isEmpty() const {
    bool res = arrBook.empty();
    if (res) {
        Input::bufSend += "Контейнер пуст\n";
    }

    return res;
}

auto Library::find(int& s) {
    string name = Input::inputFIO(s, "имя");

    list<Book>::iterator res = arrBook.end();
    for (auto it = arrBook.begin(); it != arrBook.end(); ++it) {
        if (it->getName() == name) {
            res = it;
            break;
        }
    }

    return res;
}

void Library::add(int& s) {
    Book cur;
    cur.setData(s);
    arrBook.push_back(cur);

    IOFile::addBookToFile(filename, cur);
}

void Library::showTable(const list<Book>& arr) const {
    ostringstream oss;
    string line(58, '-');
    oss << "Таблица книг\n";
    oss << line << endl;
    oss << "|" << setw(20) << "Название" << setw(5) << "|"
        << setw(16) << "Автор" << setw(4) << "|"
        << setw(11) << "Год издания" << setw(1) << "|" << endl;
    oss << line << endl;

    for (auto& el : arr) {
        oss << "|" << setw(20) << el.getName() << setw(5) << "|"
            << setw(16) << el.getAuthor() << setw(4) << "|"
            << setw(8) << el.getDate() << setw(4) << "|" << endl;
        oss << line << endl;
    }

    Input::bufSend += oss.str();
}

void Library::showAll(int& s) const {
    if (isEmpty()) return;

    showTable(arrBook);
}

void Library::del(int& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrBook.end()) {
        Input::bufSend += "Нет такой книги\n";
        return;
    }

    Input::bufSend += "Вы уверены, что хотите удалить ?\n"
        "1. Да\n"
        "0. Нет\n";
    if (Input::inputNumber(s, 0, 1)) {
        arrBook.erase(it);
        Input::bufSend += "Удаление завершено\n";

        IOFile::writeBookToFile(filename, arrBook);
    }
}

void Library::edit(int& s) {
    if (isEmpty()) return;
    showAll(s);

    auto it = find(s);
    if (it == arrBook.end()) {
        Input::bufSend += "Нет такой книги\n";
        return;
    }

    Book copy = *it;
    bool menu = 1;
    short choice;
    while (menu) {
        Input::bufSend += "\nВыбор редактирования\n"
            "1. Название книги\n"
            "2. Автор книги\n"
            "3. Год издания книги\n"
            "0. Выйти из редактирования\n";
        choice = Input::inputNumber(s, 0, 4);
        switch (choice) {
        case 1:
            copy.setName(Input::inputFIO(s, "название книги"));
            break;
        case 2:
            copy.setAuthor(Input::inputFIO(s, "автора книги"));
            break;
        case 3:
            copy.setDate(Input::inputNumber(s, 1800, 2025, "год издания"));
            break;
        case 0:
            menu = 0;
        }
    }

    Input::bufSend += "Вы уверены, что хотите отредактировать?\n"
        "1. Да\n"
        "0. Нет\n";
    if (Input::inputNumber(s, 0, 1)) {
        (*it) = copy;
        Input::bufSend += "Редактирование завершено\n";

        IOFile::writeBookToFile(filename, arrBook);
    }
}

void Library::sortName(int& s) {
    if (isEmpty()) return;

    arrBook.sort([](Book& a, Book& b) {
        return (a.getName().compare(b.getName()) < 0);
        });

    showAll(s);
}

void Library::sortAuthor(int& s) {
    if (isEmpty()) return;

    arrBook.sort([](Book& a, Book& b) {
        return a.getAuthor() > b.getAuthor();
        });

    showAll(s);
}

void Library::sortDate(int& s) {
    if (isEmpty()) return;

    arrBook.sort([](Book& a, Book& b) {
        return a.getDate() < b.getDate();
        });

    showAll(s);
}

void Library::searchName(int& s) const {
    if (isEmpty()) return;

    string searchName = Input::inputFIO(s, "название искомой книги");

    list<Book> listSearch;
    for (auto& el : arrBook) {
        if (el.getName() == searchName) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "Нет данных с таким запросом\n";
        return;
    }

    showTable(listSearch);
}

void Library::searchAuthor(int& s) const {
    if (isEmpty()) return;

    string searchName = Input::inputFIO(s, "автора искомой книги");

    list<Book> listSearch;
    for (auto& el : arrBook) {
        if (el.getAuthor() == searchName) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "Нет данных с таким запросом\n";
        return;
    }

    showTable(listSearch);
}

void Library::searchDate(int& s) const {
    if (isEmpty()) return;

    int date = Input::inputNumber(s, 1800, 2025, "год издания");

    list<Book> listSearch;
    for (auto& el : arrBook) {
        if (el.getDate() == date) {
            listSearch.push_back(el);
        }
    }

    if (!listSearch.size()) {
        Input::bufSend += "Нет данных с таким запросом\n";
        return;
    }

    showTable(listSearch);
}