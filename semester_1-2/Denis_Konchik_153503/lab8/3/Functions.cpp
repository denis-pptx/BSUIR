#include "Functions.h"
#include "Human.h"
#include "FileWrite.h"
extern int N;

void strget(string& str) {
    if (cin.peek() == '\n')
        cin.ignore(1);

    getline(cin, str);
}

void strget(char* str) {
    if (cin.peek() == '\n')
        cin.ignore(1);

    cin.getline(str, 100);
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


bool IsEmpty() {
    if (N == 0) {
        cout << "\nСписок работников пуст\n\n";
        return true;
    }
    return false;
}

void PrintEmployee(Human* Employee) {
    if (IsEmpty()) return;

    cout << "\nСписок всех работников: ";
    for (int i = 0; i < N; i++) {
        Employee[i].get();
        cout << "\n";
    }

    cout << "\n";

}


Human* AddEmployee(Human* Employee) {
    Human* NewArr = new Human[++N];
    for (int i = 0; i < N - 1; i++)
        NewArr[i] = Employee[i];

    delete[] Employee;

    NewArr[N - 1].set();

    WriteAddEdit(NewArr, N);
    return NewArr;
}

int IndexByTabel(Human* Employee, char* tabel) {

    int IndexOfTabel = -1; // Индекс

    for (int i = 0; i < N; i++)
        if (!strcmp(Employee[i].GetTabel(), tabel))
            IndexOfTabel = i;

    return IndexOfTabel;
}

void EditEmployee(Human* Employee) {
    if (IsEmpty()) return;

    cout << "\nТабельный номер изменяемого работника: ";
    char edit[100]; strget(edit); // Табельный номер

    // Индекс изменяемого элемента
    int IndexOfEdit = IndexByTabel(Employee, edit);

    if (IndexOfEdit != -1)
        Employee[IndexOfEdit].set('\0');
    else
        cout << "Такого работника нет\n\n";

    WriteAddEdit(Employee, IndexOfEdit + 1);
}

Human* DelEmployee(Human* Employee) {
    if (IsEmpty()) return Employee;

    cout << "\nТабельный номер удаляемого работника: ";
    char del[100]; strget(del); // Табельный номер

    // Индекс удаляемого элемента
    int IndexOfDel = IndexByTabel(Employee, del);

    if (IndexOfDel != -1) {
        Human* NewArr = new Human[N - 1];
        cout << "Работник " << Employee[IndexOfDel].GetName() << " удален из списка\n\n";

        for (int i = 0; i < IndexOfDel; i++)
            NewArr[i] = Employee[i];

        for (int i = IndexOfDel + 1; i < N; i++)
            NewArr[i - 1] = Employee[i];

        --N;
        WriteDelete(NewArr, IndexOfDel);
        delete[] Employee;
        return NewArr;
    }
    else {
        cout << "Такого работника нет\n\n";
        return Employee;
    }
}

Human* DelAll(Human* Employee) {
    ClearFile();

    delete[] Employee;
    N = 0; Employee = 0;
    ClearFile();
    cout << "\nВсе работники удалены\n\n";

    return Employee;
}

void cmd() {
    cout << "\n\nКоманды:";
    cout << "\nadd - добавить работника";
    cout << "\ndel - удалить работника";
    cout << "\nadel - удалить всех работников\nи очистить файл\n";
    cout << "\nedit - изменить работника";
    cout << "\nprint - список всех";
    cout << "\nnum - число всех";
    cout << "\n\nРабота с файлом:";
    cout << "\nprfile - просмотр файла";
    cout << "\nload - загрузить из файла";
    cout << "\n\ncmd - все команды";
    cout << "\ncls - очистить консоль";
    cout << "\nnexit - выход";
    cout << "\n\n\n";
}