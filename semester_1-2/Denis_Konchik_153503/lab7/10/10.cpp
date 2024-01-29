// Лабораторная 7, задача 10. Выполнена: Кончик Д. С.

/*
Патриций решил устроить праздник и для этого приготовил 240 бочек вина. 
Однако к нему пробрался недоброжелатель, который подсыпал яд в одну из бочек. 
Недоброжелателя тут же поймали, дальнейшая его судьба неизвестна. 
Про яд известно, что человек, который его выпил, умирает в течение 24 часов. 
До праздника осталось два дня, то есть 48 часов. 
У патриция есть пять рабов, которыми он готов пожертвовать, 
чтобы узнать, в какой именно бочке яд. 
Каким образом можно это узнать?
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

string ToTernaryStr(int);
int TernaryStrToInt(string);
int len(string);
void Reverse(string&);
int PATRICIAN(int, int&);
int input_barell();

int main()
{
    setlocale(LC_ALL, "Rus");
    // Ввод отправленной бочки
    cout << "Enter the number of the poisoned barrel (1 - 240): ";
    int N = input_barell();

    // Выжило рабов
    int LIVE = 0;
    
    // Полученный номер отправленной бочки
    int AnsPoison = PATRICIAN(N, LIVE);

    cout << "Poisoned barrel: " << AnsPoison;
    cout << "\nAlived slaves: " << LIVE << "\n";

    return 0;
}


int PATRICIAN(int N, int& LIVE) {
    string poison = ToTernaryStr(N);

    // Массив номеров бочек в троичной системе счисления
    string* barell = new string[240];

    for (int i = 0; i < 240; i++)
        barell[i] = ToTernaryStr(i + 1);

    // Массив жив ли раб
    int Slave[5] = { 1,1,1,1,1 };

    // ########################## ПЕРВЫЙ ДЕНЬ ##########################

        // i раб пробует бочку с нулем на i позиции
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < 240; b++)
            if (barell[b][s] == '0' && barell[b] == poison)
                Slave[s] = 0;

    }

    cout << "\nПЕРВЫЙ ДЕНЬ:";
    // Подсчет выживших рабов
    int alive = 0;
    for (int i = 0; i < 5; i++)
        if (Slave[i])
            alive++;
        else
            cout << "\nDied #" << i + 1;
    cout << "\n";

    // Бочки, которые осталось проверить после первого дня
    string* AfterDayOne = new string[240];
    int AfterD1 = 0;

    if (alive == 5) {
        // Если выжили все, то осталось проверить бочки,
        // в номерах которых нет ни одного нуля

        for (int b = 0; b < 240; b++) {
            bool add = true;

            for (int i = 0; i < 5; i++)
                if (barell[b][i] == '0')
                    add = false;

            if (add)
                AfterDayOne[AfterD1++] = barell[b];
        }
    }
    else {
        // Иначе, осталось проверять бочки с нулями позиций,
        // равыным умершим рабам

        for (int b = 0; b < 240; b++) {
            // Добавить бочку для дальнейшей проверки или нет
            bool add = true;
            for (int s = 0; s < 5; s++) {
                // Если раб мертв и на позиции его номера нет 0
                if (Slave[s] == 0 && barell[b][s] != '0')
                    add = false;
            }
            if (add)
                AfterDayOne[AfterD1++] = barell[b];
        }
    }


    // ########################## ВТОРОЙ ДЕНЬ ##########################

    int TempSlave[5]; // Копия массива рабов
    for (int i = 0; i < 5; i++)
        TempSlave[i] = Slave[i];

    // i раб пробует бочку с единицей на i позиции
    for (int s = 0; s < 5; s++) {
        for (int b = 0; b < AfterD1; b++)
            if (TempSlave[s] && AfterDayOne[b][s] == '1' && AfterDayOne[b] == poison)
                TempSlave[s] = 0;
    }

    cout << "\nВТОРОЙ ДЕНЬ:";

    for (int i = 0; i < 5; i++) 
        if (TempSlave[i] == 0 && Slave[i] == 1)
            cout << "\nDied #" << i + 1;
    
    cout << "\n\n";

    // Бочки, которые осталось проверить после второго дня
    string* AfterDayTwo = new string[240];
    int AfterD2 = 0;

    // Осталось проверять бочки с единицам позиций,
    // равыным умершим рабам

    

    for (int b = 0; b < AfterD1; b++) {
        // Добавить бочку для дальнейшей проверки или нет
        bool add = true;
        for (int s = 0; s < 5; s++) {
            // Если раб умер во второй день и на позиции его номера нет 1
            if (Slave[s] == 1 && TempSlave[s] == 0 && AfterDayOne[b][s] != '1') 
                add = false;
            
        }
        if (add)
            AfterDayTwo[AfterD2++] = AfterDayOne[b];
    }

    
    // Если раб не умер, то на его позиции поставить 2
    LIVE = 0; // выжило рабов
    for (int i = 0; i < 5; i++) {
        if (TempSlave[i]) {
            LIVE++;
            for (int b = 0; b < AfterD2; b++)
                AfterDayTwo[b][i] = '2';
        }
    }



    // Отравленная бочка
    int AnsPoison = TernaryStrToInt(AfterDayTwo[0]);

    return AnsPoison;
}


int TernaryStrToInt(string num) {
   
    Reverse(num);
    int digit = 0;

    for (int i = 0; i < len(num); i++)
        digit += (num[i] - '0') * (int)pow(3, i);

    return digit;
}

string ToTernaryStr(int n) {
    // Перевод из int в string троичную систему

    string ternary = "";
    while (n) {
        ternary = (char)((n % 3) + 48) + ternary;
        n /= 3;
    }
 
    while (len(ternary) != 5)
        ternary = '0' + ternary;

    return ternary;
}

int len(string str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void Reverse(string& str) {
    // Реверс строки

    for (int i = 0; i < len(str) / 2; i++) {
        char temp = str[i];
        str[i] = str[len(str) - 1 - i];
        str[len(str) - 1 - i] = temp;
    }
}


int input_barell() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n' || !(x >= 1 && x <= 240)) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Repeat input: ";
        }
        else {
            return x;
        }
    }
}