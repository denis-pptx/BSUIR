#include "pch.h"

// void AddToStraight(char* add, char* straight)
// перевод из дополнительного в прямой 

TEST(Case1, Task2) {

	char add[100] = "0";
	char straight[100];

	AddToStraight(add, straight);
	ASSERT_STREQ(straight, "0");
}

TEST(Case2, Task2) {

	char add[100] = "01100100";
	char straight[100];

	AddToStraight(add, straight);
	ASSERT_STREQ(straight, "01100100");
}

TEST(Case3, Task2) {

	char add[100] = "10011100";
	char straight[100];

	AddToStraight(add, straight);
	ASSERT_STREQ(straight, "11100100");
}