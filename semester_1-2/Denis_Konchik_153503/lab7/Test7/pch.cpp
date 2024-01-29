//
// pch.cpp
//

#include "pch.h"

bool isDivide(int a, int b) {

    a = a < 0 ? -a : a;

    int k = divide(a, b); // a : b

    int S = 0; // Сумма k чисел var
    for (int j = 0; j < k; j = Sum(j, 1))
        S = Sum(S, b);

    return S == a ? true : false;
}


int divide(int a, int b) {
    // Делитель не может быть 0
    if (b == 0) {
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

