#include "pch.h"
#include <cstring>
using namespace std;

// string ElseTernary(int);
// перевод в смещенную троичную систему

TEST(Case1, Task9) {
	EXPECT_EQ(ElseTernary(7), "21");
}

TEST(Case2, Task9) {
	EXPECT_EQ(ElseTernary(22), "211");
}

TEST(Case3, Task9) {
	EXPECT_EQ(ElseTernary(497), "111332");
}

/*
TEST(Case4, Task9) {
	EXPECT_EQ(ElseTernary(19846), "111311131");
}

TEST(Case5, Task9) {
	EXPECT_EQ(ElseTernary(219219), "31133113313");
}
*/