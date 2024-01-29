#include "FileWrite.h"
#include "Product.h"
#include "Functions.h"
#include "io.h"
#include <iostream>
using namespace std;


char storage[] = "storage.bin";
extern int N;

void CheckOpen() {
    // Проверка на открытие файла

    FILE* f;
    fopen_s(&f, storage, "rb+");
    if (f == NULL)
        cout << "BAD OPEN FILE\n";
    else
        fclose(f);
}

Product* LoadFromFile(Product* Item) {
    // Загрузка файла

    Product* Load = 0; // Массив
    FILE* f;
    fopen_s(&f, storage, "rb+");

    Product Parse;

    while (fread((char*)&Parse, sizeof(Product), 1, f)) {
        Load = (Product*)realloc(Load, ++N * sizeof(Product));
        Load[N - 1] = Parse;
    }

    if (N > 0)
        cout << "\nТоваров загружено: " << N;
    else
        cout << "\nФайл товаров пуст";

    fclose(f);
    free(Item);

    return Load;

}

void ClearFile() {
    // Очистка файла

    FILE* f;
    fopen_s(&f, storage, "wb");
    fclose(f);
}

void WriteAddEdit(Product* Item, int num) {
    // Добавление в какое-то место

    FILE* f;
    fopen_s(&f, storage, "rb+");

    fseek(f, (num - 1) * (int)sizeof(Product), 0);
    fwrite((char*)&Item[num - 1], sizeof(Product), 1, f);

    fclose(f);
}

void WriteDelete(Product* Item, int index) {
    // Смещение в файле, перезапись на удаленный

    if (index == 0 && N == 0) ClearFile();

    FILE* f;
    fopen_s(&f, storage, "rb+");

    for (int i = index; i < N + 2; i++) {
        fseek(f, index * (int)sizeof(Product), 0);
        fwrite((char*)&Item[index], sizeof(Product), 1, f);
    }

    fseek(f, 0, 0);

    // Обрезаем лишнее
    _chsize(_fileno(f), sizeof(Product) * N);

    fclose(f);


}

//void PrintFile() {
//
//    FILE* f;
//    fopen_s(&f, storage, "rb+");
//
//    Product Parse;
//
//    bool empty = true;
//    while (fread((char*)&Parse, sizeof(Product), 1, f)) {
//        empty = false;
//        Parse.get();
//
//        cout << "\n\n";
//    }
//
//    if (empty)
//        cout << "\nФайл пуст\n\n";
//
//    fclose(f);
//}