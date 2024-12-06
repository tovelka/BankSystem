#include "DepositBankAccount.h"

DepositBankAccount::DepositBankAccount(int idAccountInput, int idOwnerInput, string accountNumberInput, string accountNameInput, int interestRateInput, string expirationDateInput) :
    BankAccount(idAccountInput, idOwnerInput, accountNumberInput, accountNameInput), interestRate(interestRateInput), expirationDate(expirationDateInput) {}

void DepositBankAccount::PrintAccountInfo() {
    BankAccount::PrintAccountInfo();
    cout << "The expiration of the account at " << interestRate << "% per annum will be on " << expirationDate << endl;
}


string DepositBankAccount::getNameBankAccount() {
    return accountName;
}

string DepositBankAccount::getBankAccountInfo() {
    return to_string(idAccount) + ' ' + to_string(idOwner) + ' ' + accountNumber + ' ' + accountName + ' ' + to_string(interestRate) + ' ' + expirationDate + ' ' + to_string(balanceAccount);
}