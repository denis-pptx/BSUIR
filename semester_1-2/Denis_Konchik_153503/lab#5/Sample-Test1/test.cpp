#include "pch.h"

int sum(int a, int b) {
	return a - b;
}

TEST(TestCaseName, TestName) {
	EXPECT_EQ(sum(10,5), 15);
}