#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

class BankAccount {
public:
	int idAccount;
	int idOwner;
	string accountNumber;
	string accountName;
	float balanceAccount = 0;

	BankAccount(int idAccount, int idOwnerInput, string accountNumberInput, string accountName);
	void PrintAccountInfo();
	void PrintLowBankAccountInfo();

	float GetBalanceBankAccount();
	bool ChangeBalanceOnAccount(float sum);
};

float getFloatFromString(string s);
void PressEnter();
char PressSpecificKey(string s);
const string currentDateTime();
float roundVar(float var);