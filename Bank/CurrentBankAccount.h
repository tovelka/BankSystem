#pragma once
#include "BankAccount.h"

class CurrentBankAccount : public BankAccount {

public:
    string numOfCard;
    string validUntil;

    CurrentBankAccount(int idAccountInput, int idOwnerInput, string accountNumberInput, string accountNameInput, string numCardInput, string validUntilInput);

    string getNameBankAccount();
    string getBankAccountInfo();

    void PrintAccountInfo();
};