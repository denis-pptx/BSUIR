#pragma once

#include "Human.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Abitur;

Abitur* AddHuman(Abitur*, int&);
Abitur* DeleteHuman(Abitur*, int&);
void EditHuman(Abitur*, int&);

void FillAbitur(Abitur* Human, int& N, int add = 0, int stop = -1);
void PrintAbitur(Abitur*, int&, double mid = -1, int set = -1);
void ChoiceSort(Abitur*, int&);

Abitur* CreateArray(int&);
int input(int start = 1);
int DigitLen(int);
double CountAverage(Abitur*, int&);
void CMD();