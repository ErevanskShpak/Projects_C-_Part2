#include "Sign.h"

Account* Sign::signIn(AccArray& accArr) {
	string login = Input::inputLogin("логин");
	string password = Input::inputPassword();

	for (auto& el:accArr.getArr()) {
		if (el->getLogin() == login) {
			long long hash = Input::hashFunc(password, el->getSalt());
			if (el->getHash() == hash) {
				return el.get();
			}
		}
	}

	cout << "Неверный логин или пароль, попробуйте заново.\n";
	return nullptr;
}

void Sign::signUpAdmin(AccArray& accArr) {
	cout << "Выбор роль:\n";
	cout << "1. Админ\n";
	cout << "0. Пользователь\n";

	accArr.add(Input::inputNumber(0, 1));
}

void Sign::signUpUser(AccArray& accArr) {
	accArr.add(0);
}

void Sign::firstSign(AccArray& accArr) {
	cout << "Первого админа не существует. Создайте его\n";
	accArr.add(1);
}
