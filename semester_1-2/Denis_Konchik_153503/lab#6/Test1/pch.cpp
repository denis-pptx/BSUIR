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
    
    // Убираем пробелы в конце строки
    int len = strlen(str);
    while (str[len - 1] == ' ')
        str[--len] = '\0';

    // Длина первого слова
    int i = 0;
    while (str[i] != ' ' && str[i] != '\0')
        i++;

    MinNum = 1; // Номер слова минимальной длины
    MinLen = i; // Длина слова минимальной длины
    int backup = 0, Number = 1, length = 0;


    backup = ++i; // На каком символе остановились
    while (i <= strlen(str)) {

        // Двигаемся до пробела
        while (str[i] != ' ' && str[i] != '\0')
            i++;


        Number++; // Номер текущего слова
        length = i - backup; // Длина текущего слова

        if (length < MinLen) {
            MinLen = length;
            MinNum = Number;
        }

        backup = ++i;
    }
}