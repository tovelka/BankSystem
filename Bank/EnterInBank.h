#pragma once
#include <iostream>
#include "menuBank.h"

using namespace std;

void sign(bool isNew);

int createUser();
int enterInProfileBankUser();

bool checkSMSCode(bool oneMore, int idUserInput);

int knowOutFreeId();

bool NoteNewHistory(string s);