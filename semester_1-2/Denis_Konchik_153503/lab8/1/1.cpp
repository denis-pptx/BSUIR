// Лабораторная 8, задача 1. Выполнена: Кончик Д. С.

/*
[Вариант 14]:
Ведомость абитуриентов, сдавших вступительные экзамены в университет, содержит ФИО абитуриента
и его оценки. Определить средний балл по университету и вывести список абитуриентов, средний балл которых
выше среднего балла по университету (сортировка выбором по возрастанию).
*/

#include <iostream>
#include <string>
#include <windows.h>
#include "Human.h"
using namespace std;


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "ФИО - три слова, разделенные пробелами\n" <<
            "Баллы - четыре числа, разделенные пробелами\n" <<
            "\nКоличество абитуриентов: ";
    int N = input();

    cout << "Делать ввод до встречи суммы баллов большей, чем: ";
    int stop = input(0);

    // Массив абитуриентов
    Abitur* Human = CreateArray(N);

    // Заполнение информации о абитуриентах
    FillAbitur(Human, N, 0, stop);

    // Все команды
    CMD();

    string command;
    do {
        cout << "\n";
        cin >> command;
        if (cin.peek() != '\n') {
            command = "unknown";
            cin.ignore(10000, '\n');
        }

        if (command == "printav")
            PrintAbitur(Human, N, CountAverage(Human, N));
        else if (command == "cls")
            system("cls");
        else if (command == "print")
            PrintAbitur(Human, N);
        else if (command == "sort")
            ChoiceSort(Human, N);
        else if (command == "add")
            Human = AddHuman(Human, N);
        else if (command == "printset") {
            if (N == 0) {
                cout << "\nСписок абитуриентов пуст\n";
            }
            else {
                cout << "Балл: ";
                int set = input(0);
                PrintAbitur(Human, N, -1, set);
            }
        }
        else if (command == "delete")
            Human = DeleteHuman(Human, N);
        else if (command == "edit")
            EditHuman(Human, N);
        else if (command == "cmd")
            CMD();
        else if (command != "exit")
            cout << "Неизвестная команда\n";

    } while (command != "exit");

    return 0;
}
