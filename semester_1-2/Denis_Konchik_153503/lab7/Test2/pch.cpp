//
// pch.cpp
//

#include "pch.h"



void AddToStraight(char* add, char* straight) {

    char back[100]; // ��������
    if (add[0] == '1') {
        Reverse(add);

        // ���������� �������� ����� � -1 � ���. ����,
        // �������� �������� ���
        // -1 � ��� ���� - ��� 1

        char more = '0'; // ����������� ����� ������
        int i = 0;
        for (i; i < len(add) - 1; i++) {
            if (add[i] - '0' + more - '0' == 2) {
                back[i] = '1';
                more = '1';
            }
            else if (add[i] - '0' + more - '0' == 1) {
                back[i] = '0';
                more = '1';
            }
            else if (add[i] - '0' + more - '0' == 0) {
                back[i] = '1';
                more = '0';
            }
            else {
                back[i] = '0';
                more = '0';
            }
        }

        back[i] = add[i];
        back[i + 1] = '\0';


        // ������ ���

        i = 0;
        for (i; i < len(back) - 1; i++) {
            if (back[i] == '0')
                straight[i] = '1';
            else
                straight[i] = '0';
        }
        straight[i] = back[i];
        straight[i + 1] = '\0';

        Reverse(straight);
    }
    else {
        int i = 0;
        for (i = 0; i < len(add); i++)
            straight[i] = add[i];
        straight[i] = '\0';
    }

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

