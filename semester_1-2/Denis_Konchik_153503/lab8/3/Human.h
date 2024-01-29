#pragma once

#include <iostream>
#include <string>
using namespace std;

class Human {
private:
    char name[100];    // ���
    char tabel[100];   // ��������� �����
    double hour;    // ������������� ����
    double rate;    // ��������� �����
    double salary;  // ��

public:

    Human() : name{ 0 }, tabel{ 0 }, hour{ 0 }, rate{ 0 }, salary{ 0 } {}

    void count();
    void set(char enter = '\n');
    void get();
    char* GetTabel();
    char* GetName();
};
