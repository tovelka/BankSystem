#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>
#include "CurrentBankAccount.h"
#include "DepositBankAccount.h"

using namespace std;

class UserAccount {
private:
    const static int numOfBankAccounts = 10;
    string fullNameUser;
    string phoneUser;
    CurrentBankAccount* accountsCurrent[numOfBankAccounts];
    DepositBankAccount* accountsDeposit[numOfBankAccounts];
    CurrentBankAccount* accountsSavings[numOfBankAccounts];

public:
    int idUser;

    UserAccount(int idUser, string fullNameUserInput, string phoneUserInput);
    UserAccount();

    void PrintUserAccountInfo();
    void PrintInfoBankAccount();
    void PrintInfoBankAccount(string name);
    void PrintLowInfoBankAccount(int type);
    void PrintLowInfoBankAccount();
    string GetFullNameUser();

    bool UpdateAllBankAccountsOnUser();
    bool UpdateCurrentBalancesInDataBase();
    bool UpdateDepositBalancesInDataBase();
    bool AddNewBankAccount(int type, string name);
    bool DeleteCurrentBankAccount(string nameAcc);
    bool DeleteDepositBankAccount(string nameAcc);
    bool NoteNewAccount(CurrentBankAccount& bankAccount);
    bool NoteNewAccount(DepositBankAccount& bankAccount);
    bool NoteNewHistory( string s);

    bool TransferMoneyOnMyCurrentToCurrentAccounts(int firstAccount, int secondAccount, float countMoney);
    bool TransferMoneyOnMyCurrentToDepositAccounts(int firstAccount, int secondAccount, float countMoney);
    bool TransferToAnotherPerson(string nameInCurrentBankAccount,string phoneOutAccount, float countMoney);
    //bool NoteNewAccount(SavingsBankAccount bankAccount);

    bool ExistNameCurrentBankAccount(string nameAcc);
    int GetIdCurrentBankAccount(string nameAcc);
    int GetIdDepositBankAccount(string nameAcc);

    int CheckCountOfAccounts();
    int CheckCountOfAccounts(int type);
    int GetFreeNumOfIdAccount(int type);

    bool DepositOnCurrentBankAccount(int numOfAccount, float sum);
    bool WithdrawOnCurrentBankAccount(int numOfBankAccount, float sum);
    bool DepositOnDepositBankAccount(int numOfAccount, float sum);
    int GetBalanceAllBankAccounts(int typeAccount);
    //void DeleteAccount();

    string generateNewNum(int start, int end, int count);
    ~UserAccount();
};

int GetIdByPhone(string phoneNumInput);