#include "Result.h"
#include <iostream>
#include "Functions.h"
using namespace std;

extern int AllMonth[];
extern int N;

bool AlphabetCompare(char* str1, char* str2) {
    // true - str1 первее, чем str2 в алфавитном порядке

    int l1 = strlen(str1), l2 = strlen(str2);
    int max = l1 > l2 ? l1 : l2;

    for (int i = 0; i < max; i++) {
        if (str1[i] == str2[i])
            continue;
        return str1[i] > str2[i] ? false : true;
    }
}

bool CheckItem(Product Item, int* Date) {

    int* prod = Item.GetDate(); // Дата продукта

    int ItemDate = prod[0] + prod[1] * AllMonth[prod[1] - 1] + prod[2] * 365; // Дата продукта в днях
    int CurrentDate = Date[0] + Date[1] * AllMonth[Date[1] - 1] + Date[2] * 365; // Текущая дата в днях

    if (CurrentDate - ItemDate > 30 && Item.GetPrice() > 1000)
        return true;
    else
        return false;
}

void PrintSort(Product* Item) {
    // Вывод по условию задачи

    if (N == 0) {
        cout << "\nСписок товаров пуст\n\n";
        WriteResult(0, 0, true);
        return;
    }

    
    int CurrentDate[3]; 
    cout << "\n"; InputDate(CurrentDate, "Текущая дата: ");

    int num = 0; // Число подходящих товаров


    // Массив, отсортированный в алфавитном порядке по имени
    Product* SortItem = (Product*)calloc(N, sizeof(Product));

    // Заполнение SortTem, подсчет числа подходящих товаров
    for (int i = 0; i < N; i++) {
        SortItem[i] = Item[i];
        if (CheckItem(Item[i], CurrentDate))
            num++;
    }

    if (num == 0) {
        cout << "Таких товаров нет\n\n";
        WriteResult(0, 0, true);
    }
    else {

        // Сортировка
        for (int i = 0; i < N; i++) {
            for (int j = N - 1; j > i; j--) {
                if (AlphabetCompare(SortItem[j].GetName(), SortItem[j - 1].GetName())) {
                    Product temp = SortItem[j];
                    SortItem[j] = SortItem[j - 1];
                    SortItem[j - 1] = temp;
                }
            }
        }

        // Отсортированное на вывод
        Product* OutputItem = (Product*)calloc(num, sizeof(Product));
        int oi = 0;

        // Вывод подходящих товаров
        for (int i = 0; i < N; i++) {
            if (CheckItem(SortItem[i], CurrentDate)) {
                SortItem[i].get();
                cout << "\n";
                OutputItem[oi++] = SortItem[i];
            }
        }

        // Запись в файл результат
        WriteResult(OutputItem, oi);

        cout << "\n";
        free(OutputItem);
        free(SortItem);
    }
}


void WriteResult(Product* OutputItem, int oi, bool clear) {

    FILE* f;
    fopen_s(&f, "result.bin", "wb");
    
    if (!clear) {
        for (int i = 0; i < oi; i++)
            fwrite((char*)&OutputItem[i], sizeof(Product), 1, f);
    }

    fclose(f);
}