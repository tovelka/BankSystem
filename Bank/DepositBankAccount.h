#pragma once
#include "BankAccount.h"

class DepositBankAccount : public BankAccount {

public:
    int interestRate;
    string expirationDate;

    DepositBankAccount(int idAccountInput, int idOwnerInput, string accountNameInput, string accountNumberInput, int interestRateInput, string expirationDateInput);

    void PrintAccountInfo();
    string getNameBankAccount();
    string getBankAccountInfo();
};