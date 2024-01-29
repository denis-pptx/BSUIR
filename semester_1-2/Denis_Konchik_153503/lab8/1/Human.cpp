#include "Human.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Abitur {
    string name[3]; // ФИО
    int score[4]; // Аттестат + 3 экзамена
    int sum; // Сумма баллов

    void SetName(string* name) {
        for (int i = 0; i < 3; i++)
            this->name[i] = name[i];
    }

    void SetScore(int* score) {
        this->sum = 0; // Сумма баллов
        for (int i = 0; i < 4; i++) {
            this->score[i] = score[i];
            this->sum += score[i];
        }
    }
};

Abitur* AddHuman(Abitur* Human, int& N) {
    // Добавление структур в массив + их заполнение

    Abitur* NewStruct = new Abitur[N + 1];
    for (int i = 0; i < N; i++)
        NewStruct[i] = Human[i];


    cout << "\nВведите информацию о добавленном абитуриенте:\n";
    FillAbitur(NewStruct, ++N, 1);

    delete[] Human;
    return NewStruct;

}


Abitur* DeleteHuman(Abitur* Human, int& N) {
    // Удаление абитуриента по номеру

    if (N == 0) {
        cout << "\nСписок абитуриентов пуст\n";
        return Human;
    }

    cout << "Номер удаляемого абитуриента: ";
    int num = input();

    if (num > N) {
        cout << "Такого абитуриента нет\n";
        return Human;
    }

    Abitur* NewStruct = new Abitur[N - 1];

    for (int i = 0; i < num - 1; i++)
        NewStruct[i] = Human[i];

    for (int i = num; i < N; i++)
        NewStruct[i - 1] = Human[i];

    delete[] Human;
    N--;

    cout << "Абитуриент #" << num << " удален\n";
    return NewStruct;
}


Abitur* CreateArray(int& N) {
    // Создание динамического массива структур
    Abitur* Human = new Abitur[N];
    return Human;
}


int input(int start) {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;
        // Проверка предыдущего извлечения данных из буфера
        if (cin.fail() || x < start || !(cin.peek() == ' ' || cin.peek() == '\n')) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}

int DigitLen(int n) {
    int len = 0;
    while (n) {
        len++;
        n /= 10;
    }

    return len;
}

void FillAbitur(Abitur* Human, int& N, int add, int stop) {

    if (add == 0) {
        cout << "\nВведите информацию о каждом абитуриенте в формате: \n"
            << "ФИО, кол-во баллов аттестата и по каждому из 3-ех предметов\n\n";
    }

    int from = add == 0 ? 0 : N - 1;
    bool go = true;
    // Заполнение структуры
    int i = 0;
    for (i = from; i < N && go; i++) {
        string name[3]; // ФИО
        int score[4]; // Аттестат + 3 экзамена

        // Имя
        do {
            cin.clear(); cin.ignore(10000, '\n');

            cout << "#" << i + 1 << " (ФИО):" << setw(2) << " ";
            for (int j = 0; j < 3; j++)
                cin >> name[j];
            Human[i].SetName(name);

        } while (!(cin.peek() == '\n'));

        // Баллы
        do {
            cin.clear(); cin.ignore(10000, '\n');

            cout << "Баллы: " << setw(3 + (long long)DigitLen(i + 1)) << " ";
            for (int j = 0; j < 4; j++)
                score[j] = input(0);

            Human[i].SetScore(score);
        } while (!(cin.peek() == '\n'));



        cout << "Сумма: " << setw(3 + (long long)DigitLen(i + 1)) << " " << Human[i].sum << "\n\n";

        if (stop != -1 && Human[i].sum >= stop) {
            cout << "Ввод остановлен, встречена заданная сумма баллов\n";
            N = i + 1;
            break;
        }

        // Продолжение ввода
        if (i != N - 1) {
            do {
                cout << "Продолжить ввод? (Да / Нет): ";
                string decision;
                cin >> decision;

                if (cin.peek() != '\n') {
                    cin.ignore(10000, '\n');
                    continue;
                }

                if (decision == "Нет") {
                    N = i + 1;
                    go = false;
                    break;
                }
                else if (decision == "Да") {
                    break;
                }
            } while (true);
        }
    }
}

double CountAverage(Abitur* Human, int& N) {
    // Подсчет среднего балла по университету

    double sum = 0; // Сумма всех баллов

    for (int i = 0; i < N; i++)
        sum += Human[i].sum;

    return sum / N;
}

void ChoiceSort(Abitur* Human, int& N) {
    // Сортировка выбором по возрастанию балла

    if (N == 0) {
        cout << "\nСписок абитуриентов пуст\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        int min = i;
        for (int j = min + 1; j < N; j++)
            if (Human[j].sum < Human[min].sum)
                min = j;

        if (min != i) {
            Abitur temp = Human[i];
            Human[i] = Human[min];
            Human[min] = temp;
        }
    }

    cout << "\nСтуденты по возрастанию баллов отсортированы\n";
}

void PrintAbitur(Abitur* Human, int& N, double mid, int set) {

    if (N == 0) {
        cout << "\nСписок абитуриентов пуст\n";
        return;
    }
    if (mid == -1 && set == -1) {
        cout << "\nСписок всех абитуриентов:";
    }
    else if (mid != -1 && set == -1) {
        cout << "\nСредний балл по университету: " << mid;
        cout << "\nСтуденты с баллом выше, чем средний:";
    }
    else if (mid == -1 && set != -1) {
        cout << "\nСтуденты с баллом: " << set;
    }


    // Вывод абитуриентов
    //int numeration = 0;
    for (int i = 0; i < N; i++) {

        if (set == -1 && Human[i].sum > mid || set != -1 && Human[i].sum == set) {

            // Имя
            cout << "\n#" << i + 1 << " (ФИО):" << setw(2) << " ";
            for (int j = 0; j < 3; j++)
                cout << Human[i].name[j] << " ";

            // Баллы
            cout << "\nБаллы: " << setw(3 + (long long)DigitLen(i + 1)) << " ";
            for (int j = 0; j < 4; j++)
                cout << Human[i].score[j] << " ";

            cout << "\nСумма: " << setw(3 + (long long)DigitLen(i + 1)) << " " << Human[i].sum;
        }
        cout << "\n";
    }
}

void EditHuman(Abitur* Human, int& N) {

    if (N == 0) {
        cout << "\nСписок абитуриентов пуст\n";
        return;
    }

    // Изменение абитуриента

    cout << "Номер изменяемого абитуриента: ";
    int num = input();
    if (num > N) {
        cout << "Такого абитуриента нет\n";
        return;
    }

    cout << "Изменить: 1 - имя, 2 - баллы: ";
    int what = input();
    if (!(what == 1 || what == 2)) {
        cout << "Неизвестная команда\n";
        return;
    }


    if (what == 1) {
        // Имя
        do {
            string name[3]; // ФИО
            cin.clear(); cin.ignore(10000, '\n');

            cout << "ФИО: ";
            for (int j = 0; j < 3; j++)
                cin >> name[j];

            Human[num - 1].SetName(name);
        } while (!(cin.peek() == '\n'));
  
    }
    else if (what == 2) {
        // Баллы
        do {
            int score[4]; // Аттестат + 3 экзамена
            cin.clear(); cin.ignore(10000, '\n');

            cout << "Баллы: ";
            for (int j = 0; j < 4; j++)
                score[j] = input(0);

            Human[num - 1].SetScore(score);
        } while (!(cin.peek() == '\n'));
    }

    cout << "Абитуриент #" << num << " изменен\n";

}

void CMD() {
    cout << "\nКоманды: \n";
    cout << "cmd - все команды\n";
    cout << "cls - очистить консоль\n";
    cout << "exit - завершить\n";
    cout << "print - вывести список абитуриентов\n";
    cout << "printav - у кого бал выше среднего\n";
    cout << "printset - вывод абитуриентов с установленным баллом\n";
    cout << "sort - отсортировать по возрастанию суммы баллов\n";
    cout << "add - добавить абитуриента в список\n";
    cout << "delete - удаление абитуриента\n";
    cout << "edit - изменение абитуриента\n";
}