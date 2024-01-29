//
// pch.cpp
//

#include "pch.h"
#include <cstring>
using namespace std;

int PATRICIAN(int N) {
    string poison = ToTernaryStr(N);

    // ������ ������� ����� � �������� ������� ���������
    string* barell = new string[240];

    for (int i = 0; i < 240; i++)
        barell[i] = ToTernaryStr(i + 1);

    // ������ ��� �� ���
    int Slave[5] = { 1,1,1,1,1 };

    // ########################## ������ ���� ##########################

        // i ��� ������� ����� � ����� �� i �������
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < 240; b++)
            if (barell[b][s] == '0' && barell[b] == poison)
                Slave[s] = 0;

    }

    // ������� �������� �����
    int alive = 0;
    for (int i = 0; i < 5; i++)
        if (Slave[i])
            alive++;

    // �����, ������� �������� ��������� ����� ������� ���
    string* AfterDayOne = new string[240];
    int AfterD1 = 0;

    if (alive == 5) {
        // ���� ������ ���, �� �������� ��������� �����,
        // � ������� ������� ��� �� ������ ����

        for (int b = 0; b < 240; b++) {
            bool add = true;

            for (int i = 0; i < 5; i++)
                if (barell[b][i] == '0')
                    add = false;

            if (add)
                AfterDayOne[AfterD1++] = barell[b];
        }
    }
    else {
        // �����, �������� ��������� ����� � ������ �������,
        // ������� ������� �����

        for (int b = 0; b < 240; b++) {
            // �������� ����� ��� ���������� �������� ��� ���
            bool add = true;
            for (int s = 0; s < 5; s++) {
                // ���� ��� ����� � �� ������� ��� ������ ��� 0
                if (Slave[s] == 0 && barell[b][s] != '0')
                    add = false;
            }
            if (add)
                AfterDayOne[AfterD1++] = barell[b];
        }
    }


    // ########################## ������ ���� ##########################

    int TempSlave[5]; // ����� ������� �����
    for (int i = 0; i < 5; i++)
        TempSlave[i] = Slave[i];

    // i ��� ������� ����� � �������� �� i �������
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < AfterD1; b++)
            if (TempSlave[s] && AfterDayOne[b][s] == '1' && AfterDayOne[b] == poison)
                TempSlave[s] = 0;
    }

    // �����, ������� �������� ��������� ����� ������� ���
    string* AfterDayTwo = new string[240];
    int AfterD2 = 0;

    // �������� ��������� ����� � �������� �������,
    // ������� ������� �����

    for (int b = 0; b < AfterD1; b++) {
        // �������� ����� ��� ���������� �������� ��� ���
        bool add = true;
        for (int s = 0; s < 5; s++) {
            // ���� ��� ���� �� ������ ���� � �� ������� ��� ������ ��� 1
            if (Slave[s] == 1 && TempSlave[s] == 0 && AfterDayOne[b][s] != '1')
                add = false;
        }
        if (add)
            AfterDayTwo[AfterD2++] = AfterDayOne[b];
    }


    // ���� ��� �� ����, �� �� ��� ������� ��������� 2
    int LIVE = 0; // ������ �����
    for (int i = 0; i < 5; i++) {
        if (TempSlave[i]) {
            LIVE++;
            for (int b = 0; b < AfterD2; b++)
                AfterDayTwo[b][i] = '2';
        }
    }



    // ����������� �����
    int AnsPoison = TernaryStrToInt(AfterDayTwo[0]);

    return AnsPoison;
}


int TernaryStrToInt(string num) {

    Reverse(num);
    int digit = 0;

    for (int i = 0; i < len(num); i++)
        digit += (num[i] - '0') * (int)pow(3, i);

    return digit;
}

string ToTernaryStr(int n) {
    // ������� �� int � string �������� �������

    string ternary = "";
    while (n) {
        ternary = (char)((n % 3) + 48) + ternary;
        n /= 3;
    }

    while (len(ternary) != 5)
        ternary = '0' + ternary;

    return ternary;
}

int len(string str) {
    // ����� ������

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Reverse(string& str) {
    // ������ ������

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}