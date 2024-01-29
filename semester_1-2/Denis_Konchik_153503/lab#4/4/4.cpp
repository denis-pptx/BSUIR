// Лабораторная 4, задача 4. Выполнена: Кончик Д. С.

/*
Элемент матрицы называется локальным минимумом, если он строго меньше всех имеющихся у него соседей.
Соседями элемента a(ij) в матрице назовем элементы a(kg), где i-1 <= k <= i+l, j-1 <= g <= j+1, (k,g)≠(i,j).
Подсчитать количество локальных минимумов заданной матрицы
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

    /* Создадим матрицу (N+2)x(M+2) порядка,
    крайние строки и столбцы проинициализируем
    максимально возможными значениями */

    // Динамический массив (N+2)x(M+2)
    double** array = new double* [N + 2];
    for (int i = 0; i < N + 2; i++) {
        array[i] = new double[M + 2];
    }

    // Инициализация крайних строк и столбцов максимальным значением
    double max = 1.7e308;
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < M + 2; j++) {
            if (i == 0 || j == 0 || i == N + 1 || j == M + 1) {
                array[i][j] = max;
            }
        }
    }

    // Ввод матрицы (за исключением крайних строк и столбцов)
    cout << "\nВведите матрицу " << N << "x" << M << ": \n";
    array = input_array(array, &N, &M);

    // Подсчет количества локальных минимумов
    int local_min = 0;
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < M + 1; j++) {

            // Сравнение текущего элемента со всеми элементами, которые его окружают
            if (array[i][j] < array[i - 1][j - 1] && array[i][j] < array[i - 1][j] && array[i][j] < array[i - 1][j + 1] &&  // 1 2 3
                array[i][j] < array[i][j - 1] && array[i][j] < array[i][j + 1] &&                                           // 4   6
                array[i][j] < array[i + 1][j - 1] && array[i][j] < array[i + 1][j] && array[i][j] < array[i + 1][j + 1]) {  // 7 8 9

                local_min++;
            }
       
        }
    }

    cout << "\nКоличество локальных минимумов: " << local_min << "\n";

    // Удаление динамического массива (N+2)x(N+2)
    for (int i = 0; i < N + 2; i++) {
        delete[] array[i];
    } delete[] array;

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

double** input_array(double** array, int* N, int *M) {
    // Проверка на корректность ввода

    double x; // Вводимый элемент
    bool repeat; // Повторить ввод

    do {
        repeat = false;
        for (int i = 1; i < *N + 1 && !repeat; i++) {
            for (int j = 1; j < *M + 1 && !repeat; j++) {

                // Извлечение символа из буфера
                cin >> x;
                
                if (!cin.fail() &&                               // Последнее извлечение удачно
                    (cin.peek() == ' ' || cin.peek() == '\n')) { // Последний неизвлеченный символ пробел или Enter

                    // Пропуск пробелов после элемента
                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');

                    // Если размер строки больше / меньше, чем запрашивается
                    if (cin.peek() == '\n' && j != *M ||  
                        j == *M && cin.peek() != '\n')
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