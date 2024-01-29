// Лабораторная 7, задача 7. Выполнена: Кончик Д. С.

/*
Разработать программу, которая проверяет, делится ли введенное пользователем число на заданное простое. 
Программа не должна содержать операций умножения, деления, вычитания (в том числе взятия остатка от деления).  
Рекомендуется использовать побитовые операции. Для каждого варианта нужно проверить делимость на 3 простых числа. 
Проверять можно по отдельности (сначала получить ответ для первого, затем для второго, затем для третьего).

[Вариант 13]: 3, 23, 107
*/

#include <iostream>
using namespace std;

int Sum(int num1, int num2);
int ChangeSign(int n);
int getSign(int n);
int module(int n);
int divide(int a, int b);
int input_int();

bool isDivide(int a, int b) {
    int k = divide(a, b); // a : b

    int S = 0; // Сумма k чисел var
    for (int j = 0; j < k; j = Sum(j, 1))
        S = Sum(S, b);

    return S == a ? true : false;
}


int main()
{

    int var[3] = { 3,23,107 }; // Числа 13 варианта

    cout << "Enter X: ";
    int x = input_int();
    x = module(x); // Модуль x

    for (int i = 0; i < 3; i = Sum(i,1)) {
        // Вывод
        cout << "\nX / " << var[i] << ": ";
        if (isDivide(x, var[i]))
            cout << "YES";
        else
            cout << "NO";
        
    }
    cout << "\n";

	return 0;
}

int divide(int a, int b) {
    // Делитель не может быть 0
    if (b == 0) {
        cout << "ERROR";
        exit(0);
    }

    // Получение знака ответа
    bool Negative = false;
    if (getSign(a) ^ getSign(b)) // Знаковые биты отличаются
        Negative = true;

    // Модули чисел
    a = module(a);
    b = module(b);

    // Ответ
    int answer = 0;

    // answer - сколько раз можно вычесть b из a
    while (a >= b) {
        answer = Sum(answer, 1);
        a = Sum(a, ChangeSign(b));
    }

    if (Negative)
        return ChangeSign(answer);
    else
        return answer;

}

int Sum(int num1, int num2) {
    // Сумма

    int answer = 0, transfer = 0;

    answer = num1 ^ num2;
    // Если какие-то соответствующие биты 1,
    // то переносим их дальше влево
    transfer = (num1 & num2) << 1;

    // пока будет нечего переносить
    while (transfer) {
        int temp = answer;
        answer = answer ^ transfer;
        transfer = (temp & transfer) << 1;
    }

    return answer;
}

int ChangeSign(int n) {
    // Отрицание битов X = -X - 1
    // add(~n, 1) = -n - 1 + 1 = -n
    return Sum(~n, 1);
}

int getSign(int n) {
    // Получить знаковый бит
    return n >> 31;
}

int module(int n) {
    // Модуль n

    if (getSign(n) & 1) // Число отрицательное, знаковый бит 1
        return ChangeSign(n); // Сделать отрицательным
    else
        return n; // Оставить таким же
}



int input_int() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Repeat input: ";
        }
        else {
            return x;
        }
    }
}