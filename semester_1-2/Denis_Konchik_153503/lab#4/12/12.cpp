// Лабораторная 4, задача 12. Выполнена: Кончик Д. С.

/*
Написать функцию, которая будет удалять дубликаты элементов из массива.
Входные параметры: массив, длинна массива.
Выходные параметры: новый массив, новый размер.
*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
double* input_array(double* array, int* N);
double* no_duplicate(double* array, int* N);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Количество элементов массива: ";
    int N = input_N();

    cout << "\nВведите массив из " << N << " элемент" << ((N == 1) ? "а" : "ов") << ": \n";
    double* array = new double[N];
    array = input_array(array, &N);

    // Массив без дубликатов
    double* new_array = 0;
    new_array = no_duplicate(array, &N);

    // Вывод массива без дубликатов
    cout << "\nМассив без дубликатов [" << N << "]: \n";
    for (int i = 0; i < N; i++) {
        cout << new_array[i] << " ";
    } cout << "\n";

    
    delete[] array;
    delete[] new_array;

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
    cout << "\nПовторите ввод массива: \n";
}

double* input_array(double* array, int* N) {

    double x;
    int i = 0;
    bool repeat;
    // Ввод массива + проверка на корректность ввода
    do {
        repeat = false;

        for (i = 0; i < *N && !repeat; i++) {

            // Извлечение числа из буфера
            cin >> x;

            // Если (последнее извлечение удачно) 
            // И (последний неизвлеченный символ пробел или перенос на новую строку)
            if (!cin.fail() && (cin.peek() == ' ' || cin.peek() == '\n')) {

                // Пропуск пробелов после элемента
                while (cin.peek() == ' ')
                    cin.ignore(1, ' ');

                // Если размер строки больше / меньше, чем запрашивается
                if (cin.peek() == '\n' && i != *N - 1)
                    repeat_input(&repeat);

                array[i] = x;
            }
            else {
                repeat_input(&repeat);
            }

        }

        // Если элементов больше, чем запрашивается
        if (!repeat && cin.peek() != '\n')
            repeat_input(&repeat);

    } while (repeat);

    // Взвращение массива
    return array;
}

double* no_duplicate(double* array, int* N) {
    double* new_arr = new double[*N];

    int k = 0; // Индексы элементов массива без дубликатов
    int add = 1; // Добавить элемент в массив без дубликатов или нет

    // Заполнение массива без дубликатов
    new_arr[k++] = array[0];
    for (int i = 1; i < *N; i++) {
        // Сравнение текущего элемента исходного массива со всеми элементами массива без дубликатов
        for (int j = 0; j < k; j++) {
            // Если элемент уже есть в массиве без дубликатов, то не добавляем
            if (array[i] == new_arr[j]) {
                add = 0;
                break;
            }
        }

        // Добавление элемента в массив без дубликатов
        if (add) {
            new_arr[k++] = array[i];
        } add = 1;
    }

    *N = k;
    return new_arr;
}
