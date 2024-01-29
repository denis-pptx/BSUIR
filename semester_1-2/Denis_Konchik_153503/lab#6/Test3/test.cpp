#include "pch.h"

// void FindGrid(char* str)
// # удаляет предыдущую литеру

// Тест из задания

TEST(Case1, Test3) {
	char test[] = "VR##Y#HELO#LO";
	char exp[] = "HELLO";
	EXPECT_STREQ(FindGrid(test), exp);
}

// Без решеток

TEST(Case2, Test3) {
	char test[] = "HELLO";
	char exp[] = "HELLO";
	EXPECT_STREQ(FindGrid(test), exp);
}

// Одна решетка

TEST(Case3, Test3) {
	char test[] = "HEK#LLO";
	char exp[] = "HELLO";
	EXPECT_STREQ(FindGrid(test), exp);
}

TEST(Case4, Test3) {
	char test[] = "#HELLO";
	char exp[] = "HELLO";
	EXPECT_STREQ(FindGrid(test), exp);
}

TEST(Case5, Test3) {
	char test[] = "HELLO#";
	char exp[] = "HELL";
	EXPECT_STREQ(FindGrid(test), exp);
}

// Все решетки

TEST(Case6, Test3) {
	char test[] = "#####";
	char exp[] = "";
	EXPECT_STREQ(FindGrid(test), exp);
}

// Решетки стирают весь текст

TEST(Case7, Test3) {
	char test[] = "HELLO##########";
	char exp[] = "";
	EXPECT_STREQ(FindGrid(test), exp);
}

// Все решетки, кроме одного

TEST(Case8, Test3) {
	
	char test[] = "H####";
	char exp[] = "";

	EXPECT_STREQ(FindGrid(test), exp);
}

TEST(Case9, Test3) {

	char test[] = "####O";
	char exp[] = "O";

	EXPECT_STREQ(FindGrid(test), exp);
}

TEST(Case10, Test3) {

	char test[] = "###L#";
	char exp[] = "";

	EXPECT_STREQ(FindGrid(test), exp);
}