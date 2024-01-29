#include "pch.h"

// void sort_columns(int** array, int* mass, int& N, int& M, long long& sum, int& amount)
// ������� ���������� � ������ mass �������� �������� �� ������ �������� ������� array
// amount - ����� ���� ���������, sum - �� �����

TEST(Task3_3, Case1) {
    // ��� �������� ��������, INT_MAX

    int n = 3, m = 4, MAX = INT_MAX;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 6);
    EXPECT_EQ(sum, 6 * (long long)MAX);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case2) {
    // ��� �������� ��������, INT_MAX - 2

    int n = 3, m = 4, MAX = INT_MAX - 2;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 6);
    EXPECT_EQ(sum, 6 * (long long)MAX);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case3) {
    // ��� �������� ��������, INT_MIN + 1

    int n = 3, m = 4, MIN = INT_MIN + 1;

    int** array = new int* [n];
    array[0] = new int[m] { MIN, MIN, MIN, MIN };
    array[1] = new int[m] { MIN, MIN, MIN, MIN };
    array[2] = new int[m] { MIN, MIN, MIN, MIN };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 6);
    EXPECT_EQ(sum, 6 * (long long)MIN);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case4) {
    // ��� �������� ��������, INT_MIN + 3

    int n = 3, m = 4, MIN = INT_MIN + 1;

    int** array = new int* [n];
    array[0] = new int[m] { MIN, MIN, MIN, MIN };
    array[1] = new int[m] { MIN, MIN, MIN, MIN };
    array[2] = new int[m] { MIN, MIN, MIN, MIN };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 6);
    EXPECT_EQ(sum, 6 * (long long)MIN);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}



TEST(Task3_3, Case5) {
    // ��� �������� ������, INT_MAX - 1

    int n = 3, m = 4, MAX = INT_MAX - 1;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 0);

    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case6) {
    // ��� �������� ������, INT_MAX - 3

    int n = 3, m = 4, MAX = INT_MAX - 3;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 0);

    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case7) {
    // ��� �������� ������, INT_MIN

    int n = 3, m = 4, MIN = INT_MIN;

    int** array = new int* [n];
    array[0] = new int[m] { MIN, MIN, MIN, MIN };
    array[1] = new int[m] { MIN, MIN, MIN, MIN };
    array[2] = new int[m] { MIN, MIN, MIN, MIN };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 0);

    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}

TEST(Task3_3, Case8) {
    // ��� �������� ��������, INT_MIN

    int n = 3, m = 4, MIN = INT_MIN + 2;

    int** array = new int* [n];
    array[0] = new int[m] { MIN, MIN, MIN, MIN };
    array[1] = new int[m] { MIN, MIN, MIN, MIN };
    array[2] = new int[m] { MIN, MIN, MIN, MIN };

    // ����� � ���������� ���������
    long long sum = 0;
    int amount = 0;

    // ������ ��� �������� ��������� � ������ ��������
    int* mass = new int[n * (m / 2)];

    sort_columns(array, mass, n, m, sum, amount);

    EXPECT_EQ(amount, 0);

    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] mass;

}