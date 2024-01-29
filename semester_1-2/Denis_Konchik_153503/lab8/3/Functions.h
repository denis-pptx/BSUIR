#pragma once
#include "Human.h"

void strget(string&);
void strget(char* str);
double input(string);
bool IsEmpty();
void cmd();
int IndexByTabel(Human* Employee, char* tabel);

void PrintEmployee(Human*);
void EditEmployee(Human*);
Human* AddEmployee(Human*);
Human* DelEmployee(Human*);
Human* DelAll(Human*);
