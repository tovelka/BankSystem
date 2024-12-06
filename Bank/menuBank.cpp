#include "menuBank.h"
#include "EnterInBank.h"

void menu(int usId) {
	system("cls");
	UserAccount currentUser;
	currentUser = getUserOnId(usId);
	if (currentUser.GetFullNameUser() == "ERROR")
		exit();
	else if (currentUser.UpdateAllBankAccountsOnUser()) {
		cout << "Вы успешно вошли!\n";
		currentUser.PrintUserAccountInfo();
		setNewMenu(currentUser);
	}
}
void setNewMenu(UserAccount& userAccount) {
	bool backOnMenu = false;
	system("cls");
	userAccount.PrintUserAccountInfo();
	int newMenuNum;
	newMenuNum = PressSpecificKey("\n\nМеню:\n0 - Выйти из профиля\n1 - Посмотреть информацию о всех счетах\n2 - Открыть новый счёт\n3 - Закрыть счёт\n4 - Перевести\n5 - Пополнить счёт\n6 - Посмотреть историю переводов\nВвод: ");
	switch (newMenuNum)
	{
		case '0': {
			exit();
			break;
		}
		case '1': {
			system("cls");
			userAccount.PrintUserAccountInfo();
			userAccount.PrintInfoBankAccount();
			backOnMenu = true;
			PressEnter();
			break;
		}
		case '2': {
			system("cls");
			userAccount.PrintUserAccountInfo();
			int typeAcc = 0;
			cout << "\n2 - Открыть счёт\n*Можно создать до 10 счетов каждого типа\n";
			typeAcc = choiceAtString("Укажите тип счёта для открытия:\n1 - Рассчетный счёт\n2 - Депозитный счёт (23%)\n",1,3,3);
			if (typeAcc == 0) {
				backOnMenu = true;
				break;
			}
			string nameAcc;
			cout << "Придумайте название для счёта\n";
			cin >> nameAcc;
			if (userAccount.ExistNameCurrentBankAccount(nameAcc)) {
				cout << "Счёт с таким именем уже создан, попробуйте ввести другое имя:\n";
				PressEnter();
				backOnMenu = true;
				break;
			}
			else if (userAccount.AddNewBankAccount(typeAcc, nameAcc)) {
				cout << userAccount.idUser;
				menu(userAccount.idUser);
				backOnMenu = true;
				PressEnter();
				break;
			}
			else {
				cout << "Error of Adding New BankAccount!\n";
				PressEnter();
				backOnMenu = true;
				break;
			}
			PressEnter();
			break;
		}
		case '3':
			deleteBankAccount(0,userAccount);
			backOnMenu = true;
			PressEnter();
			break;
		case '4':
			TransferMoney(0,userAccount);
			backOnMenu = true;
			PressEnter();
			break;
		case '5':
			DepositAccount(0,userAccount);
			backOnMenu = true;
			PressEnter();
			break;
		case '6':
			system("cls");
			userAccount.PrintUserAccountInfo();
			cout << endl;
			CheckHistory(userAccount.idUser);
			backOnMenu = true;
			PressEnter();
			break;
		default: {
			cout << "Введите корректный номер меню!\n\n";
			backOnMenu = true;
			PressEnter();
			break;
		}
	}
	if (backOnMenu) {
		backOnMenu = false;
		setNewMenu(userAccount);
	}
}

void exit() {
	system("cls");
	enters(0);
}

bool deleteBankAccount(bool isOneMore, UserAccount& userAccount) {
	system("cls");
	userAccount.PrintUserAccountInfo();
	string nameAcc;
	char choice = PressSpecificKey("\nВыберите тип аккаунта:\n\n1 - Расчётный счёт\n2 - Депозитный счёт\n");
	system("cls");
	userAccount.PrintUserAccountInfo();
	if (choice == '1') {
		userAccount.PrintLowInfoBankAccount(1);
		cout << "Введите имя аккаунта: ";
		cin >> nameAcc;
		return userAccount.DeleteCurrentBankAccount(nameAcc);
	}
	else if (choice == '2') {
		userAccount.PrintLowInfoBankAccount(2);
		cout << "Введите имя аккаунта: ";
		cin >> nameAcc;
		return userAccount.DeleteDepositBankAccount(nameAcc);
	}
	else
		return deleteBankAccount(1,userAccount);
	return true;
}

bool TransferMoney(bool isOneMore, UserAccount& userAccount) {
	system("cls");
	userAccount.PrintUserAccountInfo();
	if (isOneMore == true)
		cout << "\nПопробуйте еще раз:\n";
	float sum;
	cout << "\nВведите сумму перевода: ";
	cin >> sum;
	char choice = PressSpecificKey("\nВыберите метод перевода:\n\n0 - Назад\n1 - Между своими\n2 - Другому человеку\n");
	if (choice == '0') {
		return false;
	}
	if (choice == '1') {
		string numOfInAccount;
		string numOfOutAccount;
		userAccount.PrintLowInfoBankAccount();
		cout << "\nВведите имя рассчётного счёта с которого хотите перевести: ";
		cin >> numOfInAccount;
		char choice2 = PressSpecificKey("\nВыберите на какой счёт перевести:\n\n1 - на другой рассчётный счёт\n2 - на депозитный счёт\n");
		cout << "Укажите имя счёта куда переводить: ";
		cin >> numOfOutAccount;
		if (choice2 == '1') {
			if (userAccount.TransferMoneyOnMyCurrentToCurrentAccounts(userAccount.GetIdCurrentBankAccount(numOfInAccount), userAccount.GetIdCurrentBankAccount(numOfOutAccount), sum)) {
				NoteNewHistory(to_string(userAccount.idUser) + " перевод " + to_string((int)(sum)) + " руб. с " + numOfInAccount + " на " + numOfOutAccount + ' ');
				return true;
			}
		}
		else if (choice2 == '2') {
			if (userAccount.TransferMoneyOnMyCurrentToDepositAccounts(userAccount.GetIdCurrentBankAccount(numOfInAccount), userAccount.GetIdDepositBankAccount(numOfOutAccount), sum)) {
				NoteNewHistory(to_string(userAccount.idUser) + " перевод " + to_string((int)(sum)) + " руб. с " + numOfInAccount + " на " + numOfOutAccount + ' ');
				return true;
			}
		}
		else TransferMoney(1,userAccount);
	}
	else if (choice == '2') {
		string nameOfInAccount;
		string phoneOfOutAccount;
		userAccount.PrintLowInfoBankAccount(1);
		cout << "Введите имя рассчётного счёта с которого хотите перевести: ";
		cin >> nameOfInAccount;
		cout << "Введите номер телефона, кому вы хотите перевести: ";
		cin >> phoneOfOutAccount;
		if ((userAccount.TransferToAnotherPerson(nameOfInAccount, phoneOfOutAccount, sum))) {
			NoteNewHistory(to_string(userAccount.idUser) + " перевод по номеру телефону " + phoneOfOutAccount + " в размере " + to_string((int)(sum)) + " руб. ");
			return true;
		}
	}
	else {
		return TransferMoney(1,userAccount);
	}
	return false;
}

bool DepositAccount(bool isOneMore,UserAccount& userAccount) {
	char choice = PressSpecificKey("\nВыберите тип счёта:\n\n1 - Расчётный\n2 - Депозитный\n");
	string ch2;
	float sum = 0;

	userAccount.PrintLowInfoBankAccount();

	cout << "\nУкажите название счёта:\n";
	cin >> ch2;
	cout << "Введите сумму: ";
	cin >> sum;
	if (choice == '1') {
		if (userAccount.DepositOnCurrentBankAccount(userAccount.GetIdCurrentBankAccount(ch2), sum)) {
			cout << "Пополнено " << sum << " руб.!\n";
			userAccount.UpdateCurrentBalancesInDataBase();
			NoteNewHistory(to_string(userAccount.idUser) + " поступление " + to_string((int)(sum)) + " руб. на " + ch2 + " ");
			return true;
		}
		else
			cout << "DepositAccountError(135)\n";
	}
	else if (choice == '2') {
		if (userAccount.DepositOnDepositBankAccount(userAccount.GetIdCurrentBankAccount(ch2), sum)) {
			cout << "Пополнено " << sum << " руб.!\n";
			userAccount.UpdateDepositBalancesInDataBase();
			NoteNewHistory(to_string(userAccount.idUser) + " поступление " + to_string((int)(sum)) + " руб. на " + ch2 + " ");
			return true;
		}
		else
			cout << "DepositAccountError(143)\n";
	}

	return false;
}

void CheckHistory(int usId) {
	ifstream inputFile("HistoryAccounts.txt");
	vector<string> lines; // Вектор для хранения строк

	if (!inputFile.is_open()) {
		cout << "Не удалось открыть файл " << "HistoryAccounts.txt" << endl;
	}
	string line;

	int c = 0;
	while (getline(inputFile, line)) {
		istringstream iss(line);
		int firstElement;
		iss >> firstElement; // Считываем первый элемент строки
		if (firstElement == usId) {
			cout << line << endl;
		}
	}
	inputFile.close();
}

UserAccount getUserOnId(int usId) {
	ifstream file;
	file.open("users.txt");
	int idUser;
	string fullNameBase;
	string phoneNumber;

	while (file >> idUser >> fullNameBase >> phoneNumber) {
		if (idUser == usId) 
			return UserAccount(idUser, fullNameBase,phoneNumber);
	}
	if (file.bad())
		cout << "I/O error while reading\n";
	else if (file.eof())
		cout << "The end of the file has been reached\n";
	else if (file.fail())
		cout << "Invalid data format\n";
	system("pause");
	return UserAccount();
}

void enters(bool oneMore) {
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
		enters(1);
}

int choiceAtString(string s, int fir, int sec,int times) {
	int inputS;
	cout << s;
	cin >> inputS;
	if (inputS >= fir && inputS <= sec)
		return inputS;
	else {
		if (times == 1)
			return 0;
		cout << times - 1 << " more attempts\n";
		return choiceAtString(s, fir,sec,times-1);
	}
}
