#pragma once

#include "Human.h"

Human* LoadFromFile(Human* Employee);
void WriteDelete(Human* Employee, int num);
void WriteAddEdit(Human* Employee, int num);
void PrintFile();
void ClearFile();
void CheckOpen();