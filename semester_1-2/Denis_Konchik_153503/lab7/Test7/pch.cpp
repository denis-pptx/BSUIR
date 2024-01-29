//
// pch.cpp
//

#include "pch.h"

bool isDivide(int a, int b) {

    a = a < 0 ? -a : a;

    int k = divide(a, b); // a : b

    int S = 0; // ����� k ����� var
    for (int j = 0; j < k; j = Sum(j, 1))
        S = Sum(S, b);

    return S == a ? true : false;
}


int divide(int a, int b) {
    // �������� �� ����� ���� 0
    if (b == 0) {
        exit(0);
    }

    // ��������� ����� ������
    bool Negative = false;
    if (getSign(a) ^ getSign(b)) // �������� ���� ����������
        Negative = true;

    // ������ �����
    a = module(a);
    b = module(b);

    // �����
    int answer = 0;

    // answer - ������� ��� ����� ������� b �� a
    while (a >= b) {
        answer = Sum(answer, 1);
        a = Sum(a, ChangeSign(b));
    }

    if (Negative)
        return ChangeSign(answer);
    else
        return answer;

}

int Sum(int num1, int num2) {
    // �����

    int answer = 0, transfer = 0;

    answer = num1 ^ num2;
    // ���� �����-�� ��������������� ���� 1,
    // �� ��������� �� ������ �����
    transfer = (num1 & num2) << 1;

    // ���� ����� ������ ����������
    while (transfer) {
        int temp = answer;
        answer = answer ^ transfer;
        transfer = (temp & transfer) << 1;
    }

    return answer;
}

int ChangeSign(int n) {
    // ��������� ����� X = -X - 1
    // add(~n, 1) = -n - 1 + 1 = -n
    return Sum(~n, 1);
}

int getSign(int n) {
    // �������� �������� ���
    return n >> 31;
}

int module(int n) {
    // ������ n

    if (getSign(n) & 1) // ����� �������������, �������� ��� 1
        return ChangeSign(n); // ������� �������������
    else
        return n; // �������� ����� ��
}

