//
// pch.h
//

#pragma once
#include <cstring>
using namespace std;
#include "gtest/gtest.h"

string ToTernaryStr(int);
string ElseTernary(int);
int len(string);
int find(string, string);
void replace(string&, int, string);
void erase(string&, int);