#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "UserAccount.h"


void menu(int usId);

void setNewMenu(UserAccount& userAccount);

UserAccount getUserOnId(int usId);

void exit();
bool deleteBankAccount(bool isOneMore, UserAccount& userAccount);

bool TransferMoney(bool isOneMore, UserAccount& userAccount);
bool DepositAccount(bool isOneMore, UserAccount& userAccount);

void CheckHistory(int usId);

void enters(bool oneMore);

int choiceAtString(string s, int fir, int sec, int times);

