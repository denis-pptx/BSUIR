#include "pch.h"

// int Foo(int n)
// наибольший нечетный делитель натурального числа n


TEST(Add3, Case1) {
	// Для нечетных чисел ответ само число

	EXPECT_EQ(Foo(INT_MAX), INT_MAX);
	EXPECT_EQ(Foo(INT_MAX - 2), INT_MAX - 2);

	EXPECT_EQ(Foo(1), 1);
	EXPECT_EQ(Foo(3), 3);
	EXPECT_EQ(Foo(5), 5);
}

TEST(Add3, Case2) {
	// Для 2^n ответ 1

	EXPECT_EQ(Foo(1073741824), 1); // 2^30
	EXPECT_EQ(Foo(536870912), 1);  // 2^29

	EXPECT_EQ(Foo(1), 1); // 2^0
	EXPECT_EQ(Foo(2), 1); // 2^1
	EXPECT_EQ(Foo(4), 1); // 2^2

}

TEST(Add3, Case3) {
	// Для x * 2^n ответ x, x - простое, x≠2

	EXPECT_EQ(Foo(3 * 536870912), 3); // 3 * 2^29
	EXPECT_EQ(Foo(3 * 268435456), 3); // 3 * 2^28

	EXPECT_EQ(Foo(3 * 1), 3); // 3 * 2^0
	EXPECT_EQ(Foo(3 * 2), 3); // 3 * 2^1
	EXPECT_EQ(Foo(3 * 4), 3); // 3 * 2^2

}
