#include "Product.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


int AllMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
string storage = "storage.txt";
string result = "result.txt";


struct Product {
    char name[100]; // ������������ ������
    int amount;     // ���������� ������
    double price;   // ����
    int date[3];    // ���� ����������� �� �����

    int index; // ����� � �������
};


void WriteInFile(Product* Item, int& N, string file, int one) {
    // ������ � ���� ���������
    fstream st;
    st.open(file, fstream::out | fstream::app);

    if (!st.is_open())
        cout << "BAD OPEN";

    if (file == storage)
        st.write((char*)&Item[N-1], sizeof(Product));
    else {
        for (int i = 0; i < N; i++)
            st.write((char*)&Item[i], sizeof(Product));
    }


    st.close();
}


void FillItem(Product* Item, int& N, int edit) {
    // ���������� ���������

    if (!edit)
        cout << "\n�����: " << N << "\n";

    cout << "������������: ";
    cin.ignore(10, '\n'); cin.getline(Item[N - 1].name, 100);

    cout << "����� ������: ";
    Item[N - 1].amount = input_int(1);

    cout << "���� �������: ";
    Item[N - 1].price = input_double(0);

    // ���� �����������
    ParseDate(Item[N - 1].date);

    WriteInFile(Item, N, storage, 1);
}

void EditItem(Product* Item, int& N) {
    // ��������� ��������� �� ������

    if (N == 0) {
        cout << "\n������ ������� ����\n"; return;
    }

    cout << "\n����� ����������� ������: ";
    int num = input_int(1);
    if (num > N) {
        cout << "������ ������ ���\n";
        return;
    }

    FillItem(Item, num, 1);
}

void PrintItem(Product Item, int i, int sort) {
    cout << "\n�����: ";
    if (sort)
        cout << Item.index + 1;
    else
        cout << i + 1;

    cout << "\n������������: ";
    cout << Item.name;

    cout << "\n����� ������: ";
    cout << Item.amount;

    cout << "\n���� �������: ";
    cout << setprecision(2) << fixed << Item.price;

    cout << "\n���� �����������: ";
    for (int j = 0; j < 3; j++) {
        cout << Item.date[j];
        if (j != 2) cout << ".";
    }

    cout << "\n";
}



void PrintAll(Product* Item, int& N) {
    // ����� ���� ��������

    if (N == 0) {
        cout << "\n������ ������� ����\n";
        return;
    }

    for (int i = 0; i < N; i++)
        PrintItem(Item[i], i);
}

bool AlphabetCompare(char* str1, char* str2) {
    // true - str1 ������, ��� str2 � ���������� �������

    int l1 = strlen(str1), l2 = strlen(str2);
    int max = l1 > l2 ? l1 : l2;

    for (int i = 0; i < max; i++) {
        if (str1[i] == str2[i])
            continue;
        return str1[i] > str2[i] ? false : true;
    }
}

bool CheckItem(Product Item, int* Date) {
    int ItemDate = Item.date[0] + Item.date[1] * AllMonth[Item.date[1] - 1] + Item.date[2] * 365;
    int CurrentDate = Date[0] + Date[1] * AllMonth[Date[1] - 1] + Date[2] * 365;

    if (CurrentDate - ItemDate > 30 && Item.price > 1000)
        return true;
    else
        return false;
}

void PrintSort(Product* Item, int& N) {
    // ����� �� ������� ������

    if (N == 0) {
        cout << "\n������ ������� ����\n";
        return;
    }

    cout << "\n������� ������� ����: \n";
    int CurrentDate[3]; ParseDate(CurrentDate);

    int num = 0; // ����� ���������� �������

    for (int i = 0; i < N; i++)
        Item[i].index = i;

    // ������, ��������������� � ���������� ������� �� �����
    Product* SortItem = (Product*)calloc(N, sizeof(Product));
    for (int i = 0; i < N; i++) {
        SortItem[i] = Item[i];
        if (CheckItem(Item[i], CurrentDate))
            num++;
    }

    if (num == 0) {
        cout << "����� ������� ���\n";
    }
    else {
        for (int i = 0; i < N; i++) {
            for (int j = N - 1; j > i; j--) {
                if (AlphabetCompare(SortItem[j].name, SortItem[j - 1].name)) {
                    Product temp = SortItem[j];
                    SortItem[j] = SortItem[j - 1];
                    SortItem[j - 1] = temp;
                }
            }
        }

        // ��������������� �� �����
        Product* OutputItem = (Product*)calloc(num, sizeof(Product));
        int oi = 0;

        for (int i = 0; i < N; i++) {
            if (CheckItem(SortItem[i], CurrentDate)) {
                PrintItem(SortItem[i], i, 1);
                OutputItem[oi++] = SortItem[i];
            }
        }

        // ������ � ����
        WriteInFile(OutputItem, num, result, 0);

        free(OutputItem);
        free(SortItem);
    }
}

Product* AddItem(Product* Item, int& N) {
    // ���������� ��������� � ������ + � ����������

    Product* NewItem = (Product*)calloc(++N, sizeof(Product));
    for (int i = 0; i < N - 1; i++)
        NewItem[i] = Item[i];

    FillItem(NewItem, N);

    free(Item);
    return NewItem;
}


Product* DeleteItem(Product* Item, int& N) {
    // �������� ������ �� ������

    if (N == 0) {
        cout << "\n������ ������� ����\n"; return Item;
    }

    cout << "\n����� ���������� ������: ";
    int num = input_int(1);

    if (num > N) {
        cout << "������ ������ ���\n";
        return Item;
    }

    Product* NewItem = (Product*)calloc(N - 1, sizeof(Product));

    for (int i = 0; i < num - 1; i++)
        NewItem[i] = Item[i];

    for (int i = num; i < N; i++)
        NewItem[i - 1] = Item[i];

    free(Item);
    --N;

    cout << "����� #" << num << " ������\n";
    return NewItem;
}


void ParseDate(int* date) {

    string str;
    int a = 0;

    while (a != 3) {
        cout << "����: ";
        cin >> str;

        // ���� ����������� ������� ����
        if (str.length() != 10 || str[2] != '.' || str[5] != '.')
            continue;

        a = sscanf_s(str.c_str(), "%d.%d.%d", &date[0], &date[1], &date[2]);

        // ���� �� ���������� ����� ����
        if (date[0] <= 0 || date[1] <= 0 || date[2] <= 0 ||
            date[1] > 12 || date[0] > AllMonth[date[1] - 1])
            a = 0;
    }
}

int input_int(int start) {
    int x;

    // ���� �� ����� ������� ���������� ��������
    while (true) {
        cin >> x;
        // �������� ����������� ���������� ������ �� ������
        if (cin.fail() || x < start || !(cin.peek() == ' ' || cin.peek() == '\n')) {
            cin.clear(); // ����������� � ������� ����� ������
            cin.ignore(10000, '\n'); // ����� 'n' �������� �� Enter
            cout << "��������� ����: ";
        }
        else {
            return x;
        }
    }
}

double input_double(double start) {
    double x;

    // ���� �� ����� ������� ���������� ��������
    while (true) {
        cin >> x;
        // �������� ����������� ���������� ������ �� ������
        if (cin.fail() || x < start || !(cin.peek() == ' ' || cin.peek() == '\n')) {
            cin.clear(); // ����������� � ������� ����� ������
            cin.ignore(10000, '\n'); // ����� 'n' �������� �� Enter
            cout << "��������� ����: ";
        }
        else {
            return x;
        }
    }
}

void CMD() {
    cout << "\n�������:";
    cout << "\ncmd - ��� �������";
    cout << "\ncls - �������� �������";
    cout << "\nadd - �������� �����";
    cout << "\nedit - �������� �����";
    cout << "\ndelete - ������� �����";
    cout << "\nprint - ��� ������";
    cout << "\nprints - �������� ������ ������, \n������ 1000p, ���������� �������";
    cout << "\nexit - ���������\n";
}