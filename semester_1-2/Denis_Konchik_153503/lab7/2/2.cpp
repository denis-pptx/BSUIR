// Лабораторная 7, задача 2. Выполнена: Кончик Д. С.

/*
Перевести числа. Предусмотреть ввод положительных и отрицательных чисел.

[Вариант 13]
Из дополнительного кода в прямой код.
*/

#include <iostream>
#include <cmath>
using namespace std;

int len(char*);
void Reverse(char*);
void Input(char*, const int&);
void AddToStraight(char*, char*);
void DeletePoint(char* str, int pos);
void InsertPoint(char* str, int pos);

int main()
{
    const int MAX = 100;
    char straight[MAX]; // Прямой
    char add[MAX]; // Дополнительный
    
    // Ввод данных
    cout << "Enter additional code: ";
    Input(add, MAX);

    // Есть ли точка
    int PointPos = 0;
    for (int i = 0; i < len(add); i++) {
        if (add[i] == '.') {
            PointPos = i;
            break;
        }
    }

    if (PointPos) DeletePoint(add, PointPos);

    // Из дополнительного в прямой
    AddToStraight(add, straight);

    if (PointPos) InsertPoint(straight, PointPos);
    
    // Вывод
    cout << "Straight code: " << straight;

    return 0;
}

void DeletePoint(char* str, int pos) {
    int i = 0;
    for (i = pos; i < len(str) - 1; i++)
        str[i] = str[i + 1];
    str[i] = '\0';
}

void InsertPoint(char* str, int pos) {
    int l = len(str), i = 0;
    for (i = l; i > pos; i--)
        str[i] = str[i - 1];
    str[pos] = '.';
    str[l + 1] = '\0';
}

void AddToStraight(char* add, char* straight) {

    char back[100]; // Обратный

    if (add[0] == '1') {
        Reverse(add);

        // Складываем исходное число с -1 в доп. коде,
        // получаем обратный код
        // -1 в доп коде - все 1

        char more = '0'; // Переносится через разряд
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


        // Прямой код

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
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Reverse(char* str) {
    // Реверс строки

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}

void Input(char* str, const int& size) {

    cin >> str;

    if (len(str) > size) {
        cout << "INCORRECT INPUT";
        exit(0);
    }

    for (int i = 0; i < len(str); i++) {
        if (!(str[i] == '0' || str[i] == '1' || str[i] == '.')) {
            cout << "INCORRECT INPUT";
            exit(0);
        }
    }
}