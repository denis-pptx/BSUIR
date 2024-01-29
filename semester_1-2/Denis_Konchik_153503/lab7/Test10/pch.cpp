//
// pch.cpp
//

#include "pch.h"
#include <cstring>
using namespace std;

int PATRICIAN(int N) {
    string poison = ToTernaryStr(N);

    // Массив номеров бочек в троичной системе счисления
    string* barell = new string[240];

    for (int i = 0; i < 240; i++)
        barell[i] = ToTernaryStr(i + 1);

    // Массив жив ли раб
    int Slave[5] = { 1,1,1,1,1 };

    // ########################## ПЕРВЫЙ ДЕНЬ ##########################

        // i раб пробует бочку с нулем на i позиции
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < 240; b++)
            if (barell[b][s] == '0' && barell[b] == poison)
                Slave[s] = 0;

    }

    // Подсчет выживших рабов
    int alive = 0;
    for (int i = 0; i < 5; i++)
        if (Slave[i])
            alive++;

    // Бочки, которые осталось проверить после первого дня
    string* AfterDayOne = new string[240];
    int AfterD1 = 0;

    if (alive == 5) {
        // Если выжили все, то осталось проверить бочки,
        // в номерах которых нет ни одного нуля

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
        // Иначе, осталось проверять бочки с нулями позиций,
        // равыным умершим рабам

        for (int b = 0; b < 240; b++) {
            // Добавить бочку для дальнейшей проверки или нет
            bool add = true;
            for (int s = 0; s < 5; s++) {
                // Если раб мертв и на позиции его номера нет 0
                if (Slave[s] == 0 && barell[b][s] != '0')
                    add = false;
            }
            if (add)
                AfterDayOne[AfterD1++] = barell[b];
        }
    }


    // ########################## ВТОРОЙ ДЕНЬ ##########################

    int TempSlave[5]; // Копия массива рабов
    for (int i = 0; i < 5; i++)
        TempSlave[i] = Slave[i];

    // i раб пробует бочку с единицей на i позиции
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < AfterD1; b++)
            if (TempSlave[s] && AfterDayOne[b][s] == '1' && AfterDayOne[b] == poison)
                TempSlave[s] = 0;
    }

    // Бочки, которые осталось проверить после второго дня
    string* AfterDayTwo = new string[240];
    int AfterD2 = 0;

    // Осталось проверять бочки с единицам позиций,
    // равыным умершим рабам

    for (int b = 0; b < AfterD1; b++) {
        // Добавить бочку для дальнейшей проверки или нет
        bool add = true;
        for (int s = 0; s < 5; s++) {
            // Если раб умер во второй день и на позиции его номера нет 1
            if (Slave[s] == 1 && TempSlave[s] == 0 && AfterDayOne[b][s] != '1')
                add = false;
        }
        if (add)
            AfterDayTwo[AfterD2++] = AfterDayOne[b];
    }


    // Если раб не умер, то на его позиции поставить 2
    int LIVE = 0; // выжило рабов
    for (int i = 0; i < 5; i++) {
        if (TempSlave[i]) {
            LIVE++;
            for (int b = 0; b < AfterD2; b++)
                AfterDayTwo[b][i] = '2';
        }
    }



    // Отравленная бочка
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
    // Перевод из int в string троичную систему

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
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Reverse(string& str) {
    // Реверс строки

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}