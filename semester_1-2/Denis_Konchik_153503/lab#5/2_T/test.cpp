#include "pch.h"

// bool Half(int* array, int N)
// ��� �� �������� �������������.
// �������� � ������� ������� NegativeCheck �� �������� �������
// ����: ��������, ����� ��� �������� ���� < 0

TEST(Task2, Case1) {
	// ��� �������� �������������, INT_MIN

	int MIN = INT_MIN;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	EXPECT_EQ(Half(array, 5), true);
	delete array;
}

TEST(Task2, Case2) {
	// ��� �������� �������������, INT_MIN + 1

	int MIN = INT_MIN + 1;
	int* array = new int[5]{ MIN, MIN, MIN, MIN, MIN };

	EXPECT_EQ(Half(array, 5), true);
	delete array;
}

TEST(Task2, Case3) {
	// ��� �������� �������������, INT_MAX

	int MAX = INT_MAX;
	int* array = new int[5]{ MAX, MAX, MAX, MAX, MAX };

	EXPECT_EQ(Half(array, 5), false);
	delete array;
}

TEST(Task2, Case4) {
	// ��� �������� �������������, INT_MAX - 1

	int MAX = INT_MAX - 1;
	int* array = new int[5]{ MAX, MAX, MAX, MAX, MAX };

	EXPECT_EQ(Half(array, 5), false);
	delete array;
}

TEST(Task2, Case5) {
	// ��� �������� ������������� INT_MIN,
	// ����� ������ � ������ ���������� INT_MAX

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
	// ��� �������� ������������� INT_MIN + 1,
	// ����� ������ � ������ ���������� INT_MAX - 1

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
