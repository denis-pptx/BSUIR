#include "Functions.h"
#include "Human.h"
#include "FileWrite.h"
extern int N;

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


bool IsEmpty() {
    if (N == 0) {
        cout << "\n������ ���������� ����\n\n";
        return true;
    }
    return false;
}

void PrintEmployee(Human* Employee) {
    if (IsEmpty()) return;

    cout << "\n������ ���� ����������: ";
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

    WriteAdd(NewArr);
    return NewArr;
}

int IndexByTabel(Human* Employee, string tabel) {

    int IndexOfTabel = -1; // ������

    for (int i = 0; i < N; i++)
        if (Employee[i].GetTabel() == tabel)
            IndexOfTabel = i;

    return IndexOfTabel;
}

void EditEmployee(Human* Employee) {
    if (IsEmpty()) return;

    cout << "\n��������� ����� ����������� ���������: ";
    string edit; strget(edit); // ��������� �����

    // ������ ����������� ��������
    int IndexOfEdit = IndexByTabel(Employee, edit);

    if (IndexOfEdit != -1)
        Employee[IndexOfEdit].set('\0');
    else
        cout << "������ ��������� ���\n\n";
}

Human* DelEmployee(Human* Employee) {
    if (IsEmpty()) return Employee;

    cout << "\n��������� ����� ���������� ���������: ";
    string del; strget(del); // ��������� �����

    // ������ ���������� ��������
    int IndexOfDel = IndexByTabel(Employee, del);

    if (IndexOfDel != -1) {
        Human* NewArr = new Human[N - 1];
        cout << "�������� " << Employee[IndexOfDel].GetName() << " ������ �� ������\n\n";

        for (int i = 0; i < IndexOfDel; i++)
            NewArr[i] = Employee[i];

        for (int i = IndexOfDel + 1; i < N; i++)
            NewArr[i - 1] = Employee[i];

        --N;
        delete[] Employee;
        return NewArr;
    }
    else {
        cout << "������ ��������� ���\n\n";
        return Employee;
    }
}

Human* DelAll(Human* Employee) {
    delete[] Employee;
    N = 0; Employee = 0;

    cout << "\n��� ��������� �������\n\n";

    return Employee;
}

void cmd() {
    cout << "\n�������:";
    cout << "\ncmd - ��� �������";
    cout << "\ncls - �������� �������";
    cout << "\nadd - �������� ���������";
    cout << "\ndel - ������� ���������";
    cout << "\nadel - ������� ����";
    cout << "\nedit - �������� ���������";
    cout << "\nprint - ������ ����";
    cout << "\nnum - ����� ����";
    cout << "\nexit - �����";
    cout << "\n\n";
}