// Лабораторная 4, задача 8. Выполнена: Кончик Д. С.

/*
Заменить нулями все элементы, которые находятся в ячейках между минимальным и максимальным элементами (не включая их).
Изначально все элементы в массиве различные. Если после данного действия большая часть массива будет содержать нули,
то удалить все нулевые элементы из массива (c сохранением порядка следования остальных элементов).
*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
double* input_array(double* array, int* N);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Введите количество элементов массива: ";
    int N = input_N();

    cout << "Элементы массива не должны повторяться.\n";
    cout << "\nВведите массив из " << N << " элемент" << ((N == 1) ? "а" : "ов") << ": \n";
    
   
    double* array = new double[N];
    array = input_array(array, &N);

    // Проверка, чтобы все элементы массива были разными
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (array[i] == array[j]) {
                cout << "Некоторые элементы массива повторяются.";
                return 0;
            }
        }
    }
    // Поиск минимального и максимального элементов массива
    double min = array[0]; // Значения
    double max = array[0]; // мин. и макс. элементов

    int min_num = 0; // Номера
    int max_num = 0; // мин. и макс. элементов

    for (int i = 0; i < N; i++) {
        if (array[i] > max) {
            max = array[i];
            max_num = i;
        }
        if (array[i] < min) {
            min = array[i];
            min_num = i;
        }
    }

    // Начало и конец номеров для замены на 0
    int start = 0;
    int stop = 0;
    if (max_num > min_num) {
        start = min_num + 1;
        stop = max_num - 1;
    }
    else {
        start = max_num + 1;
        stop = min_num - 1;
    }



    // Замена нулями по условию
    for (int i = start; i <= stop; i++) {
        array[i] = 0;
    }

    // Число нулей
    int zero = 0;
    for (int i = 0; i < N; i++) {
        if (array[i] == 0) {
            zero++;
        }
    }


    // Если большая часть нули
    if (zero > (N - zero)) {
        int* no_zero_arr = new int[N - zero];
        int j = 0; // Счетчик элементов для нового массива

        // Заполнение нового массива
        for (int i = 0; i < N; i++) {
            if (array[i] != 0) {
                no_zero_arr[j++] = array[i];
            }
        }

        // Вывод массива
        cout << "\nНовый массив: \n";
        for (int i = 0; i < j; i++) {
            cout << no_zero_arr[i] << " ";
        }

        delete[] no_zero_arr;
    }
    else {
        // Вывод массива
        cout << "\nНовый массив: \n";
        for (int i = 0; i < N; i++) {
            cout << array[i] << " ";
        }
    }

    cout << "\n";

    delete[] array;

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
    bool repeat;
    // Ввод массива + проверка на корректность ввода
    do {
        repeat = false;

        for (int i = 0; i < *N && !repeat; i++) {

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

            // Проверка элементов на повторяемость
            for (int j = 0; j < i && !repeat; j++) {
                if (x == array[j]) {
                    repeat_input(&repeat);
                }
            }
        }

        // Если элементов больше, чем запрашивается
        if (!repeat && cin.peek() != '\n') 
            repeat_input(&repeat);
        
    } while (repeat);

    // Возвращение массива
    return array;
}