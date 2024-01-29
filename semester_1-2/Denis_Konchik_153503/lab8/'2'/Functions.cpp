#include "Functions.h"
#include "Product.h"
#include "FileWrite.h"
#include <string>
#include <iostream>
using namespace std;

int AllMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
extern int N;


bool IsEmpty() {
    if (N == 0) {
        cout << "\nСписок товаров пуст\n\n";
        return true;
    }
    return false;
}

void PrintItem(Product* Item) {
    if (IsEmpty()) return;

    cout << "\nСписок всех товаров: ";
    for (int i = 0; i < N; i++) {
        Item[i].get();
        cout << "\n";
    }

    cout << "\n";

}


Product* AddItem(Product* Item) {
    Product* NewArr = new Product[++N];
    for (int i = 0; i < N - 1; i++)
        NewArr[i] = Item[i];

    delete[] Item;

    NewArr[N - 1].set();

    
    WriteAddEdit(NewArr, N);
    return NewArr;
}


int IndexByNum(Product* Item, char* num) {

    int IndexOfNum = -1; // Индекс

    for (int i = 0; i < N; i++)
        if (!strcmp(Item[i].GetNum(), num))
            IndexOfNum = i;

    return IndexOfNum;
}

void EditItem(Product* Item) {
    if (IsEmpty()) return;

    cout << "\nНомер изменяемого товара: ";
    char edit[100]; strget(edit); // Номер

    // Индекс изменяемого элемента
    int IndexOfEdit = IndexByNum(Item, edit);

    if (IndexOfEdit != -1)
        Item[IndexOfEdit].set('\0');
    else
        cout << "Такого работника нет\n\n";

    WriteAddEdit(Item, IndexOfEdit + 1);
}

Product* DelItem(Product* Item) {
    if (IsEmpty()) return Item;

    cout << "\nНомер удаляемого товара: ";
    char del[100]; strget(del); // Табельный номер

    // Индекс удаляемого элемента
    int IndexOfDel = IndexByNum(Item, del);

    if (IndexOfDel != -1) {
        Product* NewArr = new Product[N - 1];
        cout << "Товар \"" << Item[IndexOfDel].GetName() << "\" удален из списка\n\n";

        for (int i = 0; i < IndexOfDel; i++)
            NewArr[i] = Item[i];

        for (int i = IndexOfDel + 1; i < N; i++)
            NewArr[i - 1] = Item[i];

        --N;
        WriteDelete(NewArr, IndexOfDel);
        delete[] Item;
        return NewArr;
    }
    else {
        cout << "Такого товара нет\n\n";
        return Item;
    }
}

Product* DelAll(Product* Item) {
    ClearFile();

    delete[] Item;
    Item = 0;
    ClearFile();

    if (N)
        cout << "\nВсе товары удалены\n\n";
    else
        cout << "\nСписок товаров пуст\n\n";

    N = 0;
    return Item;
}

void strget(char* str) {
    if (cin.peek() == '\n')
        cin.ignore(1);

    cin.getline(str, 100);
}

void strget(string& str) {
    if (cin.peek() == '\n')
        cin.ignore(1);

    getline(cin, str);
}

double input(string repeat) {
    double x;
    while (true) {
        cout << repeat; cin >> x;
        if (x >= 0 && cin.good() && cin.peek() == '\n') {
            return x;
        }
        else {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}


void InputDate(int* date, string repeat) {

    string str;
    int a = 0;

    while (a != 3) {
        cout << repeat;
        cin >> str;

        // Если некорректно введена дата
        if (str.length() != 10 || str[2] != '.' || str[5] != '.')
            continue;

        a = sscanf_s(str.c_str(), "%d.%d.%d", &date[0], &date[1], &date[2]);

        // Если не существует такой даты
        if (date[0] <= 0 || date[1] <= 0 || date[2] <= 0 ||
            date[1] > 12 || date[0] > AllMonth[date[1] - 1])
            a = 0;
    }
}




void cmd() {
    cout << "\n\nКоманды:";
    cout << "\nadd - добавить товар";
    cout << "\ndel - удалить товар";
    cout << "\nadel - удалить все товары\n";
    cout << "\nedit - изменить товар";
    cout << "\nprint - список";
    cout << "\nps - вывод по условию";
    cout << "\nnum - число товаров";
    cout << "\n\ncmd - все команды";
    cout << "\ncls - очистить консоль";
    cout << "\nexit - выход";
    cout << "\n\n\n";
}