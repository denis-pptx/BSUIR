#include "pch.h"

// void ZeroElements(int** array, int& N, int& M, int& amount, int* IndexI, int* IndexJ)
// ������� ���������� ������� ����� � ������� �� �����

TEST(Task3, Case1) {

    // ����� ���, INT_MAX

    int n = 3, m = 4, MAX = INT_MAX;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 0);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}

TEST(Task3, Case2) {

    // ����� ���, INT_MAX - 1

    int n = 3, m = 4, MAX = INT_MAX - 1;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 0);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}

TEST(Task3, Case3) {

    // ����� ���, INT_MAX

    int n = 3, m = 4, MAX = INT_MAX;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 0);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}


TEST(Task3, Case4) {

    // ����� ���, INT_MAX + 1

    int n = 3, m = 4, MAX = INT_MAX + 1;

    int** array = new int* [n];
    array[0] = new int[m] { MAX, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, MAX, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, MAX, MAX };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 0);


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}

TEST(Task3, Case5) {

    // ���� ����, INT_MAX

    int n = 3, m = 4, MAX = INT_MAX;

    int** array = new int* [n];
    array[0] = new int[m] { 0, MAX, MAX, MAX };
    array[1] = new int[m] { MAX, 0, MAX, MAX };
    array[2] = new int[m] { MAX, MAX, 0, MAX };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 3);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                EXPECT_EQ(array[IndexI[i]][IndexJ[j]], 0);
            }
        }
    }


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}

TEST(Task3, Case6) {

    // ���� ����, INT_MIN

    int n = 3, m = 4, MIN = INT_MIN;

    int** array = new int* [n];
    array[0] = new int[m] { 0, MIN, MIN, MIN };
    array[1] = new int[m] { MIN, 0, MIN, MIN };
    array[2] = new int[m] { MIN, MIN, 0, MIN };

    // ������� �����
    int* IndexI = new int[n * m];
    int* IndexJ = new int[n * m];

    // ����� �����
    int amount = 0;

    ZeroElements(array, n, m, amount, IndexI, IndexJ);

    EXPECT_EQ(amount, 3);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) {
                EXPECT_EQ(array[IndexI[i]][IndexJ[j]], 0);
            }
        }
    }


    for (int i = 0; i < n; i++)
        delete[] array[i];
    delete[] array;
    delete[] IndexI;
    delete[] IndexJ;
}