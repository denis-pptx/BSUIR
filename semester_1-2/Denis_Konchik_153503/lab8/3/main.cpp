// Лабораторная 8, задача 3. Выполнена: Кончик Д. С.

/*
Реализовать любой из 30 вариантов заданий используя классы. 
Реализовать корректировку записей внутри файла без полной перезаписи файла. 
Все методы класса должны иметь модификатор public, а остальные поля – private.

Функции инициализации данных, добавления, удаления, корректировки и просмотра записей файла.

[2.11] Информация о сотрудниках фирмы включает: ФИО, табельный номер, количество проработанных часов за месяц, 
почасовой тариф. Рабочее время свыше 144 часов считается сверхурочным и оплачивается в двойном размере.  
Вывести размер ЗП каждого сотрудника за вычетом подоходного налога, который составляет 12% от суммы заработка.
*/

#include <iostream>
#include <string>
#include <windows.h>
#include "Human.h"
#include "Functions.h"
#include "FileWrite.h"
using namespace std;

int N = 0; // Число работников

int main()
{
    CheckOpen();
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Указатель на массив структур
    Human* Employee = 0;

    cout << "Имя - строка\nТабельный номер - строка\nЧасы - Q >= 0\nТариф - Q >= 0\nМакс. длина строки - 100\n";
    string command; cmd();
    do {
        strget(command);

        if (command == "cmd")
            cmd();
        else if (command == "cls")
            system("cls");
        else if (command == "add")
            Employee = AddEmployee(Employee);
        else if (command == "print")
            PrintEmployee(Employee);
        else if (command == "num")
            cout << "\nВсего работников: " << N << "\n\n";
        else if (command == "del")
            Employee = DelEmployee(Employee);
        else if (command == "adel")
            Employee = DelAll(Employee);
        else if (command == "edit")
            EditEmployee(Employee);
        else if (command == "prfile")
            PrintFile();
        else if (command == "clf")
            ClearFile();
        else if (command == "load")
            Employee = LoadFromFile(Employee);
        else if (command != "exit")
            cout << "\nНеизвестная команда\n\n";

       
    } while (command != "exit");


    return 0;
}
