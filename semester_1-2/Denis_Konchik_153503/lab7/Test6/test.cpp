#include "pch.h"

TEST(Case1, Task6) {
	// Ã»Õ
	EXPECT_EQ(FuncAns(1), 0);
}

TEST(Case2, Task6) {
	// Ã»Õ + 1
	EXPECT_EQ(FuncAns(1), 0);
}

TEST(Case3, Task6) {
	// Ã»Õ - 1
	EXPECT_EQ(FuncAns(1), 0);
}

TEST(Case4, Task6) {
	EXPECT_EQ(FuncAns(9), 1);
}

TEST(Case5, Task6) {
	EXPECT_EQ(FuncAns(10), 1);
}

TEST(Case6, Task6) {
	EXPECT_EQ(FuncAns(34), 3);
}

TEST(Case7, Task6) {
	EXPECT_EQ(FuncAns(880055535), 88005553);
}

TEST(Case8, Task6) {
	// MAX
	EXPECT_EQ(FuncAns(1000000000), 100000000);
}

TEST(Case9, Task6) {
	// MAX - 1
	EXPECT_EQ(FuncAns(999999999), 100000000);
}

TEST(Case10, Task6) {
	// MAX + 1
	EXPECT_EQ(FuncAns(1000000001), 100000000);
}