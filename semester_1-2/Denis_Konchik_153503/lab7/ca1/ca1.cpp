// Лабораторная 7, задача 9. Выполнена: Кончик Д. С.

/*
Вчера на уроке математики Саша узнал о том, что иногда полезно использовать вместо десятичной системы счисления
какую-нибудь другую. Однако, учительница (как иронично) не объяснила, почему в системе счисления по основанию b в
качестве цифр выбирают числа от 0 до b - 1. Немного подумав, Саша понял, что можно выбирать и другие наборы цифр.
Например, вместо троичной системы счисления можно рассмотреть систему счисления, где вместо обычных цифр 0, 1, 2
есть цифры 1, 2 и 3. Саша заинтересовался вопросом, а как перевести число n в эту систему счисления?
Например, число 7 в этой системе записывается как 21, так как 7 = 2*3 + 1,
а число 22 записывается как 211, так как 22 = 2*3^2 + 1*3^1 + 1*3^0.

[Входные данные]
Натуральное число n, 1 ≤ n ≤ 2*10^9
7
22

[Выходные данные]
Число n, записанное в указанной системе счисления
21
211
*/

#include <iostream>
#include <cstring>
using namespace std;

string ToTernaryStr(int);
string ElseTernary(string);
int len(string);
int find(string, string);
void replace(string&, int, string);
void erase(string&, int);

int main()
{
    // Количество ответов
    cout << "Enter amount of numbers: ";
    int amount; cin >> amount;

    string* ans = new string[amount];

    // Ввод чисел, подсчет ответов
    cout << "Enter " << amount << " numbers: \n";
    for (int i = 0; i < amount; i++) {
        int n; cin >> n;

        ans[i] = ToTernaryStr(n);
        ans[i] = ElseTernary(ans[i]);
    }

    // Вывод
    cout << "\n";
    for (int i = 0; i < amount; i++)
        cout << ans[i] << "\n";

    return 0;
}



string ToTernaryStr(int n) {
    // Перевод из int в string троичную систему

    string ternary = "";
    while (n) {
        ternary = (char)(n % 3 + 48) + ternary;
        n /= 3;
    }

    return ternary;
}

int len(string str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

int find(string str, string f) {

    int pos = -1;

    for (int i = 0; i < len(str); i++) {
        if (str[i] == f[0]) {
            bool eq = true;
            int _i = i;
            for (int j = 0; j < len(f); j++) {
                if (f[j] != str[_i++]) {
                    eq = false;
                    break;
                }
            }

            if (eq) return i;
        }
    }

    return pos;
}

void replace(string& str, int pos, string on) {
    string NewStr;

    int j = 0;
    for (int i = pos; i < pos + len(on); i++)
        str[i] = on[j++];
}

void erase(string& str, int pos) {
    for (int i = pos; i < len(str); i++)
        str[i] = str[i + 1];
}

string ElseTernary(string ternary) {
    // Перевод в систему по условию

    // Если бит 0, то забираем на него
    // единицу у более старшего бита

    int P = find(ternary, "10");
    while (P != -1) {
        replace(ternary, P, "03");
        P = find(ternary, "10");
    }

    P = find(ternary, "20");
    while (P != -1) {
        replace(ternary, P, "13");
        P = find(ternary, "20");
    }

    P = find(ternary, "30");
    while (P != -1) {
        replace(ternary, P, "13");
        P = find(ternary, "30");
    }

    while (len(ternary) > 1 && ternary[0] == '0')
        erase(ternary, 0);

    if (len(ternary) == 0)
        ternary = "0";

    return ternary;
}
