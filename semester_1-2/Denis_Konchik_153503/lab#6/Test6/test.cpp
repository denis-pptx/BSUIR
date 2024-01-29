#include "pch.h"

// int anagram(char* str)
// число анаграмм слова

TEST(Case1, Test6) {
	// Мин

	char str[] = "A";
	EXPECT_EQ(anagram(str), 1);
}

TEST(Case2, Test6) {
	// Мин - 1

	char str[] = "";
	EXPECT_EQ(anagram(str), 0);
}

TEST(Case3, Test6) {
	// Мин + 1

	char str[] = "AB";
	EXPECT_EQ(anagram(str), 2);

	strcpy(str, "AA");
	EXPECT_EQ(anagram(str), 1);
}

TEST(Case4, Test6) {
	// Макс

	char str[] = "ABCDEFGHIJKLMO";
	EXPECT_EQ(anagram(str), 87178291200);

	strcpy(str, "AACDEFGHIJKLMO");
	EXPECT_EQ(anagram(str), 43589145600);

	strcpy(str, "AAAAEFGHIJKLMO");
	EXPECT_EQ(anagram(str), 3632428800);
}

TEST(Case5, Test6) {
	// Макс + 1

	char str[] = "ABCDEFGHIJKLMOP";
	EXPECT_EQ(anagram(str), 1307674368000);

	strcpy(str, "AACDEFGHIJKLMOP");
	EXPECT_EQ(anagram(str), 653837184000);

	strcpy(str, "AAAAEFGHIJKLMOP");
	EXPECT_EQ(anagram(str), 54486432000);
}

TEST(Case6, Test6) {
	// Макс - 1

	char str[] = "ABCDEFGHIJKLM";
	EXPECT_EQ(anagram(str), 6227020800);

	strcpy(str, "AACDEFGHIJKLM");
	EXPECT_EQ(anagram(str), 3113510400);

	strcpy(str, "AAAAEFGHIJKLM");
	EXPECT_EQ(anagram(str), 259459200);
}