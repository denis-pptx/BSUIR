#pragma once
#include "Product.h"


void strget(char*);
void strget(string&);
double input(string);
void InputDate(int* date, string repeat);

int IndexByNum(Product* Item, char* num);
bool IsEmpty();
void cmd();

void PrintItem(Product* Item);
void EditItem(Product* Item);
Product* AddItem(Product* Item);
Product* DelItem(Product* Item);
Product* DelAll(Product* Item);


