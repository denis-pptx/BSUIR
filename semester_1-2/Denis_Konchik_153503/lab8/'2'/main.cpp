// Лабораторная 8, задача 2. Выполнена: Кончик Д. С.

/*
[Вариант 14]:
Список товаров, имеющихся на складе, включает в себя наименование товара, количество единиц товара,
цену единицы и дату поступления товара на склад. Вывести в алфавитном порядке список товаров,
хранящихся больше месяца, стоимость которых превышает 1000 руб.
*/

#include <iostream>
#include <windows.h>
#include "Product.h"
#include "Functions.h"
#include "FileWrite.h"
#include "Result.h"
#include <iostream>
#include <string>
using namespace std;

int N = 0; // Список всех товаров

int main()
{
    CheckOpen();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Ввод даты в формате ДД.ММ.ГГГГ\n";
    cout << "Максимальная длина строки - 100\n";

    // Указатель на массив классов
    Product* Item = 0;

    // Подгружаем файл
    Item = LoadFromFile(Item);

    string command; cmd();
    do {
        strget(command);

        if (command == "cmd")
            cmd();
        else if (command == "cls")
            system("cls");
        else if (command == "add")
            Item = AddItem(Item);
        else if (command == "print")
            PrintItem(Item);
        else if (command == "num")
            cout << "\nВсего товаров: " << N << "\n\n";
        else if (command == "del")
            Item = DelItem(Item);
        else if (command == "adel")
            Item = DelAll(Item);
        else if (command == "edit")
            EditItem(Item);
        /*else if (command == "prfile")
            PrintFile();*/
        else if (command == "ps")
            PrintSort(Item);
        else if (command != "exit")
            cout << "\nНеизвестная команда\n\n";


    } while (command != "exit");


    return 0;
}
