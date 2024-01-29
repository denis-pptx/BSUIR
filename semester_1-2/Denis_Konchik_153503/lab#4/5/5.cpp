// Лабораторная 4, задача 5. Выполнена: Кончик Д. С.

/*
Соседями элемента а(ij) в матрице назовем элементы a(kg), где i-1 <= k <= i+l, j-1 <= g <= j+1, (k,g)≠(i,j).
Операция сглаживания матрицы дает новую матрицу того же размера, каждый элемент которой получается
как среднее арифметическое имеющихся соседей соответствующего элемента исходной матрицы.
Построить результат сглаживания заданной вещественной матрицы.
*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
double** input_array(double** array, int* N, int* M);

int main()
{
    setlocale(LC_ALL, "Rus");

    cout << "Задайте матрицу";
    cout << "\nСтроки: ";  int N = input_N();
    cout << "Столбцы: ";  int M = input_N();

    // Динамический массив NxM
    double** array = new double* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new double[M];
    }

    // Ввод матрицы (за исключением крайних строк и столбцов)
    cout << "\nВведите матрицу " << N << "x" << M << ": \n";
    array = input_array(array, &N, &M);

    // Динамический массив NxN (сглаженная матрица)
    double** new_array = new double* [N];
    for (int i = 0; i < N; i++) {
        new_array[i] = new double[M];
    }
   
    // Расчет сглаженной матрицы
    if (N == 1) {
        new_array[0][0] = array[0][0];
    }
    else {
        int k = 0; // Число соседей элемента
        double S = 0; // Сумма соседей элемента
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i >= 1) {
                    S += array[i - 1][j]; k++;
                }
                if (i <= N - 2) {
                    S += array[i + 1][j]; k++;
                }
                if (j >= 1) {
                    S += array[i][j - 1]; k++;
                }
                if (j <= M - 2) {
                    S += array[i][j + 1]; k++;
                }
                if (i >= 1 && j >= 1) {
                    S += array[i - 1][j - 1]; k++;
                }
                if (i <= N - 2 && j >= 1) {
                    S += array[i + 1][j - 1]; k++;
                }
                if (i >= 1 && j <= M - 2) {
                    S += array[i - 1][j + 1]; k++;
                }
                if (i <= N - 2 && j <= M - 2) {
                    S += array[i + 1][j + 1]; k++;
                }

                new_array[i][j] = S / k;

                S = 0;
                k = 0;
            }
        }
    }

    cout << "\nСглаженная матрица: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << new_array[i][j] << "\t";
        }
        cout << "\n";
    }


    // Удаление динамических массивов
    for (int i = 0; i < N; i++) {
        delete[] array[i];
    } delete[] array;

    for (int i = 0; i < N; i++) {
        delete[] new_array[i];
    } delete[] new_array;

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

double** input_array(double** array, int* N, int* M) {
    // Проверка на корректность ввода

    double x; // Вводимый элемент
    bool repeat; // Повторить ввод

    do {
        repeat = false;
        for (int i = 0; i < *N && !repeat; i++) {
            for (int j = 0; j < *M && !repeat; j++) {

                // Извлечение символа из буфера
                cin >> x;

                if (!cin.fail() &&                               // Последнее извлечение удачно
                    (cin.peek() == ' ' || cin.peek() == '\n')) { // Последний неизвлеченный символ пробел или Enter

                    // Пропуск пробелов после элемента
                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    // Если размер строки больше / меньше, чем запрашивается
                    if (cin.peek() == '\n' && j != *M - 1 ||
                        j == *M - 1 && cin.peek() != '\n')
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