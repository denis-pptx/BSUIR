#include <iostream>
#include <string>
#include "Human.h"
#include "Functions.h"
using namespace std;


void Human::count() {
    // ������� ��������
    hour = fabs(hour);
    salary = hour * rate * 0.88;
    salary *= hour > 144 ? 2 : 1;
}

void Human::set(char enter) {
    // ������
    cout << enter << "���: ";
    strget(name);

    cout << "��������� �����: ";
    strget(tabel);

    hour = input("����: ");
    rate = input("�����: ");

    count();
    cout << "\n";
}

void Human::get() {
    // ������
    cout.setf(ios::fixed); cout.precision(2);

    cout << "\n���: " << name;
    cout << "\n��������� �����: " << tabel;
    cout << "\n����: " << hour;
    cout << "\n�����: " << rate;
    cout << "\n��������: " << salary;
}

string Human::GetTabel() {
    return tabel;
}

string Human::GetName() {
    return name;
}