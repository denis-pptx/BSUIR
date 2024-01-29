#include "FileWrite.h"
#include "Human.h"
#include "io.h"
using namespace std;


char storage[] = "storage.dat";
extern int N;

void CheckOpen() {
    // �������� �� �������� �����
    
    FILE* f;
    fopen_s(&f, storage, "rb+");
    if (f == NULL)
        cout << "BAD OPEN FILE\n";
    else
        fclose(f);
}

Human* LoadFromFile(Human* Employee) {
    // �������� �����

    Human* Load = 0; // ������
    FILE* f;
    fopen_s(&f, storage, "rb+");

    Human Parse;

    bool empty = true;
    while (fread((char*)&Parse, sizeof(Human), 1, f)) {
        empty = false;
        Load = (Human*)realloc(Load, ++N * sizeof(Human));
        Load[N - 1] = Parse;
    }
    
    if (empty)
        cout << "\n���� ����\n\n";
    else
        cout << "\n���������� ���������: " << N << "\n\n";

    fclose(f);

    return Load;
}

void ClearFile() {
    // ������� �����

    FILE* f;
    fopen_s(&f, storage, "wb");
    fclose(f);
}

void WriteAddEdit(Human* Employee, int num) {
    // ���������� � �����-�� �����

    FILE* f; 
    fopen_s(&f, storage, "rb+");

    fseek(f, (num - 1) * (int)sizeof(Human), 0);
    fwrite((char*)&Employee[num - 1], sizeof(Human), 1, f);

    fclose(f);
}

void WriteDelete(Human* Employee, int index) {
    // �������� � �����, ���������� �� ���������

    if (index == 0 && N == 0) ClearFile();

    FILE* f;
    fopen_s(&f, storage, "rb+");

    for (int i = index; i < N + 2; i++) {
        fseek(f, index * (int)sizeof(Human), 0);
        fwrite((char*)&Employee[index], sizeof(Human), 1, f);
    }

    fseek(f, 0, 0);

    // �������� ������
    _chsize(_fileno(f), sizeof(Human) * N);

    fclose(f);
 
    
    
}

void PrintFile() {

    FILE* f;
    fopen_s(&f, storage, "rb+");

    Human Parse;
 
    bool empty = true;
    while (fread((char*)&Parse, sizeof(Human), 1, f)) {
        empty = false;
        Parse.get();

        cout << "\n\n";
    }

    if (empty)
        cout << "\n���� ����\n\n";
    


    fclose(f);
}