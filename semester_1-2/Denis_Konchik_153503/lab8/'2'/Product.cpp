#include <iostream>
#include <string>
#include "Product.h"
#include "Functions.h"
using namespace std;

void Product::set(char enter) {
    // Сеттер
   
    cout << enter << "Номер: "; strget(num);
    cout << "Наименование: "; strget(name);
    
    amount = input("Количество: ");
    price = input("Цена единицы: ");
    InputDate(date, "Дата: ");

    cout << "[Добавлено]\n\n";

}

void Product::get() {
    // Геттер
    cout.setf(ios::fixed); cout.precision(2);

    cout << "\nНомер: " << num;
    cout << "\nНаименование: " << name;
    cout << "\nКоличество: " << amount;
    cout << "\nЦена единицы: " << price;
    cout << "\nДата: " << date[0] << '.' << date[1] << '.' << date[2];
}

char* Product::GetNum() {
    return num;
}

char* Product::GetName() {
    return name;
}

int* Product::GetDate() {
    return date;
}


double Product::GetPrice() {
    return price;
}