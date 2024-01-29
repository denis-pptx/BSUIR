#include "pch.h"

// bool check(char* s, char* t)
// можно ли фишкой из s получить t

// Тесты из условия

TEST(Case1, Test8) {
	char s[] = "abcdef";
	char t[] = "cdedcb";

	EXPECT_EQ(check(s,t), true);
}

TEST(Case2, Test8) {
	char s[] = "aaa";
	char t[] = "aaaaa";

	EXPECT_EQ(check(s, t), true);
}

TEST(Case3, Test8) {
	char s[] = "aab";
	char t[] = "baaa";

	EXPECT_EQ(check(s, t), false);
}

TEST(Case4, Test8) {
	char s[] = "ab";
	char t[] = "b";

	EXPECT_EQ(check(s, t), true);
}

TEST(Case5, Test8) {
	char s[] = "abcdef";
	char t[] = "abcdef";

	EXPECT_EQ(check(s, t), true);
}

TEST(Case6, Test8) {
	char s[] = "ba";
	char t[] = "baa";

	EXPECT_EQ(check(s, t), false);
}

TEST(Case7, Test8) {
	// Мин

	char s[] = "a";
	char t[] = "a";
	EXPECT_EQ(check(s, t), true);

	strcpy(s, "b");
	strcpy(t, "a");
	EXPECT_EQ(check(s, t), false);
}

TEST(Case8, Test8) {
	// Мин + 1

	char s[] = "ab";
	char t[] = "ba";
	EXPECT_EQ(check(s, t), true);

	strcpy(s, "aa");
	strcpy(t, "ab");
	EXPECT_EQ(check(s, t), false);
}

TEST(Case9, Test8) {
	// Мин - 1

	char s[] = "";
	char t[] = "";
	EXPECT_EQ(check(s, t), false);
}