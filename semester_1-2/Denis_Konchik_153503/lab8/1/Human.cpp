#include "Human.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

struct Abitur {
    string name[3]; // ���
    int score[4]; // �������� + 3 ��������
    int sum; // ����� ������

    void SetName(string* name) {
        for (int i = 0; i < 3; i++)
            this->name[i] = name[i];
    }

    void SetScore(int* score) {
        this->sum = 0; // ����� ������
        for (int i = 0; i < 4; i++) {
            this->score[i] = score[i];
            this->sum += score[i];
        }
    }
};

Abitur* AddHuman(Abitur* Human, int& N) {
    // ���������� �������� � ������ + �� ����������

    Abitur* NewStruct = new Abitur[N + 1];
    for (int i = 0; i < N; i++)
        NewStruct[i] = Human[i];


    cout << "\n������� ���������� � ����������� �����������:\n";
    FillAbitur(NewStruct, ++N, 1);

    delete[] Human;
    return NewStruct;

}


Abitur* DeleteHuman(Abitur* Human, int& N) {
    // �������� ����������� �� ������

    if (N == 0) {
        cout << "\n������ ������������ ����\n";
        return Human;
    }

    cout << "����� ���������� �����������: ";
    int num = input();

    if (num > N) {
        cout << "������ ����������� ���\n";
        return Human;
    }

    Abitur* NewStruct = new Abitur[N - 1];

    for (int i = 0; i < num - 1; i++)
        NewStruct[i] = Human[i];

    for (int i = num; i < N; i++)
        NewStruct[i - 1] = Human[i];

    delete[] Human;
    N--;

    cout << "���������� #" << num << " ������\n";
    return NewStruct;
}


Abitur* CreateArray(int& N) {
    // �������� ������������� ������� ��������
    Abitur* Human = new Abitur[N];
    return Human;
}


int input(int start) {
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
        cout << "\n������� ���������� � ������ ����������� � �������: \n"
            << "���, ���-�� ������ ��������� � �� ������� �� 3-�� ���������\n\n";
    }

    int from = add == 0 ? 0 : N - 1;
    bool go = true;
    // ���������� ���������
    int i = 0;
    for (i = from; i < N && go; i++) {
        string name[3]; // ���
        int score[4]; // �������� + 3 ��������

        // ���
        do {
            cin.clear(); cin.ignore(10000, '\n');

            cout << "#" << i + 1 << " (���):" << setw(2) << " ";
            for (int j = 0; j < 3; j++)
                cin >> name[j];
            Human[i].SetName(name);

        } while (!(cin.peek() == '\n'));

        // �����
        do {
            cin.clear(); cin.ignore(10000, '\n');

            cout << "�����: " << setw(3 + (long long)DigitLen(i + 1)) << " ";
            for (int j = 0; j < 4; j++)
                score[j] = input(0);

            Human[i].SetScore(score);
        } while (!(cin.peek() == '\n'));



        cout << "�����: " << setw(3 + (long long)DigitLen(i + 1)) << " " << Human[i].sum << "\n\n";

        if (stop != -1 && Human[i].sum >= stop) {
            cout << "���� ����������, ��������� �������� ����� ������\n";
            N = i + 1;
            break;
        }

        // ����������� �����
        if (i != N - 1) {
            do {
                cout << "���������� ����? (�� / ���): ";
                string decision;
                cin >> decision;

                if (cin.peek() != '\n') {
                    cin.ignore(10000, '\n');
                    continue;
                }

                if (decision == "���") {
                    N = i + 1;
                    go = false;
                    break;
                }
                else if (decision == "��") {
                    break;
                }
            } while (true);
        }
    }
}

double CountAverage(Abitur* Human, int& N) {
    // ������� �������� ����� �� ������������

    double sum = 0; // ����� ���� ������

    for (int i = 0; i < N; i++)
        sum += Human[i].sum;

    return sum / N;
}

void ChoiceSort(Abitur* Human, int& N) {
    // ���������� ������� �� ����������� �����

    if (N == 0) {
        cout << "\n������ ������������ ����\n";
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

    cout << "\n�������� �� ����������� ������ �������������\n";
}

void PrintAbitur(Abitur* Human, int& N, double mid, int set) {

    if (N == 0) {
        cout << "\n������ ������������ ����\n";
        return;
    }
    if (mid == -1 && set == -1) {
        cout << "\n������ ���� ������������:";
    }
    else if (mid != -1 && set == -1) {
        cout << "\n������� ���� �� ������������: " << mid;
        cout << "\n�������� � ������ ����, ��� �������:";
    }
    else if (mid == -1 && set != -1) {
        cout << "\n�������� � ������: " << set;
    }


    // ����� ������������
    //int numeration = 0;
    for (int i = 0; i < N; i++) {

        if (set == -1 && Human[i].sum > mid || set != -1 && Human[i].sum == set) {

            // ���
            cout << "\n#" << i + 1 << " (���):" << setw(2) << " ";
            for (int j = 0; j < 3; j++)
                cout << Human[i].name[j] << " ";

            // �����
            cout << "\n�����: " << setw(3 + (long long)DigitLen(i + 1)) << " ";
            for (int j = 0; j < 4; j++)
                cout << Human[i].score[j] << " ";

            cout << "\n�����: " << setw(3 + (long long)DigitLen(i + 1)) << " " << Human[i].sum;
        }
        cout << "\n";
    }
}

void EditHuman(Abitur* Human, int& N) {

    if (N == 0) {
        cout << "\n������ ������������ ����\n";
        return;
    }

    // ��������� �����������

    cout << "����� ����������� �����������: ";
    int num = input();
    if (num > N) {
        cout << "������ ����������� ���\n";
        return;
    }

    cout << "��������: 1 - ���, 2 - �����: ";
    int what = input();
    if (!(what == 1 || what == 2)) {
        cout << "����������� �������\n";
        return;
    }


    if (what == 1) {
        // ���
        do {
            string name[3]; // ���
            cin.clear(); cin.ignore(10000, '\n');

            cout << "���: ";
            for (int j = 0; j < 3; j++)
                cin >> name[j];

            Human[num - 1].SetName(name);
        } while (!(cin.peek() == '\n'));
  
    }
    else if (what == 2) {
        // �����
        do {
            int score[4]; // �������� + 3 ��������
            cin.clear(); cin.ignore(10000, '\n');

            cout << "�����: ";
            for (int j = 0; j < 4; j++)
                score[j] = input(0);

            Human[num - 1].SetScore(score);
        } while (!(cin.peek() == '\n'));
    }

    cout << "���������� #" << num << " �������\n";

}

void CMD() {
    cout << "\n�������: \n";
    cout << "cmd - ��� �������\n";
    cout << "cls - �������� �������\n";
    cout << "exit - ���������\n";
    cout << "print - ������� ������ ������������\n";
    cout << "printav - � ���� ��� ���� ��������\n";
    cout << "printset - ����� ������������ � ������������� ������\n";
    cout << "sort - ������������� �� ����������� ����� ������\n";
    cout << "add - �������� ����������� � ������\n";
    cout << "delete - �������� �����������\n";
    cout << "edit - ��������� �����������\n";
}