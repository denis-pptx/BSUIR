#include "pch.h"

// int FuncVar(int L, int M, char* S1, char* S2)

// Значения из условия

TEST(Case1, Test5) {
	int L = 14, M = 1000;
	char S1[] = "cup";
	char S2[] = "russia";

	EXPECT_EQ(FuncVar(L, M, S1, S2), 752);
}

TEST(Case2, Test5) {
	int L = 7, M = 123;
	char S1[] = "russian";
	char S2[] = "codecup";

	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);
}

TEST(Case3, Test5) {
	int L = 7, M = 15;
	char S1[] = "codec";
	char S2[] = "decup";

	EXPECT_EQ(FuncVar(L, M, S1, S2), 1);
}

TEST(Case4, Test5) {
	// Мин

	int L = 1, M = 1;

	char S1[] = "a";
	char S2[] = "a";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);

	strcpy(S1, "a");
	strcpy(S1, "b");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);
}

TEST(Case5, Test5) {
	// Мин - 1

	int L = 0, M = 0;

	char S1[] = "";
	char S2[] = "";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);

}

TEST(Case6, Test5) {
	// Мин + 1

	int L = 2, M = 2;

	char S1[] = "ab";
	char S2[] = "cd";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);

	strcpy(S1, "a");
	strcpy(S1, "b");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);

	strcpy(S1, "ab");
	strcpy(S1, "c");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 1);
}

TEST(Case7, Test5) {
	// Макс

	int L = 109, M = 104;

	char S1[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char S2[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);


	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(S2, "baavaccd");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 2);

	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz");
	strcpy(S2, "baavaccaa");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 1);

}

TEST(Case8, Test5) {
	// Макс + 1

	int L = 110, M = 105;

	char S1[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char S2[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);


	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(S2, "baavacvcd");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 2);

	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz");
	strcpy(S2, "baavvaccaa");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 1);

}

TEST(Casse8, Test5) {
	// Макс - 1

	int L = 108, M = 103;

	char S1[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char S2[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	EXPECT_EQ(FuncVar(L, M, S1, S2), 0);


	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	strcpy(S2, "baavaccd");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 2);

	strcpy(S1, "aaaahhjjjjjjjjjjjjjjjjjjvhhhhhhhhhhhaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaz");
	strcpy(S2, "baavaccaa");
	EXPECT_EQ(FuncVar(L, M, S1, S2), 1);

}