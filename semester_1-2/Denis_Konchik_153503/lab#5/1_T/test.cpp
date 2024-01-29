#include "pch.h"

// bool Saddle(int** array, int i, int j, int M, int N)
// Седловая точка - наименьший в строке, наибольший в столбце


TEST(Task1, Case1) {
	// Все элементы седловые точки, INT_MAX

	int n = 3, m = 4, MAX = INT_MAX;

	int** array = new int* [n];
	array[0] = new int[m] { MAX, MAX, MAX, MAX };
	array[1] = new int[m] { MAX, MAX, MAX, MAX };
	array[2] = new int[m] { MAX, MAX, MAX, MAX };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			EXPECT_EQ(Saddle(array, i, j, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case2) {
	// Все элементы седловые точки, INT_MAX - 1

	int n = 3, m = 4, MAX = INT_MAX - 1;

	int** array = new int* [n];
	array[0] = new int[m] { MAX, MAX, MAX, MAX };
	array[1] = new int[m] { MAX, MAX, MAX, MAX };
	array[2] = new int[m] { MAX, MAX, MAX, MAX };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			EXPECT_EQ(Saddle(array, i, j, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case3) {
	// Все элементы седловые точки, INT_MIN

	int n = 3, m = 4, MIN = INT_MIN;

	int** array = new int* [n];
	array[0] = new int[m] { MIN, MIN, MIN, MIN };
	array[1] = new int[m] { MIN, MIN, MIN, MIN };
	array[2] = new int[m] { MIN, MIN, MIN, MIN };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			EXPECT_EQ(Saddle(array, i, j, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case4) {
	// Все элементы седловые точки, INT_MIN + 1

	int n = 3, m = 4, MIN = INT_MIN + 1;

	int** array = new int* [n];
	array[0] = new int[m] { MIN, MIN, MIN, MIN };
	array[1] = new int[m] { MIN, MIN, MIN, MIN };
	array[2] = new int[m] { MIN, MIN, MIN, MIN };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			EXPECT_EQ(Saddle(array, i, j, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case5) {
	// Седловая точка одна, INT_MAX

	int n = 3, m = 4, MAX = INT_MAX;

	int** array = new int* [n];
	array[0] = new int[m] { MAX - 1, MAX, MAX, MAX };
	array[1] = new int[m] { MAX - 2, MAX, MAX, MAX };
	array[2] = new int[m] { MAX - 2, MAX, MAX, MAX };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!(i == 0 && j == 0)) 
				EXPECT_EQ(Saddle(array, i, j, n, m), false);
	EXPECT_EQ(Saddle(array, 0, 0, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case6) {
	// Седловая точка одна, INT_MAX - 1

	int n = 3, m = 4, MAX = INT_MAX - 1;

	int** array = new int* [n];
	array[0] = new int[m] { MAX - 1, MAX, MAX, MAX };
	array[1] = new int[m] { MAX - 2, MAX, MAX, MAX };
	array[2] = new int[m] { MAX - 2, MAX, MAX, MAX };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!(i == 0 && j == 0))
				EXPECT_EQ(Saddle(array, i, j, n, m), false);
	EXPECT_EQ(Saddle(array, 0, 0, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case7) {
	// Седловая точка одна, INT_MIN

	int n = 3, m = 4, MIN = INT_MIN;

	int** array = new int* [n];
	array[0] = new int[m] { MIN + 1, MIN + 2, MIN + 2, MIN + 2 };
	array[1] = new int[m] { MIN, MIN, MIN, MIN };
	array[2] = new int[m] { MIN, MIN, MIN, MIN };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!(i == 0 && j == 0))
				EXPECT_EQ(Saddle(array, i, j, n, m), false);
	EXPECT_EQ(Saddle(array, 0, 0, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}

TEST(Task1, Case8) {
	// Седловая точка одна, INT_MIN + 1

	int n = 3, m = 4, MIN = INT_MIN + 1;

	int** array = new int* [n];
	array[0] = new int[m] { MIN + 1, MIN + 2, MIN + 2, MIN + 2 };
	array[1] = new int[m] { MIN, MIN, MIN, MIN };
	array[2] = new int[m] { MIN, MIN, MIN, MIN };

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!(i == 0 && j == 0))
				EXPECT_EQ(Saddle(array, i, j, n, m), false);
	EXPECT_EQ(Saddle(array, 0, 0, n, m), true);

	for (int i = 0; i < n; i++)
		delete[] array[i];
	delete array;
}
