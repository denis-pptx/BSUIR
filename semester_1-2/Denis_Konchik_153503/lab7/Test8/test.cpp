#include "pch.h"

// AnsByNumber(int n)
// двудесятичное число по номеру

TEST(Case1, Task8) {
	EXPECT_EQ(AnsByNumber(1), 1);
}

TEST(Case2, Task8) {
	EXPECT_EQ(AnsByNumber(2), 10);
}

TEST(Case3, Task8) {
	EXPECT_EQ(AnsByNumber(10), 1100);
}

TEST(Case4, Task8) {
	EXPECT_EQ(AnsByNumber(20), 1000000);
}

TEST(Case5, Task8) {
	EXPECT_EQ(AnsByNumber(21), 1000001);
}

TEST(Case6, Task8) {
	EXPECT_EQ(AnsByNumber(30), 1000000000);
}

TEST(Case7, Task8) {
	EXPECT_EQ(AnsByNumber(31), 1000000001);
}