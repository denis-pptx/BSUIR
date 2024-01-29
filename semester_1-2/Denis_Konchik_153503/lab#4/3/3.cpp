// Лабораторная 4, задача 3. Выполнена: Кончик Д. С.

/*
Дана действительная квадратная матрица порядка N.
Найти сумму и произведение элементов, расположенных в заштрихованной части матрицы,
см. рисунок «б».
*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
double** input_array(double** array, int* N);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите порядок матрицы: ";
    int N = input_N();

    // Динамический массив NxN
    double** array = new double* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new double[N];
    }

    // Ввод матрицы N-го порядка
    cout << "\nВведите матрицу " << N << "-го порядка: \n";
    array = input_array(array, &N);


    // Расчет произведения и суммы по условию
    double S = 0; // Сумма 
    double P = 1; // Произведение 
    int stop = 1;

    for (int i = 0; i < N; i++) {
        // Левая часть матрицы
        for (int j = 0; j < stop; j++) {
            S += array[i][j];
            P *= array[i][j];
        }

        // Правая часть матрицы
        for (int j = N - 1; j > N - 1 - stop; j--) {
            if (!(N % 2 == 1 && i == N / 2 && j == N / 2)) { // Центральный элемент матрицы нечетного порядка не прибивлять
                S += array[i][j];
                P *= array[i][j];
            }
        }

        /* "stop" - число элементов строки слева направо (левая часть),
           соответствующих зашрихованной части матрицы
           до элемента в середине строки (для следующей итерации цикла) */

        if (N % 2 == 1)
            stop += i < N / 2 ? 1 : -1;
        else if (N % 2 == 0 && i != N / 2 - 1)
            stop += i < N / 2 ? 1 : -1;
    }


    cout << "\nСумма: " << S;
    cout << "\nПроизведение: " << P << "\n";


    // Удаление динамического массива
    for (int i = 0; i < N; i++) {
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

double** input_array(double** array, int* N) {
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
                    if (cin.peek() == '\n' && j != *N ||
                        j == *N && cin.peek() != '\n')
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