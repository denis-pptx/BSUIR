#include "pch.h"

// MaxStr(char* str)
// макс длина подстроки не палиндрома

TEST(Case0, Test7) {
	// Из условия
	char str[] = "aba";
	EXPECT_EQ(MaxStr(str), 2);
}
TEST(Case1, Test7) {
	// Мин
	char str[] = "a";
	EXPECT_EQ(MaxStr(str), -1);
}

TEST(Case2, Test7) {
	// Мин + 1
	char str[] = "ab";
	EXPECT_EQ(MaxStr(str), 2);

	strcpy(str, "aa");
	EXPECT_EQ(MaxStr(str), -1);
}

TEST(Case3, Test7) {
	// Мин - 1
	char str[] = "";
	EXPECT_EQ(MaxStr(str), -1);
}

TEST(Case4, Test7) {
	// Макс
	char str[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcadefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	EXPECT_EQ(MaxStr(str), 105);

	strcpy(str, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	EXPECT_EQ(MaxStr(str), -1);
}

TEST(Case5, Test7) {
	// Макс + 1
	char str[] = "abcdefghijklmnopqrstuvwxyazabcdefghijklmnopqrstuvwxyzabcadefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	EXPECT_EQ(MaxStr(str), 106);

	strcpy(str, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	EXPECT_EQ(MaxStr(str), -1);
}

TEST(Case6, Test7) {
	// Макс - 1
	char str[] = "abcdefghijklmnopqrtuvwxyzabcdefghijklmnopqrstuvwxyzabcadefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	EXPECT_EQ(MaxStr(str), 104);

	strcpy(str, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	EXPECT_EQ(MaxStr(str), -1);
}

// рандомные кейсы

TEST(Case7, Test7) {
	char str[] = "abcdefgfedcba";
	EXPECT_EQ(MaxStr(str), 12);
}

TEST(Case8, Test7) {
	char str[] = "abccbaq";
	EXPECT_EQ(MaxStr(str), 7);
}

TEST(Case9, Test7) {
	char str[] = "abcdefghijklmnopqrstuvvutsrqponmlkjihgfedcba";
	EXPECT_EQ(MaxStr(str), 43);
}