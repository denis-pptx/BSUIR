//
// pch.cpp
//

#include "pch.h"


void Reverse(char* str) {
    // ������ ������

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}

int LetterToInt(char x) {
    if (48 <= x && x <= 57)
        return x - '0';
    else if (65 <= x && x <= 73)
        return x - 55;
    else if (97 <= x && x <= 105)
        return x - 87;
}

int IntToLetter(int x) {
    if (0 <= x && x <= 9)
        return x + '0';
    else if (10 <= x && x <= 18)
        return x + 55;
    else {
        exit(0);
    }
}

int len(char* str) {
    // ����� ������

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Same_Amount(char* num1, char* num2) {
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

        for (int i = len(change); i < MaxLen; i++) {
            change[i] = '0';
        }
        change[MaxLen] = '\0';
        Reverse(change);
    }
}


void Additional_Zero(char* num, int z = 0) {
    Reverse(num);

    int NewLen = len(num) + z;

    for (int j = len(num); j < NewLen; j++)
        num[j] = '0';

    num[NewLen] = '\0';

    Reverse(num);
}


void DelZero(char* num) {
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
    else if (num[0] == '-') {

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





void SameView(char* num1, char* num2) {
    // ���������� ���������� �����
    Same_Amount(num1, num2);

    // �������������� ������
    Additional_Zero(num1, 5);
    Additional_Zero(num2, 5);
}

void DelSign(char* num, char sign = '-') {
    Reverse(num);
    int l = len(num);
    if (num[l - 1] == sign)
        num[l - 1] = '\0';
    Reverse(num);
}

void AddMinus(char* num) {
    int l = len(num);
    if (!(l == 1 && num[0] == '0')) {

        Reverse(num);
        num[l] = '-';
        num[l + 1] = '\0';
        Reverse(num);

    }
}

void FuncSum(char* sum, char* num1, char* num2) {
    // ��������������
    Reverse(num1); Reverse(num2);

    // ����������
    int P = 0; // ������� �������
    int i = 0;
    for (i = 0; i < len(num1); i++) {
        // ����� ���� �����
        int CellSum = LetterToInt(num1[i]) + LetterToInt(num2[i]) + P;

        if (CellSum < 19) {
            sum[i] = IntToLetter(CellSum);
            P = 0;
        }
        else {
            sum[i] = IntToLetter(CellSum - 19);
            P = 1;
        }
    }
    sum[i] = '\0';
    Reverse(sum);
}

void FuncDifference(char* sum, char* num1, char* num2, bool& n1_bigger_n2) {
    // num1 > num2

    // ��������������
    Reverse(num1); Reverse(num2);

    // ��������
    int P = 0; // ����� �������
    int i = 0;
    for (i = 0; i < len(num1); i++) {
        // �������� ���� �����
        int CellDiff = LetterToInt(num1[i]) - LetterToInt(num2[i]);

        if (i == len(num1) - 1 && CellDiff < 0)
            n1_bigger_n2 = false;

        if (CellDiff >= 0) {
            sum[i] = IntToLetter(CellDiff);
        }
        else {
            sum[i] = IntToLetter(19 + LetterToInt(num1[i]) - LetterToInt(num2[i]));


            // �������� ������� �� ������, �� ������� ����� �������
            int j = i + 1;

            if (num1[j] != '\0') {
                while (num1[j] == '0')
                    num1[j++] = 'I';

                if (num1[j] == '\0')
                    n1_bigger_n2 = false;
                else
                    num1[j] = IntToLetter(LetterToInt(num1[j]) - 1); // �������� ������� � ��������� ������
            }
            else {
                n1_bigger_n2 = false;
            }

        }
    }
    sum[i] = '\0';
    Reverse(sum);
}

void copy(char* temp, char* str) {
    int i = 0;
    for (i = 0; i < len(str); i++)
        temp[i] = str[i];
    temp[i] = '\0';
}

void OperationFunc(char* sum, char* num1, char* num2) {
    if ((num1[0] == '-' || num2[0] == '-') && !(num1[0] == '-' && num2[0] == '-')) {
        // ������ ���� �� ����� �������� �����

        // ����� num1 > num2

        bool n1_bigger_n2 = true;

        // ��������� �������� �����
        char temp1[100]; copy(temp1, num1);
        char temp2[100]; copy(temp2, num2);

        DelSign(num1); DelSign(num2);// ������� ������ � �����
        Same_Amount(num1, num2); // ���������� ���������� �����
        FuncDifference(sum, num1, num2, n1_bigger_n2); // �������� �� �������� �������

        if (temp1[0] == '-') {
            DelZero(sum);
            AddMinus(sum);
        }

        // �����
        if (n1_bigger_n2 == false) {

            // ���������� �������� �����
            copy(num1, temp1); copy(num2, temp2);

            DelSign(num1); DelSign(num2); // ������� ������ � �����
            Same_Amount(num1, num2); // ���������� ���������� �����

            FuncDifference(sum, num2, num1, n1_bigger_n2); // �������� �� �������� �������

            if (temp2[0] == '-') {
                DelZero(sum);
                AddMinus(sum);
            }
        }
    }
    else if (!(num1[0] == '-' && num2[0] == '-')) {
        // ������� ���

        SameView(num1, num2); // � ����������� ����
        FuncSum(sum, num1, num2); // ����������
    }
    else if (num1[0] == '-' && num2[0] == '-') {

        // ����� � �����

        DelSign(num1); DelSign(num2); // ������� ������
        SameView(num1, num2); // � ����������� ����
        FuncSum(sum, num1, num2); // ����������
        AddMinus(sum); // ���������� �����
    }
}


char* SUM(char* number1, char* number2, const int MAX) {
    char* sum = new char[MAX];


    char* temp1 = new char[MAX]; copy(temp1, number1);
    char* temp2 = new char[MAX]; copy(temp2, number2);

    // ������� ����� � �����
    DelSign(temp1, '+'); DelSign(temp2, '+');


    // ����������
    OperationFunc(sum, temp1, temp2);
    DelZero(sum); // �������� ������ ����� � ������

    return sum;
}

char* DIFF(char* number1, char* number2, const int MAX) {
    char* difference = new char[MAX];

    char* temp1 = new char[MAX]; copy(temp1, number1);
    char* temp2 = new char[MAX]; copy(temp2, number2);

    // ������� ����� � �����
    DelSign(temp1, '+'); DelSign(temp2, '+');


    // �������� - � ������� ����� �������� ����
    if (number2[0] != '-')
        AddMinus(temp2);
    else
        DelSign(temp2, '-');

    // ���������� ������ ����� �� ������ (���� �������)
    OperationFunc(difference, temp1, temp2);
    DelZero(difference); // �������� ������ ����� � ������

    return difference;
}