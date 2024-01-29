//
// pch.cpp
//

#include "pch.h"



void Operation(char** number, char* sum) {
    // ������� �� ������������� ���� � ������
    for (int i = 0; i < 2; i++)
        Natural_to_Straight(number[i]);

    // ������ ����� ����� � ������ ����������
    Same_Amount_of_Bits(number[0], number[1]);

    // ��������� �������������� ����� ����� ��������� ����
    for (int i = 0; i < 2; i++)
        Additional_Zero(number[i], 5);


    // ������� �� ������� ���� � ��������
    for (int i = 0; i < 2; i++)
        Straight_to_Back(number[i]);


    // ������� �� ��������� ���� � �������������� (+1)
    for (int i = 0; i < 2; i++)
        Back_to_Add(number[i]);


    // ����� ����� � �������������� ����

    Sum_in_Add(sum, number[0], number[1]);

    // ����� � �������� ����
    Add_to_Back(sum);

    // ����� � ������ ����
    Straight_to_Back(sum);

    // ������� ����� � ������������ �����
    Straight_to_Natural(sum);

}

int len(char* str) {
    // ����� ������

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Reverse(char* str) {
    // ������ ������

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}



void Same_Amount_of_Bits(char* num1, char* num2) {
    int NumRes = -1; // ����� �����, ������� ����� ��������
    int MaxLen = 0;     // ������, �� �������� ����� ��������

    char* change = 0;

    if (len(num1) > len(num2)) {
        change = num2;
        MaxLen = len(num1);
    }
    else if (len(num1) < len(num2)) {
        change = num1;
        MaxLen = len(num2);
    }


    if (MaxLen) {
        Reverse(change);

        // ������������ �������� ���
        int OldLen = len(change);
        change[MaxLen - 1] = change[OldLen - 1];
        change[MaxLen] = '\0';

        for (int i = OldLen - 1; i < MaxLen - 1; i++) {
            change[i] = '0';
        }

        Reverse(change);
    }
}

void Natural_to_Straight(char* num) {
    if (num[0] == '-') {
        // ����� �������������
        num[0] = '1';
    }
    else {
        // ����� �������������
        // ������ ����� ������ �� 1
        int j = 0;
        num[len(num) + 1] = '\0';
        for (j = len(num); j > 0; j--)
            num[j] = num[j - 1];

        // C������ ��� 0
        num[0] = '0';
    }
}

void Straight_to_Back(char* num) {
    if (num[0] != '0') {
        for (int j = 1; j < len(num); j++) {
            if (num[j] == '1')
                num[j] = '0';
            else
                num[j] = '1';
        }
    }
}

void Back_to_Add(char* num) {
    if (num[0] != '0') {
        Reverse(num);

        char more = '1'; // ������� ����� ������
        for (int j = 0; j < len(num) - 1; j++) {
            if (num[j] - '0' + more - '0' == 0) {
                num[j] = '0';
                more = '0';
            }
            else if (num[j] - '0' + more - '0' == 1) {
                num[j] = '1';
                more = '0';
            }
            else if (num[j] - '0' + more - '0' == 2) {
                num[j] = '0';
                more = '1';
            }
        }

        Reverse(num);
    }
}

void Additional_Zero(char* num, int z) {
    Reverse(num);
    int OldLen = len(num);
    int NewLen = OldLen + z;
    num[NewLen - 1] = num[OldLen - 1];
    num[NewLen] = '\0';

    for (int j = OldLen - 1; j < NewLen - 1; j++) {
        num[j] = '0';
    }
    Reverse(num);
}

void Sum_in_Add(char* sum, char* num1, char* num2) {
    Reverse(num1); Reverse(num2);

    char more = '0'; // ������� ����� ������
    for (int i = 0; i < len(num1); i++) {


        if (num1[i] - '0' + num2[i] - '0' + more - '0' == 0) {
            sum[i] = '0';
            more = '0';
        }
        else if (num1[i] - '0' + num2[i] - '0' + more - '0' == 1) {
            sum[i] = '1';
            more = '0';
        }
        else if (num1[i] - '0' + num2[i] - '0' + more - '0' == 2) {
            sum[i] = '0';
            more = '1';
        }
        else if (num1[i] - '0' + num2[i] - '0' + more - '0' == 3) {
            sum[i] = '1';
            more = '1';
        }
    }
    sum[len(num1)] = '\0';
    Reverse(sum);

    Reverse(num1); Reverse(num2);
}

void Add_to_Back(char* num) {
    if (num[0] != '0') {
        // ������� �������������� ����� � ������ ���

        // ���������� ����� � -1 � ���. ����,
        // �������� �������� ��� �����
        // -1 � ��� ���� - ��� 1

        Reverse(num);
        char more = '0'; // ����������� ����� ������

        int i = 0;
        for (i; i < len(num) - 1; i++) {
            if (num[i] - '0' + more - '0' == 2) {
                num[i] = '1';
                more = '1';
            }
            else if (num[i] - '0' + more - '0' == 1) {
                num[i] = '0';
                more = '1';
            }
            else if (num[i] - '0' + more - '0' == 0) {
                num[i] = '1';
                more = '0';
            }
            else {
                num[i] = '0';
                more = '0';
            }
        }

        Reverse(num);
    }
}

void Straight_to_Natural(char* num) {
    if (num[0] == '0') {
        int Zero = 0; // ����� ����� � �����
        while (num[Zero] && num[Zero] == '0')
            Zero++;

        Reverse(num);
        num[len(num) - Zero] = '\0';
        Reverse(num);

        if (len(num) == 0) {
            num[0] = '0';
            num[1] = '\0';
        }

    }
    else {

        int Zero = 1; // ����� ����� � �����
        while (num[Zero] && num[Zero] == '0')
            Zero++;

        int OldLen = len(num);

        Reverse(num);

        num[OldLen - Zero + 1] = '\0';
        num[OldLen - Zero] = '-';

        Reverse(num);
    }
}