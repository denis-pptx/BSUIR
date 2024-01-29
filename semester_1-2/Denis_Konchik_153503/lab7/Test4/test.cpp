#include "pch.h"
const int MAX = 100;

char* DIFF(char* number1, char* number2, const int MAX);
char* SUM(char* number1, char* number2, const int MAX);
// Разность и сумма в 19 системе счисления

TEST(Case1, Task4) {
	char* number1 = new char[MAX] {"0"};
	char* number2 = new char[MAX] {"0"};

	ASSERT_STREQ(SUM(number1, number2, MAX), "0");
	ASSERT_STREQ(DIFF(number1, number2, MAX), "0");
}

TEST(Case2, Task4) {
	char* number1 = new char[MAX] {"1A4D7F0HI"};
	char* number2 = new char[MAX] {"1A4D7F0HI"};

	ASSERT_STREQ(SUM(number1, number2, MAX), "3197FB1GH");
	ASSERT_STREQ(DIFF(number1, number2, MAX), "0");
}

TEST(Case3, Task4) {
	char* number1 = new char[MAX] {"-1A4D7F0HI"};
	char* number2 = new char[MAX] {"1A4D7F0HI"};

	ASSERT_STREQ(SUM(number1, number2, MAX), "0");
	ASSERT_STREQ(DIFF(number1, number2, MAX), "-3197FB1GH");
}

TEST(Case4, Task4) {
	char* number1 = new char[MAX] {"1A4D7F0HI"};
	char* number2 = new char[MAX] {"-1A4D7F0HI"};

	ASSERT_STREQ(SUM(number1, number2, MAX), "0");
	ASSERT_STREQ(DIFF(number1, number2, MAX), "3197FB1GH");
}

TEST(Case5, Task4) {
	char* number1 = new char[MAX] {"-1A4D7F0HI"};
	char* number2 = new char[MAX] {"-1A4D7F0HI"};

	ASSERT_STREQ(SUM(number1, number2, MAX), "-3197FB1GH");
	ASSERT_STREQ(DIFF(number1, number2, MAX), "0");
}