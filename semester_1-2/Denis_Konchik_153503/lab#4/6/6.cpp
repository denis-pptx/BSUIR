// Лабораторная 4, задача 6. Выполнена: Кончик Д. С.

/*
Для заданной матрицы A размерности NxM построить матрицу B такого же размера,
элементы которой обладают следующим свойством: элемент B[i,j] равен максимальному
из элементов матрицы A, расположенных левее и выше позиции (i,j), включая позицию (i,j).
При этом считается, что позиция (1,1) - верхняя левая позиция матрицы.
Например:
5   8   9   8         5   8   9   9
6   7   10  7   ->    6   8   10  10
3   9   1   5         6   9   10  10

*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
double** input_array(double** array, int* N, int* M);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите размерность матрицы.\n";
    cout << "Строки: "; int N = input_N();
    cout << "Столбцы: "; int M = input_N();

    // Динамический массив NxM
    double** array = new double* [N];
    for (int i = 0; i < N; i++) {
        array[i] = new double[M];
    }

    // Ввод матрицы NxM
    cout << "\nВведите матрицу " << N << "x" << M << ": \n";
    array = input_array(array, &N, &M);

    // Динамический массив NxM (матрица по условию)
    double** new_array = new double* [N];
    for (int i = 0; i < N; i++) {
        new_array[i] = new double[M];
    }

    // Расчет новой матрицы
    double max; // Максимальный элемент (по условию)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            
            max = array[0][0];
            for (int m = 0; m <= i; m++) {
                for (int n = 0; n <= j; n++) {
                    max = array[m][n] > max ? array[m][n] : max;
                }
            }

            new_array[i][j] = max > array[i][j] ? max : array[i][j];
        }
    }
   

    cout << "\nНовая матрица: \n";
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