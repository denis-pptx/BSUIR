#pragma once
#include "Human.h"

void strget(string&);
double input(string);
bool IsEmpty();
void cmd();
int IndexByTabel(Human*, string);

void PrintEmployee(Human*);
void EditEmployee(Human*);
Human* AddEmployee(Human*);
Human* DelEmployee(Human*);
Human* DelAll(Human*);
