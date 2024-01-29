// Лабораторная 4, задача 14. Выполнена: Кончик Д. С.

/*
На вход подаётся поле для игры в "сапёр" размером NxM символов,
где символ '.' означает пустое место, а символ '*' - бомбу.
Требуется дополнить это поле числами, как в оригинальной игре.
Выделение памяти через функции языка С.
*/

#include <iostream>
#include <malloc.h>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
char** input_field(char** field, int* N, int* M);

int main()
{
    setlocale(LC_ALL, "Rus");


    // Ввод данных
    cout << "Введите размеры поля \n";
    cout << "Строки: "; int N = input_N();
    cout << "Столбцы: "; int M = input_N();

    /*Создадим матрицу (N+2)x(M+2),
    крайние строки и столбцы проинициализируем
    сиволами "." (нет бомбы) */

    // Создание динамического массива (N+2)x(M+2)
    char** field = (char**)malloc((N + 2) * sizeof(int*));
    for (int i = 0; i < N + 2; i++) {
        field[i] = (char*)malloc((M + 2) * sizeof(int));
    }

    // Инициализация крайних строк и столбцов символами "."
    for (int i = 0; i < N + 2; i++) {
        for (int j = 0; j < N + 2; j++) {
            if (i == 0 || j == 0 || i == N + 1 || j == N + 1) {
                field[i][j] = '.';
            }
        }
    }

    // Ввод поля (за исключением крайних строк и столбцов)
    cout << "\nВведите поле " << N << "x" << M << ": \n";
    field = input_field(field, &N, &M);


    // Дополнение поля цифрами, как в игре "сапер"
    int bomb = 0; // Число бомб вокруг точки
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < M + 1; j++) {

            // Если элемент не бомба, то проверяем соседей на бомбы
            if (field[i][j] != '*') {

                for (int a = i - 1; a <= i + 1; a++) {
                    for (int b = j - 1; b <= j + 1; b++) {
                        if (field[a][b] == '*')
                            bomb++;
                    }
                }

                field[i][j] = bomb + '0'; // ASCII код цифры
                bomb = 0;
            }

        }
    }

    // Вывод заполненного поля
    cout << "\nЗаполненное поле: \n";
    for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < M + 1; j++) {
            cout << field[i][j] << " ";
        }
        cout << "\n";
    }

    // Освобождение памяти
    for (int i = 0; i < N + 2; i++) {
        free(field[i]);
    } free(field);

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
    cout << "\nПовторите ввод поля: \n";
}

char** input_field(char** field, int* N, int* M) {
    // Проверка на корректность ввода

    char x; // Вводимый элемент
    bool repeat; // Повторить ввод

    do {
        repeat = false;
        for (int i = 1; i < *N + 1 && !repeat; i++) {
            for (int j = 1; j < *M + 1 && !repeat; j++) {

                // Извлечение символа из буфера
                cin >> x; 

                if (!cin.fail() &&                               // Последнее извлечение удачно
                    (cin.peek() == ' ' || cin.peek() == '\n') && // Последний неизвлеченный символ пробел или Enter
                    (x == '.' || x == '*')) {                    // Введеннный символ * или .


                    // Пропуск пробелов после элемента
                    while (cin.peek() == ' ')
                        cin.ignore(1, ' ');
                    
                  

                    // Если размер строки больше / меньше, чем запрашивается
                    if (cin.peek() == '\n' && j != *M ||
                        j == *M && cin.peek() != '\n')
                        repeat_input(&repeat);

                    // Полложить элемент в массив
                    field[i][j] = x;
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
    return field;
}