#include "pch.h"
#include <cstring>

// bool IsSameWords(char** word, int& amount) 
// ���������, ���� �� � ������� ���� ���������� �����

TEST(Case1, Test2) {
	// � ������� ���� �����

	int amount = 1;
	char** word = new char* [amount];
	word[0] = "AAA";

	EXPECT_EQ(IsSameWords(word, amount), false);
}

TEST(Case2, Test2) {
	// � ������� ��� ������ �����

	int amount = 2;
	char** word = new char* [amount];
	word[0] = "AAA";
	word[1] = "BBB";


	EXPECT_EQ(IsSameWords(word, amount), false);
}

TEST(Case3, Test2) {
	// � ������� 5 ������ ����

	int amount = 5;
	char** word = new char* [amount];
	word[0] = "AAA";
	word[1] = "BBB";
	word[2] = "CCC";
	word[3] = "DDD";
	word[4] = "EEE";

	EXPECT_EQ(IsSameWords(word, amount), false);
}

TEST(Case4, Test2) {
	// � ������� 2 ���������� �����

	int amount = 2;
	char** word = new char* [amount];
	word[0] = "AAA";
	word[1] = "AAA";

	EXPECT_EQ(IsSameWords(word, amount), true);
}

TEST(Case5, Test2) {
	// � ������� 5 ���������� ����

	int amount = 5;
	char** word = new char* [amount];
	word[0] = "AAA";
	word[1] = "AAA";
	word[2] = "AAA";
	word[3] = "AAA";
	word[4] = "AAA";

	EXPECT_EQ(IsSameWords(word, amount), true);
}

TEST(Case6, Test2) {
	// � ������� 5 ����, 2 ����������

	int amount = 5;
	char** word = new char* [amount];
	word[0] = "AAA";
	word[1] = "BBB";
	word[2] = "AAA";
	word[3] = "BBB";
	word[4] = "BBB";

	EXPECT_EQ(IsSameWords(word, amount), true);
}