#pragma once
#include <string>
using namespace std;

class Product {
private:
    char num[100];  // Идентификационный номер
    char name[100]; // Наименование товара
    double amount;  // Количество единиц
    double price;   // Цена
    int date[3];    // Дата поступления на склад

public:
    Product() : num{ 0 }, name{ 0 }, amount{ 0 }, price{ 0 }, date{ 0 } {}

    void set(char enter = '\n');
    void get();

    char* GetNum();
    char* GetName();
    int* GetDate();
    double GetPrice();
};

