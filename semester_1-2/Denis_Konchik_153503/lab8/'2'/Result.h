#pragma once
#include "Product.h"


bool AlphabetCompare(char* str1, char* str2);
bool CheckItem(Product Item, int* Date);
void PrintSort(Product* Item);
void WriteResult(Product* OutputItem, int oi, bool clear = 0);