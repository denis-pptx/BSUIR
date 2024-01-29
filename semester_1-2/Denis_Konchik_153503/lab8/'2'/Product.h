#pragma once
#include <string>
using namespace std;

class Product {
private:
    char num[100];  // ����������������� �����
    char name[100]; // ������������ ������
    double amount;  // ���������� ������
    double price;   // ����
    int date[3];    // ���� ����������� �� �����

public:
    Product() : num{ 0 }, name{ 0 }, amount{ 0 }, price{ 0 }, date{ 0 } {}

    void set(char enter = '\n');
    void get();

    char* GetNum();
    char* GetName();
    int* GetDate();
    double GetPrice();
};

