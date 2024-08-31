#include "Book.h"

void Book::setData(int& s) {
	setName(Input::inputFIO(s, "название книги"));
	setAuthor(Input::inputFIO(s, "автора книги"));
	setDate(Input::inputNumber(s, 1800, 2025, "год издания"));
}
