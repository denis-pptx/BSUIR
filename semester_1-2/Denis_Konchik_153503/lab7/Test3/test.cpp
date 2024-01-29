#include "pch.h"


// void Operation(char**, char*)
// ����� �������� ����� � ������������ �����

TEST(Case1, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "0" };
    number[1] = new char[100]{ "0" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "0");
}

TEST(Case2, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "1" };
    number[1] = new char[100]{ "0" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "1");
}


TEST(Case3, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "10101" };
    number[1] = new char[100]{ "10101" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "101010");
}

TEST(Case4, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "-10101" };
    number[1] = new char[100]{ "10101" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "0");
}

TEST(Case5, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "10101" };
    number[1] = new char[100]{ "-10101" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "0");
}

TEST(Case6, Task3) {

    char** number = new char* [2]; // ������������
    number[0] = new char[100]{ "-10101" };
    number[1] = new char[100]{ "-10101" };

    char sum[100]; // �����
    Operation(number, sum);

    ASSERT_STREQ(sum, "-101010");
}