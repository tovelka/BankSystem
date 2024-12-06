#include "UserAccount.h"

UserAccount::UserAccount(int idUserInput, string fullNameUserInput, string phoneUserInput) : idUser(idUserInput),
fullNameUser(fullNameUserInput), phoneUser(phoneUserInput){
    for (int i = 0; i < 10; ++i) {
        accountsCurrent[i] = nullptr; // Инициализация указателей нулями
        accountsDeposit[i] = nullptr;
        accountsSavings[i] = nullptr;
    }
};
UserAccount::UserAccount() : idUser(0), fullNameUser("ERROR"), phoneUser("ERROR") {
    for (int i = 0; i < 10; ++i) {
        accountsCurrent[i] = nullptr; // Инициализация указателей нулями
        accountsDeposit[i] = nullptr;
        accountsSavings[i] = nullptr;
    }
};

string UserAccount :: GetFullNameUser() {
    return fullNameUser;
}

void UserAccount::PrintUserAccountInfo() {
    cout << "User " << fullNameUser << endl;
    cout << "Balance on " << CheckCountOfAccounts() << " accounts is " << GetBalanceAllBankAccounts(0) << " rub." << endl;
}

bool UserAccount::AddNewBankAccount(int type, string name) {
    if (CheckCountOfAccounts(type) >= numOfBankAccounts) {
        return false;
    }
    switch (type)
    {
    case 1: {
        int idAcc = GetFreeNumOfIdAccount(1);
        accountsCurrent[CheckCountOfAccounts(1)] = new CurrentBankAccount(idAcc, idUser, generateNewNum(0, 9, 16), name, "5757" + generateNewNum(0, 9, 12), "11.2026");
        if (NoteNewAccount(*accountsCurrent[CheckCountOfAccounts(1) - 1]))
            cout << "Account is created!\n";
        else
            return false;
        return true;
        break;
    }
    case 2: {
        int idAcc = GetFreeNumOfIdAccount(2);
        accountsDeposit[CheckCountOfAccounts(2)] = new DepositBankAccount(idAcc, idUser, generateNewNum(0, 9, 16), name, 23, "12.11.2026");
        if (NoteNewAccount(*accountsDeposit[CheckCountOfAccounts(2) - 1]))
            cout << "Account is created!\n";
        else
            return false;
        return true;
        break;
    }
    default:
        return false;
        break;
    }
}

bool UserAccount::NoteNewAccount(CurrentBankAccount& bankAccount) {
    ifstream inputFile("CurrentAccounts.txt");
    vector<string> lines; // Вектор для хранения строк

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << std::endl;
        return false;
    }
    string line;

    int c = 0;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        int firstElement;
        iss >> firstElement; // Считываем первый элемент строки
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] != nullptr && firstElement == (accountsCurrent[i]->idAccount)) {
                line = accountsCurrent[i]->getBankAccountInfo();
            }
        }
        if (c > 0) {
            lines.push_back("\n" + line); // Добавляем строку в вектор
        }
        else {
            lines.push_back(line);
        }
        c++;
    }
    inputFile.close();

    ofstream outputFile("CurrentAccounts.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << " для записи." << endl;
        return false;
    }

    for (const auto& updatedLine : lines) {
        outputFile << updatedLine; // Записываем каждую строку
    }
    if(c == 0)
        outputFile << bankAccount.getBankAccountInfo();
    else
        outputFile << "\n" + bankAccount.getBankAccountInfo();
    outputFile.close();
    NoteNewHistory(to_string(idUser) + " расчётный счёт " + bankAccount.accountName + " открыт ");
    return true;
}

bool UserAccount::NoteNewAccount(DepositBankAccount& bankAccount) {
    ifstream inputFile("DepositAccounts.txt");
    vector<string> lines; // Вектор для хранения строк

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "DepositAccounts.txt" << std::endl;
        return false;
    }
    string line;

    int c = 0;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        int firstElement;
        iss >> firstElement; // Считываем первый элемент строки
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] != nullptr && firstElement == (accountsCurrent[i]->idAccount)) {
                line = accountsCurrent[i]->getBankAccountInfo();
            }
        }
        if (c > 0) {
            lines.push_back("\n" + line); // Добавляем строку в вектор
        }
        else {
            lines.push_back(line);
        }
        c++;
    }
    inputFile.close();

    ofstream outputFile("DepositAccounts.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "DepositAccounts.txt" << " для записи." << endl;
        return false;
    }

    for (const auto& updatedLine : lines) {
        outputFile << updatedLine; // Записываем каждую строку
    }
    if (c == 0)
        outputFile << bankAccount.getBankAccountInfo();
    else
        outputFile << "\n" + bankAccount.getBankAccountInfo();
    outputFile.close();
    NoteNewHistory(to_string(idUser) + " депзитный счёт " + bankAccount.accountName + " открыт ");
    return true;
}

bool UserAccount :: NoteNewHistory(string s) {
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

bool UserAccount::ExistNameCurrentBankAccount(string nameAcc) {
    if (CheckCountOfAccounts() > 0) {
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] != nullptr) {
                if (accountsCurrent[i]->getNameBankAccount() == nameAcc) {
                    return true;
                }
            }
            else {
                cout << "Аккаунта с таким именем не существует!\n";
                break;
            }
        }
    }
    return false;
}

int UserAccount :: GetIdCurrentBankAccount(string nameAcc) {
    if (CheckCountOfAccounts(1) > 0) {
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] != nullptr) {
                if (accountsCurrent[i]->getNameBankAccount() == nameAcc) {
                    return i;
                }
            }
            else {
                cout << "Счёта с таким именем не существует!\n";
                break;
            }
        }
    }
    return -1;
}

int UserAccount::GetIdDepositBankAccount(string nameAcc) {
    if (CheckCountOfAccounts(2) > 0) {
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsDeposit[i] != nullptr) {
                if (accountsDeposit[i]->getNameBankAccount() == nameAcc) {
                    return i;
                }
            }
            else {
                cout << "Аккаунта с таким именем не существует!\n";
                break;
            }
        }
    }
    return -1;
}

bool UserAccount::DeleteCurrentBankAccount(string nameAcc) {
    if (CheckCountOfAccounts() > 0) {
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] != nullptr) {
                if (accountsCurrent[i]->getNameBankAccount() == nameAcc) {
                    int balanceCurI = accountsCurrent[i]->balanceAccount;
                    if (balanceCurI > 0) {
                        char isC = PressSpecificKey("Вы закрываете счёт, на котором осталось еще " + to_string(balanceCurI) + " руб.!\n1 - Все равно закрыть\n2 - Я передумал(а)\n");
                        if (isC != '1')
                            break;
                    }
                    NoteNewHistory(to_string(idUser) + " расчётный счёт " + accountsCurrent[i]->accountName + " закрыт ");
                    accountsCurrent[i]->idOwner = -1;
                    UpdateCurrentBalancesInDataBase();
                    for (int i = 0; i < numOfBankAccounts; ++i) { // Освобождение памяти
                        accountsCurrent[i] = nullptr;
                    }
                    UpdateAllBankAccountsOnUser();
                    return true;
                }
            }
            else {
                cout << "Аккаунта с таким именем не существует!\n";
                break;
            }
        }
    }
    return false;
}

bool UserAccount::DeleteDepositBankAccount(string nameAcc) {
    if (CheckCountOfAccounts() > 0) {
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsDeposit[i] != nullptr) {
                if (accountsDeposit[i]->getNameBankAccount() == nameAcc) {
                    int balanceCurI = accountsDeposit[i]->balanceAccount;
                    if (balanceCurI > 0) {
                        char isC = PressSpecificKey("Вы закрываете счёт, на котором осталось еще " + to_string(balanceCurI) + " руб.!\n1 - Все равно закрыть\n2 - Я передумал(а)\n");
                        if (isC != '1')
                            break;
                    }
                    NoteNewHistory(to_string(idUser) + " депозитный счёт " + accountsDeposit[i]->accountName + " закрыт ");
                    accountsDeposit[i]->idOwner = -1;
                    UpdateDepositBalancesInDataBase();
                    for (int i = 0; i < numOfBankAccounts; ++i) { // Освобождение памяти
                        accountsDeposit[i] = nullptr;
                    }
                    UpdateAllBankAccountsOnUser();
                    return true;
                }
            }
            else {
                cout << "Аккаунта с таким именем не существует!\n";
                break;
            }
        }
    }
    return false;
}

int UserAccount::GetFreeNumOfIdAccount(int type) {
    int freeId = 0;
    string lastLine;
    string freeIdString;

    ifstream in;
    switch (type)
    {
    case 1:
        in.open("CurrentAccounts.txt");
        break;
    case 2:
        in.open("DepositAccounts.txt");
        break;
    case 3:
        in.open("SavingsAccounts.txt");
        break;
    default:
        break;
    }
    if (!in.is_open()) {
        return -1;
    }
    else {
        getline(in, lastLine);
        while (getline(in, lastLine)) {}
        freeIdString = "";

        for (int i = 0; i < lastLine.length(); i++) {
            freeIdString += lastLine[i];
        }
        if (freeIdString == "")
            freeId = 0;
        else
            freeId = atoi(freeIdString.c_str()) + 1;
        return freeId;
    }
    return freeId;
}

bool UserAccount::UpdateAllBankAccountsOnUser() {
    for (int i = 0; i < numOfBankAccounts; ++i) { // Освобождение памяти
        delete accountsCurrent[i];
        delete accountsDeposit[i];
        delete accountsSavings[i];
    }
    ifstream fileCurrent;
    int countAccCurrent = 0;
    ifstream fileDeposit;
    int countAccDeposit = 0;
    ifstream fileSavings;
    int countAccSavings = 0;
    fileCurrent.open("CurrentAccounts.txt");
    fileDeposit.open("DepositAccounts.txt");
    fileSavings.open("SavingsAccounts.txt");
    //to_string(idAccount) + ' ' + to_string(idOwner) + ' ' + accountNumber + ' ' + accountName + ' ' + numOfCard + ' ' + validUntil + ' ' + to_string(balanceAccount)
    string idAccount;
    string idOwner;
    string accountNumber;
    string accountName;
    string numOfCard;
    string validUntil;
    string balanceAccount;
    string interestRate;
    string expirationDate;
    string balance;

    while (fileCurrent >> idAccount >> idOwner >> accountNumber >> accountName >> numOfCard >> validUntil >> balance) {
        if (idOwner == to_string(idUser)) {
            accountsCurrent[countAccCurrent] = new CurrentBankAccount(atoi(idAccount.c_str()), atoi(idOwner.c_str()), accountNumber, accountName, numOfCard, validUntil);
            accountsCurrent[countAccCurrent]->ChangeBalanceOnAccount(getFloatFromString(balance));
            countAccCurrent++;
        }
    }
    while (fileDeposit >> idAccount >> idOwner >> accountNumber >> accountName >> interestRate >> expirationDate >> balance) {
        if (idOwner == to_string(idUser)) {
            accountsDeposit[countAccDeposit] = new DepositBankAccount(atoi(idAccount.c_str()), atoi(idOwner.c_str()), accountNumber, accountName, atoi(interestRate.c_str()), expirationDate);
            accountsDeposit[countAccDeposit]->ChangeBalanceOnAccount(getFloatFromString(balance));
            countAccDeposit++;
        }
    }
    if (fileCurrent.bad() || fileDeposit.bad() || fileSavings.bad())
        cout << "I/O error while reading\n";
    else if (fileCurrent.eof() || fileDeposit.eof() || fileSavings.eof())
        cout << "The end of the file has been reached\n";
    else if (fileCurrent.fail() || fileDeposit.fail() || fileSavings.fail())
        cout << "Invalid data format\n";
    return true;
}

bool UserAccount :: UpdateCurrentBalancesInDataBase(){
    ifstream inputFile("CurrentAccounts.txt");
    vector<string> lines; // Вектор для хранения строк

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << std::endl;
        return false;
    }
    string line;

    int c = 0;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        int firstElement;
        iss >> firstElement; // Считываем первый элемент строки
        for (int i = 0;i < numOfBankAccounts;i++){
            if (accountsCurrent[i] != nullptr && firstElement == (accountsCurrent[i]->idAccount)){
                line = accountsCurrent[i]->getBankAccountInfo();
            }
        }
        if (c > 0) {
            lines.push_back("\n" + line); // Добавляем строку в вектор
        }
        else {
            lines.push_back(line);
        }
        c++;
    }
    inputFile.close();

    ofstream outputFile("CurrentAccounts.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << " для записи." << endl;
        return false;
    }

    for (const auto& updatedLine : lines) {
        outputFile << updatedLine; // Записываем каждую строку
    }

    outputFile.close();
    return true;
}

bool UserAccount::UpdateDepositBalancesInDataBase() {
    ifstream inputFile("DepositAccounts.txt");
    vector<string> lines; // Вектор для хранения строк

    if (!inputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "DepositAccounts.txt" << std::endl;
        return false;
    }
    string line;

    int c = 0;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        int firstElement;
        iss >> firstElement; // Считываем первый элемент строки
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsDeposit[i] != nullptr && firstElement == (accountsDeposit[i]->idAccount)) {
                line = accountsDeposit[i]->getBankAccountInfo();
            }
        }
        if (c > 0) {
            lines.push_back("\n" + line); // Добавляем строку в вектор
        }
        else {
            lines.push_back(line);
        }
        c++;
    }
    inputFile.close();

    ofstream outputFile("DepositAccounts.txt");
    if (!outputFile.is_open()) {
        cerr << "Не удалось открыть файл " << "DepositAccounts.txt" << " для записи." << endl;
        return false;
    }

    for (const auto& updatedLine : lines) {
        outputFile << updatedLine; // Записываем каждую строку
    }

    outputFile.close();
    return true;
}

string UserAccount::generateNewNum(int start, int end, int count) {
    if (count > 0)
        return (to_string(rand() % (end - start + 1) + start)) + generateNewNum(start, end, count - 1);
    else
        return to_string(rand() % (end - start + 1) + start);
}


void UserAccount::PrintInfoBankAccount() {
    cout << "\nCurrentAccounts:\n";
    for (int i = 0; i < numOfBankAccounts; ++i) {
        if (accountsCurrent[i] != nullptr)
            accountsCurrent[i]->PrintAccountInfo();
        else
            break;
    }
    cout << "\nDepositAccounts:\n";
    for (int i = 0; i < numOfBankAccounts; ++i) {
        if (accountsDeposit[i] != nullptr)
            accountsDeposit[i]->PrintAccountInfo();
        else
            break;
    }
    cout << "\nSavingsAccounts:NONE\n";
}
void UserAccount::PrintInfoBankAccount(string name) {
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsCurrent[i] != nullptr && accountsCurrent[i]->getNameBankAccount() == name) {
            accountsCurrent[i]->PrintAccountInfo();
        }
        else
            break;
    }
}

void UserAccount :: PrintLowInfoBankAccount(int type) {
    switch (type)
    {
        case 1:
            cout << "Ваши рассчётные счета: \n";
            for (int i = 0; i < numOfBankAccounts; i++) {
                if (accountsCurrent[i] != nullptr)
                    accountsCurrent[i]->PrintLowBankAccountInfo();
                else
                    break;
            }
            break;
        case 2:
            cout << "\nВаши депозитные счета: \n";
            for (int i = 0; i < numOfBankAccounts; i++) {
                if (accountsDeposit[i] != nullptr)
                    accountsDeposit[i]->PrintLowBankAccountInfo();
                else
                    break;
            }
            break;
        default:
            break;
    }
}

void UserAccount::PrintLowInfoBankAccount() {
    cout << "\nРасчётные счета:\n";
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsCurrent[i] != nullptr)
            accountsCurrent[i]->PrintLowBankAccountInfo();
        else
            break;
    }
    cout << "Депозитные счета:\n";
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsDeposit[i] != nullptr)
            accountsDeposit[i]->PrintLowBankAccountInfo();
        else
            break;
    }
}

int UserAccount::CheckCountOfAccounts() {
    int c = 0;
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsCurrent[i] == nullptr)
            break;
        else
            c++;
    }
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsDeposit[i] == nullptr)
            break;
        else
            c++;
    }
    // for (int i = 0;i < numOfBankAccounts;i++){
    //     if (accountsSavings[i] == nullptr)
    //         break;
    //     else 
    //         c++;
    // }
    return c;
}
int UserAccount::CheckCountOfAccounts(int type) {
    int c = 0;
    switch (type)
    {
    case 1:
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsCurrent[i] == nullptr)
                return c;
            else
                c++;
        }
        break;
    case 2:
        for (int i = 0; i < numOfBankAccounts; i++) {
            if (accountsDeposit[i] == nullptr)
                return c;
            else
                c++;
        }
        break;
    default:
        break;
    }
    return 0;
}


bool UserAccount::DepositOnCurrentBankAccount(int numOfAccount, float sum) {
    if (sum < 0)
        return false;
    if (numOfAccount > -1 && numOfAccount < numOfBankAccounts) {
        if (accountsCurrent[numOfAccount] != nullptr) {
            if (accountsCurrent[numOfAccount]->ChangeBalanceOnAccount(sum)) {
                return true;
            }
        }
        else {
            cout << "No such bankAccount!\n";
            return false;
        }
    }
    return false;
}

bool UserAccount::DepositOnDepositBankAccount(int numOfAccount, float sum) {
    if (sum < 0) {
        cout << "Incorrect cum\n";
        return false;
    }
    if (numOfAccount > -1 && numOfAccount < numOfBankAccounts) {
        if (accountsDeposit[numOfAccount] != nullptr) {
            cout << "Account found\n";
            if (accountsDeposit[numOfAccount]->ChangeBalanceOnAccount(sum)) {
                return true;
            }
        }
        else {
            cout << "No such bankAccount!\n";
            return false;
        }
    }
    else {
        cout << "Incorrect numOfBankAccount\n";
    }
    return false;
}

bool UserAccount::WithdrawOnCurrentBankAccount(int numOfAccount, float sum) {
    if (sum < 0)
        return false;
    if (numOfAccount > -1 && numOfAccount < numOfBankAccounts) {
        if (accountsCurrent[numOfAccount] != nullptr) {
            return accountsCurrent[numOfAccount]->ChangeBalanceOnAccount(-sum);
        }
    }
    return false;
}

bool UserAccount::TransferMoneyOnMyCurrentToCurrentAccounts(int firstAccount, int secondAccount, float countMoney) {
    if (firstAccount >= 0 && secondAccount >= 0 && firstAccount != secondAccount && firstAccount < numOfBankAccounts && secondAccount < numOfBankAccounts) {
        if (WithdrawOnCurrentBankAccount(firstAccount, countMoney)) {
            if (DepositOnCurrentBankAccount(secondAccount, countMoney)) {
                return UpdateCurrentBalancesInDataBase();
            }
            else
                return DepositOnCurrentBankAccount(firstAccount, countMoney);
        }
        else
            return false;
    }
    else
        return false;
}

bool UserAccount::TransferMoneyOnMyCurrentToDepositAccounts(int firstAccount, int secondAccount, float countMoney) {
    if (firstAccount >= 0 && secondAccount >= 0 && firstAccount < numOfBankAccounts && secondAccount < numOfBankAccounts) {
        if (WithdrawOnCurrentBankAccount(firstAccount, countMoney)) {
            if (DepositOnDepositBankAccount(secondAccount, countMoney)) {
                return (UpdateCurrentBalancesInDataBase() && UpdateDepositBalancesInDataBase());
            }
            else
                return DepositOnCurrentBankAccount(firstAccount, countMoney);
        }
        else
            return false;
    }
    else
        return false;
}

bool UserAccount :: TransferToAnotherPerson(string nameInCurrentBankAccount, string phoneOutAccount, float countMoney) {
    int numIdOfCurrentBankAccount = GetIdCurrentBankAccount(nameInCurrentBankAccount);
    int idOutUserAccount = GetIdByPhone(phoneOutAccount);
    if (idOutUserAccount < 0)
        cout << "Неверный номер телефона!\n";
    else if (countMoney <= 0)
        cout << "Введите корректную сумму!\n";
    else if (numIdOfCurrentBankAccount >= 0)
        if (WithdrawOnCurrentBankAccount(numIdOfCurrentBankAccount, countMoney) && UpdateCurrentBalancesInDataBase()) {
            ifstream inputFile("CurrentAccounts.txt");
            vector<string> lines; // Вектор для хранения строк

            if (!inputFile.is_open()) {
                cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << std::endl;
                return false;
            }
            string line;

            int c = 0;

            bool isSent = false;

            while (getline(inputFile, line)) {
                istringstream iss(line);
                string accId;
                string usId;
                string accNum;
                string accName;
                string accNumCard;
                string accValidUntil;
                float accBalance;
             
                iss >> accId >> usId >> accNum >> accName >> accNumCard >> accValidUntil >> accBalance;

                if (usId == to_string(idOutUserAccount) && !isSent) {
                    accBalance += countMoney;
                    isSent = true;
                    NoteNewHistory(to_string(idOutUserAccount) + " получен перевод " + to_string((int)(countMoney)) + " руб. на счёт " + accName + " ");
                }

                line = accId + ' ' + usId + ' ' + accNum + ' ' + accName + ' ' + accNumCard + ' ' + accValidUntil + ' ' + to_string(accBalance);

                if (c > 0) {
                    lines.push_back("\n" + line); // Добавляем строку в вектор
                }
                else {
                    lines.push_back(line);
                }
                c++;
            }
            inputFile.close();

            if (!isSent) {
                cout << "Error isSent!\n";
            }

            ofstream outputFile("CurrentAccounts.txt");
            if (!outputFile.is_open()) {
                cerr << "Не удалось открыть файл " << "CurrentAccounts.txt" << " для записи." << endl;
                return false;
            }

            for (const auto& updatedLine : lines) {
                outputFile << updatedLine; // Записываем каждую строку
            }

            outputFile.close();
            return true;
        }
    return false;
}

int UserAccount::GetBalanceAllBankAccounts(int typeAccount) {
    float acc1 = 0;
    float acc2 = 0;

    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsCurrent[i] == nullptr)
            break;
        acc1 += accountsCurrent[i]->GetBalanceBankAccount();
    }
    for (int i = 0; i < numOfBankAccounts; i++) {
        if (accountsDeposit[i] == nullptr)
            break;
        acc2 += accountsDeposit[i]->GetBalanceBankAccount();
    }

    switch (typeAccount)
    {
    case 0:
        return acc1 + acc2;
        break;
    case 1:
        return acc1;
        break;
    case 2:
        return acc2;
        break;
    default:
        return -1;
        break;
    }
}

UserAccount :: ~UserAccount() {
    for (int i = 0; i < numOfBankAccounts; ++i) { // Освобождение памяти
        delete accountsCurrent[i];
        delete accountsDeposit[i];
        delete accountsSavings[i];
    }
}

int GetIdByPhone(string phoneNumInput) {
    ifstream file;
    file.open("users.txt");
    int idUser;
    string fullNameBase;
    string phoneNumber;

    while (file >> idUser >> fullNameBase >> phoneNumber) {
        if (phoneNumber == phoneNumInput)
            return idUser;
    }
    if (file.bad())
        cout << "Ошибка ввода-вывода при чтении\n";
    else if (file.eof())
        cout << "Достигнут конец файла\n";
    else if (file.fail())
        cout << "Неверный формат данных\n";

    return -1;
}
