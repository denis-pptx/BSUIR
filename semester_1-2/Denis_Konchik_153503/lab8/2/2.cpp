// Лабораторная 8, задача 2. Выполнена: Кончик Д. С.

/*
[Вариант 14]:
Список товаров, имеющихся на складе, включает в себя наименование товара, количество единиц товара, 
цену единицы и дату поступления товара на склад. Вывести в алфавитном порядке список товаров, 
хранящихся больше месяца, стоимость которых превышает 1000 руб.
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include "Product.h"
using namespace std;

extern string storage, result;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Product* Item = 0; // Указатель на массив товаров
    int N = 0; // Число товаров

    cout << "Ввод даты в формате ДД.ММ.ГГГГ\n";
    CMD(); // Все команды
    string command;
    do {
        cout << "\n";
        
        getline(cin, command);
        cin.putback('\n');

        if (command == "add")
            Item = AddItem(Item, N);
        else if (command == "print")
            PrintAll(Item, N);
        else if (command == "cls")
            system("cls");
        else if (command == "cmd")
            CMD();
        else if (command == "delete")
            Item = DeleteItem(Item, N);
        else if (command == "edit")
            EditItem(Item, N);
        else if (command == "prints")
            PrintSort(Item, N);
        else if (command != "exit")
            cout << "Неизвестная команда\n";
        
        cin.ignore(1, '\n');
        WriteInFile(Item, N, storage);
    } while (command != "exit");

}

