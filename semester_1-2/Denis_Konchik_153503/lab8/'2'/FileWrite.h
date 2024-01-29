#pragma once

#include "Product.h"

void CheckOpen();
Product* LoadFromFile(Product* Item);
void ClearFile();
void WriteAddEdit(Product* Item, int num);
void WriteDelete(Product* Item, int index);
//void PrintFile();