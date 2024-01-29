// Лабораторная 4, задача 11. Выполнена: Кончик Д. С.

/*
Дан трёхмерный динамический массив размером n^3 целых неотрицательных чисел.
Необходимо определить диагональ с наибольшей суммой чисел.
Для обхода диагоналей нельзя использовать вложенные циклы.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
int*** input_array(int*** array, int* N);

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(1);

    cout << "Введите порядок трехмерного массива: ";
    int N = input_N();
    cout << "Заполните его целыми неотрицательными числами. \n";

    // Трехмерный динамический массив (куб)
    int*** A = new int** [N];
    for (int i = 0; i < N; i++)
    {
        A[i] = new int* [N];
        for (int j = 0; j < N; j++) {
            A[i][j] = new int[N];
        }
    }
    /*
    // Ввод куба
    cout << "\nВведите куб " << N << "x" << N << "x" << N << ": ";
    A = input_array(A, &N);*/

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int h = 0; h < N; h++) {
                A[i][j][h] = rand() % 14 + 1;
            }
        }
    }

    // Двумерный динамический массив, содержащий диагонали куба
    int** d = new int* [4];
    for (int i = 0; i < 4; i++) {
        d[i] = new int[N];
    }

    // 1 диагональ
    for (int i = 0; i < N; i++) {
        d[0][i] = A[i][i][i];
    }

    // 2 диагональ
    int x = N - 1, y = N - 1;
    for (int i = 0; i < N; i++) {
        d[1][i] = A[i][x][y];
        x--; y--;
    }

    // 3 диагональ
    x = N - 1; y = 0;
    for (int i = 0; i < N; i++) {
        d[2][i] = A[i][x][y];
        x--; y++;
    }

    // 4 диагональ
    x = 0; y = N - 1;
    for (int i = 0; i < N; i++) {
        d[3][i] = A[i][x][y];
        x++; y--;
    }


    // Вывод диагоналей и расчет сумм их элементов
    int s[4] = { 0,0,0,0 }; // Массив сумм диагоналей
    cout << "\nДиагонали куба: \n";
    for (int i = 0; i < 4; i++) {
        cout << "#" << i + 1 << ": ";
        for (int j = 0; j < N; j++) {
            cout << d[i][j] << " ";
            s[i] += d[i][j];
        }
        cout << "\t | S = " << s[i];
        cout << "\n";
    }

    // Поиск номера максимальной диагонали
    int num_of_max = 0;
    for (int i = 0; i < 4; i++) {
        num_of_max = s[i] > s[num_of_max] ? i : num_of_max;
    }

    // Вывод максимальной диагонали
    cout << "\nМаксимальная диагональ #" << num_of_max + 1 << ": \n";
    for (int i = 0; i < N; i++) {
        cout << d[num_of_max][i] << " ";
    } cout << "\t | S = " << s[num_of_max];
    cout << "\n\nP.s: Если максимальных диагоналей было несколько," <<
        "\nто была выведена диагональ с наименьшим номером.\n";






    // Удаление динамических массивов
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            delete[] A[i][j];
        }
    } delete[] A;

    for (int i = 0; i < 4; i++) {
        delete[] d[i];
    } delete[] d;

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
    cout << "\nПовторите ввод куба: ";
}

int*** input_array(int*** A, int* N) {

    int x;
    int h = 0;
    bool repeat; // Повторить ввод

    // Ввод куба + проверка на корректность ввода
    do {
        repeat = false;
        for (h = 0; h < *N && !repeat; h++) {

            cout << "\n#" << h + 1 << " слой куба: \n";

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
                        A[h][i][j] = x;
                    }
                    else {
                        repeat_input(&repeat);
                    }

                }
            }

            // Если элементов больше, чем запрашивается
            if (!repeat && cin.peek() != '\n')
                repeat_input(&repeat);
        }

        

    } while (repeat);

   
    // Взвращение массива
    return A;
}