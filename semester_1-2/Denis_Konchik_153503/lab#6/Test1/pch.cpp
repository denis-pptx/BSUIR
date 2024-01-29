//
// pch.cpp
//

#include "pch.h"
void min(char* str, int& MinNum, int& MinLen) {
    
    if (strlen(str) == 0) {
        MinNum = 0;
        MinLen = 0;
        return;
    }
    
    // ������� ������� � ����� ������
    int len = strlen(str);
    while (str[len - 1] == ' ')
        str[--len] = '\0';

    // ����� ������� �����
    int i = 0;
    while (str[i] != ' ' && str[i] != '\0')
        i++;

    MinNum = 1; // ����� ����� ����������� �����
    MinLen = i; // ����� ����� ����������� �����
    int backup = 0, Number = 1, length = 0;


    backup = ++i; // �� ����� ������� ������������
    while (i <= strlen(str)) {

        // ��������� �� �������
        while (str[i] != ' ' && str[i] != '\0')
            i++;


        Number++; // ����� �������� �����
        length = i - backup; // ����� �������� �����

        if (length < MinLen) {
            MinLen = length;
            MinNum = Number;
        }

        backup = ++i;
    }
}