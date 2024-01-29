//
// pch.cpp
//

#include "pch.h"
void LowRegister(char* word) {

    for (int i = 0; i < strlen(word); i++) {
        tolower(word[i]);
    }
}

bool IsSameWords(char** word, int& amount) {

    // Проверка на повторяющиеся слова
    if (amount == 1)
        return false;

    int index = amount - 1; // Максимальный индекс
    for (int i = 0; i < index; i++) {
        for (int j = index; j > i; j--) {

           // LowRegister(word[j]);
           // LowRegister(word[i]);

            // Сравниваем
            if (!strcmp(word[j], word[i]))
                return true;
        }
    }

    return false;
}