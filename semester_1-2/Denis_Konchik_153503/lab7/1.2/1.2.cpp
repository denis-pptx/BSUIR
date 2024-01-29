// Лабораторная 6, задача 1. Выполнена: Кончик Д. С.

/*
Необходимо разработать программу для перевода чисел из одной системы счисления в другую.
Выполнить два варианта решения задачи: без использования массивов и с помощью массивов.

[Вариант 13]
Из четырнадцатеричной в троичную
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#define ll long long int
using namespace std;

// 14: 0 1 2 3 4 5 6 7 8 9 A B C D
// 3:  0 1 2

int len(char*);
int CharToInt(char);
int Input_convert_10(ll& ten, int& BitNum, bool& minus, bool& point);


int main()
{
    cout << "Enter a number in 14 form \none character at a time. \nTo stop input press Enter twice \n";

    ll ten = 0, three = 0;
    int BitNum = 0;

    // Рекурсивный ввод и перевод в десятичную
    bool minus = false, point = false;
    Input_convert_10(ten, BitNum, minus, point);
 
    // Перевод в 3

    // целая часть
    int p = 0;
    while (ten) {

        if (p > 18) {
            cout << "OVERFLOW";
            exit(0);
        }

        three += (ten % 3) * (ll)pow(10, p++);
        ten /= 3;
    }  

    // дробная часть в 10
    double fractional = 0; 
    if (point) {
        // Если была точка
        char x = 0;
        BitNum = 0;
        cin.ignore(1, '\n');
        cin.get(x);
        while (x != 10) {
            fractional += CharToInt(x) * pow(14, --BitNum);
            cin.ignore(1, '\n');
            cin.get(x);
        } 
    }
    
    // дробная в 3
    double three_fractional = 0;
    if (fractional) {
        int i = 0, BitNum = 0;
        while (i < 11 && fractional) {
            fractional *= 3;
            three_fractional += (int)fractional * pow(10, --BitNum);
            fractional = fractional - (int)fractional;
            i++;
        }
    }

    // Ответ
    double ans = (double)three + three_fractional;

    ans = minus ? -ans : ans;
    cout << "Number in 3 form: " << setprecision(10) << ans;

    return 0;
}

int Input_convert_10(ll& ten, int& BitNum, bool& minus, bool& point) {

    char x;
    cin.get(x);

    if (x == '.') point = true;

    // Конец ввода
    if (x == '\n' || x == '.')
        return 0;

    // Ввели символ не из 14 системы
    if (!(48 <= x && x <= 57 || 65 <= x && x <= 68 || 97 <= x && x <= 100 || x == '-' || x == '.') || cin.peek() != '\n') {
        cout << "INCORRECT INPUT";
        exit(0);
    }

    // Скип энтера после извлечения
    cin.ignore(1, '\n');

    Input_convert_10(ten, BitNum, minus, point);

    if (x == '-') minus = true;

    if (x != '-' && x != '.')
        ten += CharToInt(x) * (ll)pow(14, BitNum++);
   

    return 0;
}


int len(char* str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}


int CharToInt(char x) {
    if (48 <= x && x <= 57)
        return x - '0';
    else if (65 <= x && x <= 68)
        return x - 55;
    else if (97 <= x && x <= 100)
        return x - 87;

    cout << "INCORRECT INPUT";
    exit(0);
}
