#include "EnterInBank.h"
void enter(bool oneMore);

int main() {

	enter(0); // Вход/Регистрация
	 //Заходим в профиль

	return 0;
}
void enter(bool oneMore) {
	system("cls");
	char out;
	if (!oneMore)
		out = PressSpecificKey("Войти в систему - 0, регистрация - 1\n");
	else
		out = PressSpecificKey("Введите корректное значение!\nВойти в систему - 0, регистрация - 1\n");
	if (out == '0')
		sign(0);
	else if (out == '1')
		sign(1);
	else
		enter(1);
}
