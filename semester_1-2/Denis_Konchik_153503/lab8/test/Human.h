#pragma once

#include <iostream>
#include <string>
using namespace std;

class Human {
private:
    string name;    // ���
    string tabel;   // ��������� �����
    double hour;    // ������������� ����
    double rate;    // ��������� �����
    double salary;  // ��

public:

    Human() : name{ "" }, tabel{ 0 }, hour{ 0 }, rate{ 0 }, salary{ 0 } {}

    void count();
    void set(char enter = '\n');
    void get();
    string GetTabel();
    string GetName();
};
