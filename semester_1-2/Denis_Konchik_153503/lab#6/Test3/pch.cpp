//
// pch.cpp
//

#include "pch.h"

int length(char* str) {
    // ����� ������

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void cut(char* str, int pos) {


    // � temp ���������� ��� ������� str ��� #
    char* temp = new char[length(str)];
    int t = 0;

    for (int i = 0; i < pos - 1; i++)
        temp[t++] = str[i];

    for (int i = pos + 1; i < length(str); i++)
        temp[t++] = str[i];

    temp[t] = '\0';

  
    // �������� temp � str
    for (int i = 0; i < length(temp); i++)
        str[i] = temp[i];

    str[length(temp)] = '\0';

    delete[] temp;
}

char* FindGrid(char* str) {

    // ��������� ���� #
    // ������� - ���������� � cut

    bool repeat = true;
    while (repeat) {

        repeat = false;
        int i = 0;

        while (i < length(str)) {

            if (str[i] == '#') {
                cut(str, i);
                break;
            }

            i++;
        }

        for (int j = 0; j < length(str) && !repeat; j++) {
            if (str[j] == '#')
                repeat = true;
        }
    }
    return str;
}