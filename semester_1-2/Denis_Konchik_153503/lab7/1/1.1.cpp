// Лабораторная 7, задача 1. Выполнена: Кончик Д. С.

/*
Необходимо разработать программу для перевода чисел из одной системы счисления в другую. 
Выполнить два варианта решения задачи: без использования массивов и с помощью массивов.

[Вариант 13]
Из четырнадцатеричной в троичную
*/

// С МАССИВАМИ

#include <iostream>
#include <cmath>
#define ull unsigned long long int
using namespace std;

// 14: 0 1 2 3 4 5 6 7 8 9 A B C D
// 3:  0 1 2

int len(char*);
void Reverse(char*);
int CharToInt(char);
void Input(char*, const int&);
void FourteenToTernary(char*, char*);

int main()
{
    const int MAX = 100;
    char fourteen[MAX];
    char three[MAX];
   
    // Ввод данных
    cout << "Enter a number in 14 form: "; 
    Input(fourteen, MAX);

    // Преобразование в троичную систему
    FourteenToTernary(fourteen, three);

    cout << "Number in 3 form: " << three;

    return 0;
}

void FourteenToTernary(char* fourteen, char* three) {

    bool minus = fourteen[0] == '-' ? true : false;
    
    if (minus) {
        Reverse(fourteen);
        fourteen[len(fourteen) - 1] = '\0';
        Reverse(fourteen);
    }
     
// ************ ПЕРЕВОД В 10 ***********************
    ull ten = 0;

    char whole[100]; // Целая часть
    int j = 0;
    while (fourteen[j] && fourteen[j] != '.') {
        whole[j] = fourteen[j++];
    }
    whole[j] = '\0';

    char fractional[100]; // Дробная часть
    int f = 0;
    if (j != len(fourteen)) {
        while (fourteen[++j])
            fractional[f++] = fourteen[j];
    }
    fractional[f] = '\0';
   
    // Целая часть
    ull ten_whole = 0;
    Reverse(whole);
    for (int i = 0; i < len(whole); i++)
        ten_whole += CharToInt(whole[i]) * (ull)pow(14, i);

    // Дробная часть
    double ten_fractional = 0;
    for (int i = 0; i < len(fractional); i++)
        ten_fractional += CharToInt(fractional[i]) * (double)pow(14, -1 - i);

// ************ ПЕРЕВОД В 3 *********************** 

    char three_whole[100]; // Целая часть

    if (ten_whole == 0) {
        three_whole[0] = '0';
        three_whole[1] = '\0';
    }
    else {
        int j = 0;
        while (ten_whole) {
            three_whole[j++] = ten_whole % 3 + '0';
            ten_whole /= 3;
        } three_whole[j] = '\0';
    }
    Reverse(three_whole);

    char three_fractional[100]; // Дробная часть
    double temp_fractional = ten_fractional; // Дробная часть в десятичной
    int i = 0;
    while (i < 11 && temp_fractional) {
        temp_fractional *= 3;
        three_fractional[i++] = (int)temp_fractional + '0';
        temp_fractional = temp_fractional - (int)temp_fractional;
    } three_fractional[i] = '\0';

// ************ СОЕДИНЕНИЕ В 1 СТРОКУ *********************

    int k = 0;
    for (k = 0; k < len(three_whole); k++)
        three[k] = three_whole[k];
    

    // Добавление дробной части
    if (ten_fractional) {
        three[k++] = '.';
        for (int i = 0; i < len(three_fractional); i++)
            three[k++] = three_fractional[i];
    }

    three[k] = '\0';


    if (minus) {
        Reverse(three);
        int l = len(three);
        three[l] = '-';
        three[l + 1] = '\0';
        Reverse(three);
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

int CharToInt(char x) {
    if (48 <= x && x <= 57)
        return x - '0';
    else if (65 <= x && x <= 68)
        return x - 55;
    else if (97 <= x && x <= 100)
        return x - 87;

    cout << "ERROR";
    exit(0);
}

void Input(char* str, const int& size) {
    
    cin >> str;
    
    if (len(str) > size) {
        cout << "INCORRECT INPUT";
        exit(0);
    }
    else {
        for (int i = 0; i < len(str); i++) {
            // Ввели символ не из 14-ой системы
            if (!(48 <= str[i] && str[i] <= 57 || 65 <= str[i] && str[i] <= 68 || 97 <= str[i] && str[i] <= 100 || str[0] == '-' || str[i] == '.')) {
                cout << "INCORRECT INPUT";
                exit(0);
            }
        }
    }
}