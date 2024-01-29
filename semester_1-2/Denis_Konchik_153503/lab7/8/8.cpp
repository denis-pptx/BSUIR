// Лабораторная 7, задача 8. Выполнена: Кончик Д. С.

/*
Брюс недавно получил работу в NEERC, где изучают и строят много различных любопытных чисел. 
Его первым заданием  стало исследование двудесятичных чисел.
Натуральное число называется двудесятичным, если его десятичное представление является суффиксом 
его двоичного представления; и двоичное и десятичное  представление рассматривается без ведущих нулей. 
Например, 10(10) = 1010(2), так что 10 двудесятичное число. 
Числа 1010(10) = 1111110010(2) и 42(10) = 101010(2) не являются двудесятичными.
Сначала Брюс хочет создать список двудесятичных чисел. Помогите ему найти n-ое наименьшее двудесятичное число.

[Входные данные]
Одно целое число n (1 ≤ n ≤ 10 000).
1
2
10

[Выходные данные]
Вывести одно число - n-ое наименьшее двудесятичное число в десятичном представлении.
1
10
1100
*/

#include <iostream>
#define ull unsigned long long
using namespace std;

// ОГРАНИЧИТЬ n НА 50

ull BinarySuffix(ull);
ull power(ull, int);
int len(ull);
int DigitByNumber(ull, int); 
ull AnsByNumber(int n);
int input_int();

int main()
{
    // Количество ответов
    cout << "Enter amount of numbers: ";
    int amount = input_int();

    ull* ans = new ull[amount];

    // Ввод чисел, подсчет ответов
    cout << "Enter " << amount << " numbers (>= 1, <= 50): \n";
    for (int i = 0; i < amount; i++) {
        int n = input_int();
        ans[i] = AnsByNumber(n);
    }
    
    // Вывод
    cout << "\n";
    for (int i = 0; i < amount; i++)
        cout << ans[i] << "\n";
 
    return 0;
}


ull AnsByNumber(int n) {
    ull num = 1; // Число в десятичной форме
    int N = 0; // Номер двудесятичного числа

    while (true) {
        // Если суффикс в бинарном коде равен числу в десятичной форме
        if (BinarySuffix(num) == num)
            N++;

        if (N == n)
            break;

        num++;

        // Если хотя бы одна цифра в числе не 0 или не 1
        for (int i = 0; i < len(num) - 1; i++) {
            if (!(DigitByNumber(num, i) == 0 || DigitByNumber(num, i) == 1)) {
                num -= num % power(10, i + 1);
                num += power(10, i + 1);
            }
        }
    }

    return num;
}

int DigitByNumber(ull number, int N) {
    // Цифра с конца по номеру (индекс с 0)
    return (number % power(10, N + 1) - (number % power(10, N))) / power(10, N);
}

int len(ull n) {
    // Число цифр в числе

    int symb = 0;
    while (n) {
        symb++;
        n /= 10;
    }
    return symb;
}

ull BinarySuffix(ull num) {
    // Перевести в бинарный код,
    // цифр столько же, сколько в num

    ull Binary = 0, BitNum = 0, k = 1;

    while (num && len(Binary) <= len(num)) {
        Binary += (num % 2) * k;
        num /= 2;
        k *= 10;
    }

    return Binary;
}

ull power(ull x, int n) {
    if (n == 0)
        return 1;
    else
        return x * power(x, n - 1);
}


int input_int() {
    int x;

    while (true) {
        cin >> x;

        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        if (cin.fail() || cin.peek() != '\n' || !(x >= 1 && x <= 50)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Repeat input: ";
        }
        else {
            return x;
        }
    }
}