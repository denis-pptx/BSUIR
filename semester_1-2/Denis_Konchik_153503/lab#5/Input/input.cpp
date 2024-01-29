#include <iostream>
#include "input.h"
using namespace std;

/*
    Значения:
    input_natural
    input_int
    input_int_pairs
    input_double

    Двумерные массивы:
    input_arr2_natural
    input_arr2_int
    input_arr2_double

    Одномерные массивы:
    input_arr1_natural
    input_arr1_int
    input_arr1_double

*/

void RepeatInputArray(bool& repeat) {
    cin.clear(); // Возвращение в обычный режим работы
    cin.ignore(10000, '\n'); // Игнор символов до Enter
    repeat = true;
    cout << "\nПовторите ввод массива: \n";
}

int input_natural() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n' || x <= 0) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}

int input_natural_z() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n' || x < 0) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}


int input_int() {
    int x;

    while (true) {
        cin >> x;

        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); 
            cin.ignore(10000, '\n'); 
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}

int input_int_pairs() {
    int x;

    while (true) {
        cin >> x;

        if (!cin.fail() && (cin.peek() == '\n' || cin.peek() == ' ')) {
            return x;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Повторите ввод: ";
        }

    }
}

unsigned long long input_int_pairs_ll() {
    unsigned long long x;

    while (true) {
        cin >> x;

        if (!cin.fail() && (cin.peek() == '\n' || cin.peek() == ' ')) {
            return x;
        }
        else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Повторите ввод: ";
        }

    }
}

double input_double() {
    double x;

    while (true) {
        cin >> x;

        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}

int** input_arr2_natural(int** array, int& N, int& M) {

    int x;
    bool repeat;

    do {
        repeat = false;
        for (int i = 0; i < N && !repeat; i++) {
            for (int j = 0; j < M && !repeat; j++) {

                cin >> x;

                if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n') && x > 0) {

                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    if (cin.peek() == '\n' && j != M - 1 || j == M - 1 && cin.peek() != '\n')
                        RepeatInputArray(repeat);

                    array[i][j] = x;
                }
                else {
                    RepeatInputArray(repeat);
                }
            }
        }

        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    return array;
}

int** input_arr2_int(int** array, int& N, int& M) {

    int x;
    bool repeat;

    do {
        repeat = false;
        for (int i = 0; i < N && !repeat; i++) {
            for (int j = 0; j < M && !repeat; j++) {

                cin >> x;

                if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n')) {

                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    if (cin.peek() == '\n' && j != M - 1 || j == M - 1 && cin.peek() != '\n')
                        RepeatInputArray(repeat);

                    array[i][j] = x;
                }
                else {
                    RepeatInputArray(repeat);
                }
            }
        }

        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    return array;
}
double** input_arr2_double(double** array, int& N, int& M) {
    // Ввод двумерного массива
    double x; // Вводимый элемент
    bool repeat; // Повторить ввод

    do {
        repeat = false;
        for (int i = 0; i < N && !repeat; i++) {
            for (int j = 0; j < M && !repeat; j++) {

                // Извлечение символа из буфера
                cin >> x;

                // Последнее извлечение удачно, последний неизвлеченный символ пробел или Enter
                if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n')) { 

                    // Пропуск пробелов после элемента
                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    // Если размер строки больше / меньше, чем запрашивается
                    if (cin.peek() == '\n' && j != M - 1 || j == M - 1 && cin.peek() != '\n')
                        RepeatInputArray(repeat);

                    // Положить элемент в массив
                    array[i][j] = x;
                }
                else {
                    RepeatInputArray(repeat);
                }
            }
        }

        // Если элементов больше, чем запрашивается
        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    // Взвращение массива
    return array;
}


int* input_arr1_natural(int* array, int& N) {

    int x;
    bool repeat;

    do {
        repeat = false;

        for (int i = 0; i < N && !repeat; i++) {

            cin >> x;

            if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n') && x > 0) {

                while (cin.peek() == ' ')
                    cin.ignore(1, ' ');

                if (cin.peek() == '\n' && i != N - 1)
                    RepeatInputArray(repeat);

                array[i] = x;
            }
            else {
                RepeatInputArray(repeat);
            }
        }

        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    return array;
}

int* input_arr1_int(int* array, int& N) {

    int x;
    bool repeat;

    do {
        repeat = false;

        for (int i = 0; i < N && !repeat; i++) {

            cin >> x;

            if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n')) {

                while (cin.peek() == ' ')
                    cin.ignore(1, ' ');

                if (cin.peek() == '\n' && i != N - 1)
                    RepeatInputArray(repeat);

                array[i] = x;
            }
            else {
                RepeatInputArray(repeat);
            }
        }

        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    return array;
}

double* input_arr1_double(double* array, int& N) {
    // Ввод одномерного массива
    double x;
    bool repeat;
    // Ввод массива + проверка на корректность ввода
    do {
        repeat = false;

        for (int i = 0; i < N && !repeat; i++) {

            // Извлечение числа из буфера
            cin >> x;

            // Если (последнее извлечение удачно) 
            // И (последний неизвлеченный символ пробел или перенос на новую строку)
            if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n')) {

                // Пропуск пробелов после элемента
                while (cin.peek() == ' ')
                    cin.ignore(1, ' ');

                // Если размер строки больше / меньше, чем запрашивается
                if (cin.peek() == '\n' && i != N - 1)
                    RepeatInputArray(repeat);

                array[i] = x;
            }
            else {
                RepeatInputArray(repeat);
            }
        }

        // Если элементов больше, чем запрашивается
        if (!repeat && cin.peek() != '\n')
            RepeatInputArray(repeat);

    } while (repeat);

    // Возвращение массива
    return array;
}