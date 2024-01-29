#include "pch.h"

// void DiagonalEvenFill(int** array, int* EvenDiagonal, int &N, int &M, int &EvenAmount)
// Заполняет созданный массив размером N четными элементами главной диагонали

TEST(Task3_1, Case1) {
	// Все искомые элементы нечетные, INT_MAX

	int n = 3, m = 4, MAX = INT_MAX;

	int** array = new int* [n];
	array[0] = new int[m] {MAX, MAX, MAX, MAX};
	array[1] = new int[m] {MAX, MAX, MAX, MAX};
	array[2] = new int[m] {MAX, MAX, MAX, MAX};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 0);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case2) {
	// Все искомые элементы нечетные, INT_MAX - 2

	int n = 3, m = 4, MAX = INT_MAX - 2;

	int** array = new int* [n];
	array[0] = new int[m] {MAX, MAX, MAX, MAX};
	array[1] = new int[m] {MAX, MAX, MAX, MAX};
	array[2] = new int[m] {MAX, MAX, MAX, MAX};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 0);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case3) {
	// Все искомые элементы нечетные, INT_MIN + 1

	int n = 3, m = 4, MIN = INT_MIN + 1;

	int** array = new int* [n];
	array[0] = new int[m] {MIN, MIN, MIN, MIN};
	array[1] = new int[m] {MIN, MIN, MIN, MIN};
	array[2] = new int[m] {MIN, MIN, MIN, MIN};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 0);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case4) {
	// Все искомые элементы нечетные, INT_MIN + 3

	int n = 3, m = 4, MIN = INT_MIN + 1;

	int** array = new int* [n];
	array[0] = new int[m] {MIN, MIN, MIN, MIN};
	array[1] = new int[m] {MIN, MIN, MIN, MIN};
	array[2] = new int[m] {MIN, MIN, MIN, MIN};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 0);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case5) {
	// Все искомые элементы четные, INT_MAX - 1

	int n = 3, m = 4, MAX = INT_MAX - 1;

	int** array = new int* [n];
	array[0] = new int[m] {MAX, MAX, MAX, MAX};
	array[1] = new int[m] {MAX, MAX, MAX, MAX};
	array[2] = new int[m] {MAX, MAX, MAX, MAX};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 3);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case6) {
	// Все искомые элементы четные, INT_MAX - 3

	int n = 3, m = 4, MAX = INT_MAX - 1;

	int** array = new int* [n];
	array[0] = new int[m] {MAX, MAX, MAX, MAX};
	array[1] = new int[m] {MAX, MAX, MAX, MAX};
	array[2] = new int[m] {MAX, MAX, MAX, MAX};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 3);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case7) {
	// Все искомые элементы четные, INT_MIN

	int n = 3, m = 4, MIN = INT_MIN;

	int** array = new int* [n];
	array[0] = new int[m] {MIN, MIN, MIN, MIN};
	array[1] = new int[m] {MIN, MIN, MIN, MIN};
	array[2] = new int[m] {MIN, MIN, MIN, MIN};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 3);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}

TEST(Task3_1, Case8) {
	// Все искомые элементы четные, INT_MIN + 2

	int n = 3, m = 4, MIN = INT_MIN;

	int** array = new int* [n];
	array[0] = new int[m] {MIN, MIN, MIN, MIN};
	array[1] = new int[m] {MIN, MIN, MIN, MIN};
	array[2] = new int[m] {MIN, MIN, MIN, MIN};

	int* EvenDiagonal = new int[n];
	int EvenAmount = 0;

	DiagonalEvenFill(array, EvenDiagonal, n, m, EvenAmount);

	EXPECT_EQ(EvenAmount, 3);


	delete[] EvenDiagonal;
	for (int i = 0; i < n; i++)
		delete array[i];
	delete[] array;
}