#include "pch.h"

// void min(char* str, int& MinNum, int& MinLen) 
// ������� ������ ����� ����������� ����� � ��� �����

TEST(Case1, Test1) {
	// 81 ������ (���� + 1)
	char str[] = "0000 0000 00000 0000 0000 000000 0000 0000 0000 0000 0000 0000 AA 0000 0000 0000";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 13);
	EXPECT_EQ(MinLen, 2);
}

TEST(Case2, Test1) {
	// 80 �������� (����)
	char str[] = "0000 0000 0000 0000 0000 0000 AA 0000 0000 0000 0000 0000 0000 0000 0000 000000";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 7);
	EXPECT_EQ(MinLen, 2);
}

TEST(Case3, Test1) {
	// 79 �������� (���� - 1)
	char str[] = "0000 A 0000 00000 0000 00000 00000 00000 0000 0000 00000 0000 0000 0000 000000";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 2);
	EXPECT_EQ(MinLen, 1);
}

TEST(Case4, Test1) {
	// 1 ������ (���)
	char str[] = "A";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 1);
	EXPECT_EQ(MinLen, 1);
}



TEST(Case5, Test1) {
	// 2 ������� (��� + 1)
	char str[] = "AA";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 1);
	EXPECT_EQ(MinLen, 2);
}

TEST(Case6, Test1) {
	// 0 �������� (��� - 1)
	char str[] = "";
	int MinNum, MinLen = 0;

	min(str, MinNum, MinLen);

	EXPECT_EQ(MinNum, 0);
	EXPECT_EQ(MinLen, 0);
}