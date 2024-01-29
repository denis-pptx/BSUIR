#include "pch.h"

// isDivide(int a, int b)
// делится ли a на b
// 3, 23, 107

TEST(Case1, Task7) {
	EXPECT_TRUE(isDivide(3,3));
	//EXPECT_EQ(isDivide(-3, 3), true);
	EXPECT_TRUE(isDivide(-3, 3));
}

TEST(Case2, Task7) {
	EXPECT_TRUE(isDivide(23, 23));
	EXPECT_TRUE(isDivide(-23, 23));
}

TEST(Case3, Task7) {
	EXPECT_TRUE(isDivide(107, 107));
	EXPECT_TRUE(isDivide(-107, 107));
}

TEST(Case4, Task7) {
	EXPECT_TRUE(isDivide(3 * 23 * 107, 3));
	EXPECT_TRUE(isDivide(3 * 23 * 107, 23));
	EXPECT_TRUE(isDivide(3 * 23 * 107, 107));
}

TEST(Case5, Task7) {
	EXPECT_FALSE(isDivide(3 * 23, 107));
	EXPECT_FALSE(isDivide(3 * 107, 23));
	EXPECT_FALSE(isDivide(23 * 107, 3));
}