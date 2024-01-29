#pragma once

#include <iostream>
#include <string>
using namespace std;

class Human {
private:
    char name[100];    // ФИО
    char tabel[100];   // Табельный номер
    double hour;    // Проработанные часы
    double rate;    // Почасовой тариф
    double salary;  // ЗП

public:

    Human() : name{ 0 }, tabel{ 0 }, hour{ 0 }, rate{ 0 }, salary{ 0 } {}

    void count();
    void set(char enter = '\n');
    void get();
    char* GetTabel();
    char* GetName();
};
