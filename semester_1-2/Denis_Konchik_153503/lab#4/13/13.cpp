// Лабораторная 4, задача 13. Выполнена: Кончик Д. С.

/*
У Миши в общежитии всего лишь 1 розетка. Дабы исправить это недоразумение, 
Миша купил N удлинителей таких, что i-й удлинитель имеет a[i] входов. 
Вычислите, сколько розеток получится у Миши, если он оптимально соединит удлинители?
*/

#include <iostream>
using namespace std;

int input_N();
void repeat_input(bool* repeat);
int* input_array(int* array, int* N, int* S);

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    cout << "Количество удлинителей: ";
    int N = input_N();

    int* a = new int[N];
    int S = 0; // Всего входов

    cout << "\nКоличество входов в удлинителях: \n";
    a = input_array(a, &N, &S);
    

    int socket = S - N + 1; // Всего розеток
    cout << "\nВсего розеток: " << socket << "\n";

    // Удаление динамического массива
    delete[] a;
    
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
    cout << "\nПовторите ввод входов: \n";
}

int* input_array(int* a, int* N, int* S) {

    int x, i;
    bool repeat;
    // Ввод массива + проверка на корректность ввода
    do {
        repeat = false;
        *S = 0;

        for (i = 0; i < *N && !repeat; i++) {

            cout << "#" << i + 1 << ":  ";

            // Извлечение числа из буфера
            cin >> x;


            if (!cin.fail() &&                                 // Последнее извлечение удачно
                (cin.peek() == ' ' || cin.peek() == '\n') &&   // последний неизвлеченный символ пробел или Enter
                    x > 0) {                                   // Число входов больше нуля

                // Пропуск пробелов после элемента
                while (cin.peek() == ' ')
                    cin.ignore(1, ' ');
                
                
                if (cin.peek() != '\n')
                    repeat_input(&repeat);

                a[i] = x;
                *S += x;
            }
            else {
                repeat_input(&repeat);
            }

        }

    } while (repeat);

    // Взвращение массива
    return a;
}