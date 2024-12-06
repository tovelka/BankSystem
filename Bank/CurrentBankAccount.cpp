#include "CurrentBankAccount.h"

CurrentBankAccount::CurrentBankAccount(int idAccountInput, int idOwnerInput, string accountNumberInput, string accountNameInput, string numCardInput, string validUntilInput) :
    BankAccount(idAccountInput, idOwnerInput, accountNumberInput, accountNameInput), numOfCard(numCardInput), validUntil(validUntilInput) {}

void CurrentBankAccount::PrintAccountInfo() {
    BankAccount::PrintAccountInfo();
    cout << "Card until " << validUntil << " - " << numOfCard << endl;
}


string CurrentBankAccount::getNameBankAccount() {
    return accountName;
}

string CurrentBankAccount::getBankAccountInfo() {
    return to_string(idAccount) + ' ' + to_string(idOwner) + ' ' + accountNumber + ' ' + accountName + ' ' + numOfCard + ' ' + validUntil + ' ' + to_string(balanceAccount);
}