#pragma once

#include <string>
using namespace std;

struct Product;

void WriteInFile(Product* Item, int& N, string file, int one = 1);

Product* AddItem(Product* Item, int& N);
Product* DeleteItem(Product* Item, int& N);
void FillItem(Product* Item, int& N, int edit = 0);
void EditItem(Product* Item, int& N);

void PrintItem(Product Item, int i, int sort = 0);
void PrintAll(Product* Item, int& N);
void PrintSort(Product* Item, int& N);

bool AlphabetCompare(char* str1, char* str2);
bool CheckItem(Product Item, int* Date);
void CMD();
void ParseDate(int*);

int input_int(int);
double input_double(double);