//
// pch.h
//

#pragma once

#include "gtest/gtest.h"


void Reverse(char* str);
void Input(char* str, const int& size);
int LetterToInt(char x);
int IntToLetter(int x);
int len(char* str);
void Same_Amount(char* num1, char* num2);
void Additional_Zero(char* num, int z);
void DelZero(char* num);
void SameView(char* num1, char* num2);
void DelSign(char* num, char sign);
void AddMinus(char* num);
void FuncSum(char* sum, char* num1, char* num2);
void FuncDifference(char* sum, char* num1, char* num2, bool& n1_bigger_n2);
void copy(char* temp, char* str);
void OperationFunc(char* sum, char* num1, char* num2);