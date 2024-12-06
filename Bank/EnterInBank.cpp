#include "EnterInBank.h"

void sign(bool isNew) {
	if (isNew) {
		menu(createUser());
		cout << "Пользователь создан!\n";
	}
	else {
		menu(enterInProfileBankUser());
	}
}


int enterInProfileBankUser() {
	system("cls");
	string phoneNumber;
	
	cout << "Вход:\nВведите номер телефона: ";
	cin >> phoneNumber;

	int usId = GetIdByPhone(phoneNumber);

	if (usId >= 0) {
		if (checkSMSCode(0, usId) == false) {
			return enterInProfileBankUser();
		}
		else
			return usId;
	}
	else cout << "\nНеверный номер телефона!\n";
	PressEnter();
	return enterInProfileBankUser();
}

bool checkSMSCode(bool oneMore,int idUserInput) {
	if (oneMore)
		cout << "Неверный код, попробуйте еще раз\n";
	unsigned int smsCode;
	cout << "\nВведите код из смс (0 - ввести другой номер карты): ";
	cin >> smsCode;
	if (smsCode == 123456)
		return true;
	else if (smsCode == 0)
		return false;
	else
		return checkSMSCode(true, idUserInput);
}

int createUser() {
	system("cls");
	string fullName;
	string phoneNumber;
	cout << "Регистрация:\nВведите ваше полное имя: ";
	cin >> fullName;
	cout << "\nВведите ваш номер телефона: ";
	cin >> phoneNumber;
	int newId = knowOutFreeId();
	ofstream out("users.txt", ios::app);
	if (!out.is_open()) {
		cout << "Ошибка базы данных!\n";
		system("pause");
	}
	else {
		if (newId == 0)
			out << newId << ' ' << fullName << ' ' << phoneNumber;
		else
			out << endl << newId << ' ' << fullName << ' ' << phoneNumber;
	}
	NoteNewHistory(to_string(newId) + " профиль создан ");
	out.close();
	return newId;
}

bool NoteNewHistory(string s) {
	ifstream inputFile("HistoryAccounts.txt");
	vector<string> lines; // Вектор для хранения строк

	if (!inputFile.is_open()) {
		cerr << "Не удалось открыть файл " << "HistoryAccounts.txt" << std::endl;
		return false;
	}
	string line;

	int c = 0;

	while (getline(inputFile, line)) {
		if (c > 0) {
			lines.push_back("\n" + line); // Добавляем строку в вектор
		}
		else {
			lines.push_back(line);
		}
		c++;
	}
	inputFile.close();

	ofstream outputFile("HistoryAccounts.txt");
	if (!outputFile.is_open()) {
		cerr << "Не удалось открыть файл " << "HistoryAccounts.txt" << " для записи." << endl;
		return false;
	}

	for (const auto& updatedLine : lines) {
		outputFile << updatedLine; // Записываем каждую строку
	}
	if (c == 0)
		outputFile << s + currentDateTime();
	else
		outputFile << "\n" + s + currentDateTime();
	outputFile.close();
	return true;
}



int knowOutFreeId() {
	int freeId;
	string lastLine;
	string freeIdString;

	ifstream in;
	in.open("users.txt");
	if (!in.is_open()) {
		return -1;
	}
	else {
		getline(in, lastLine);
		while (getline(in, lastLine)) {}
		freeIdString = "";

		for (size_t i = 0; i < lastLine.length(); i++) {
			freeIdString += lastLine[i];
		}
		if (freeIdString == "")
			freeId = 0;
		else 
			freeId = atoi(freeIdString.c_str()) + 1;
		return freeId;
	}
}