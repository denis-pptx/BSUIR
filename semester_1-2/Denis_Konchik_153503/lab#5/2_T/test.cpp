#include "pch.h"

// bool Half(int* array, int N)
// Все ли элементы отрицательные.
// Передает в оновную функцию NegativeCheck по половине массива
// итог: проверка, чтобы все элементы были < 0

TEST(Task2, Case1) {
	// Все элементы отрицательные, INT_MIN

	int MIN = INT_MIN;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	EXPECT_EQ(Half(array, 5), true);
	delete array;
}

TEST(Task2, Case2) {
	// Все элементы отрицательные, INT_MIN + 1

	int MIN = INT_MIN + 1;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	EXPECT_EQ(Half(array, 5), true);
	delete array;
}

TEST(Task2, Case3) {
	// Все элементы положительные, INT_MAX

	int MAX = INT_MAX;
	int* array = new int[5]{ MAX, MAX, MAX, MAX, MAX };

	EXPECT_EQ(Half(array, 5), false);
	delete array;
}

TEST(Task2, Case4) {
	// Все элементы положительные, INT_MAX - 1

	int MAX = INT_MAX - 1;
	int* array = new int[5]{ MAX, MAX, MAX, MAX, MAX };

	EXPECT_EQ(Half(array, 5), false);
	delete array;
}

TEST(Task2, Case5) {
	// Все элементы отрицательные INT_MIN,
	// кроме одного в разных положениях INT_MAX

	int MIN = INT_MIN;
	int MAX = INT_MAX;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	for (int i = 0; i < 5; i++) {
		array[i] = MAX;
		EXPECT_EQ(Half(array, 5), false);
		array[i] = MIN;
	}

	delete array;
}

TEST(Task2, Case6) {
	// Все элементы отрицательные INT_MIN + 1,
	// кроме одного в разных положениях INT_MAX - 1

	int MIN = INT_MIN + 1;
	int MAX = INT_MAX - 1;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	for (int i = 0; i < 5; i++) {
		array[i] = MAX;
		EXPECT_EQ(Half(array, 5), false);
		array[i] = MIN;
	}

	delete array;
}
