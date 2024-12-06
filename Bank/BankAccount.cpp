#include "BankAccount.h"


BankAccount::BankAccount(int idAccountInput, int idOwnerInput, string accountNumberInput, string accountNameInput) : idOwner(idOwnerInput), accountNumber(accountNumberInput), idAccount(idAccountInput), accountName(accountNameInput) {}

void BankAccount::PrintAccountInfo() {
    cout << "\nAccount '" << accountName << "' :\n";
    cout << "Account holder " << " - " << idOwner << endl;
    cout << "Account number - " << accountNumber << endl << "Account balance - " << balanceAccount << " rub." << endl;
}

void BankAccount::PrintLowBankAccountInfo() {
    cout << "Account " << accountName << " - " << balanceAccount << " rub.\n";
}

float BankAccount::GetBalanceBankAccount() {
    return balanceAccount;
}

bool BankAccount::ChangeBalanceOnAccount(float sum) {
    if (sum < 0 && balanceAccount + sum < 0) {
        cout << "Недостаточно средств на счёте!\n";
        return false;
    }
    else {
        balanceAccount += sum;
        return true;
    }
}

float getFloatFromString(string s) {
    stringstream ss(s);
    float num;
    ss >> num;
    if (ss.fail()) {
        system("pause");
        cout << "Ошибка: недопустимое преобразование." << endl;
        return 0;
    }
    else {
        return num;
    }
}

void PressEnter() {
    cout << "\nPress enter to continue: ";
    while (true) {
        if (_kbhit()) { // Проверяем, была ли нажата клавиша
            char key = _getch(); // Получаем код нажатой клавиши
            break;
        }
    }
}
char PressSpecificKey(string s) {
    cout << s;
    while (true) {
        if (_kbhit()) { // Проверяем, была ли нажата клавиша
            char key = _getch(); // Получаем код нажатой клавиши
            return key;
            break;
        }
    }
}
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
float roundVar(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}