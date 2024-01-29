// Лабораторная 4, задача 9. Выполнена: Кончик Д. С.

/*
В качестве входных данных поступают две целочисленные матрицы A и B, которые имеют размер N и соответственно.
Требуется найти произведение матриц A*B. Выделение памяти через функции языка С.
*/

#include <iostream>
#include <malloc.h>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
int** input_array(int** array, int* N);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите целочисленные матрицы";
    cout << "\nПорядок матриц: ";
    int N = input_N();

    // Создание динамических массивов (A, B)
    int** A = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = (int*)malloc(N * sizeof(int));
    }
    int** B = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        B[i] = (int*)malloc(N * sizeof(int));
    }

    // Ввод матриц (A, B)
    cout << "\nВведите матрицу A: \n";
    A = input_array(A, &N);

    cout << "\nВведите матрицу B: \n";
    B = input_array(B, &N);

    // Создание динамического массива C (произведение матриц)
    int** C = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        C[i] = (int*)malloc(N * sizeof(int));
    }

    // Расчет произведение матриц (матрица C)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    cout << "\nПроизведение матриц: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << C[i][j] << "\t";
        }
        cout << "\n";
    }

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(A[i]);
    } free(A);

    for (int i = 0; i < N; i++) {
        free(B[i]);
    } free(B);

    for (int i = 0; i < N; i++) {
        free(C[i]);
    } free(C);

    return 0;
}

int input_N() {
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


void repeat_input(bool* repeat) {
    cin.clear(); // Возвращение в обычный режим работы
    cin.ignore(10000, '\n'); // Игнор символов до Enter
    *repeat = true;
    cout << "\nПовторите ввод матрицы: \n";
}

int** input_array(int** array, int* N) {
    // Проверка на корректность ввода

    double x; // Вводимый элемент
    bool repeat; // Повторить ввод

    do {
        repeat = false;
        for (int i = 0; i < *N && !repeat; i++) {
            for (int j = 0; j < *N && !repeat; j++) {

                // Извлечение символа из буфера
                cin >> x;

                if (!cin.fail() &&                               // Последнее извлечение удачно
                    (cin.peek() == ' ' || cin.peek() == '\n')) { // Последний неизвлеченный символ пробел или Enter

                    // Пропуск пробелов после элемента
                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    // Если размер строки больше / меньше, чем запрашивается
                    if (cin.peek() == '\n' && j != *N - 1 ||
                        j == *N - 1 && cin.peek() != '\n')
                        repeat_input(&repeat);

                    // Положить элемент в массив
                    array[i][j] = x;
                }
                else {
                    repeat_input(&repeat);
                }
            }
        }

        // Если элементов больше, чем запрашивается
        if (!repeat && cin.peek() != '\n')
            repeat_input(&repeat);

    } while (repeat);

    // Взвращение массива
    return array;
}