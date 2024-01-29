#include <iostream>
#include <string>
#include "Product.h"
#include "Functions.h"
using namespace std;

void Product::set(char enter) {
    // ������
   
    cout << enter << "�����: "; strget(num);
    cout << "������������: "; strget(name);
    
    amount = input("����������: ");
    price = input("���� �������: ");
    InputDate(date, "����: ");

    cout << "[���������]\n\n";

}

void Product::get() {
    // ������
    cout.setf(ios::fixed); cout.precision(2);

    cout << "\n�����: " << num;
    cout << "\n������������: " << name;
    cout << "\n����������: " << amount;
    cout << "\n���� �������: " << price;
    cout << "\n����: " << date[0] << '.' << date[1] << '.' << date[2];
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