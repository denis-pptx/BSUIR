#include <iostream>
#include <string>
#include "Human.h"
#include "Functions.h"
using namespace std;


void Human::count() {
    // Подсчет зарплаты
    hour = fabs(hour);
    salary = hour * rate * 0.88;
    salary *= hour > 144 ? 2 : 1;
}

void Human::set(char enter) {
    // Сеттер
    cout << enter << "Имя: ";
    strget(name);

    cout << "Табельный номер: ";
    strget(tabel);

    hour = input("Часы: ");
    rate = input("Тариф: ");

    count();
    cout << "\n";
}

void Human::get() {
    // Геттер
    cout.setf(ios::fixed); cout.precision(2);

    cout << "\nИмя: " << name;
    cout << "\nТабельный номер: " << tabel;
    cout << "\nЧасы: " << hour;
    cout << "\nТариф: " << rate;
    cout << "\nЗарплата: " << salary;
}

string Human::GetTabel() {
    return tabel;
}

string Human::GetName() {
    return name;
}