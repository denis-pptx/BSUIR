// Лабораторная 6, задача 3. Выполнена: Кончик Д. С.

/*
[Вариант 14]
Ввести строки символов. Среди литер этого текста особую роль играет знак #, 
появление которого означает отмену предыдущей литеры текста; 
k знаков # отменяют k предыдущих литер (если такие есть).
Преобразовать строку с учетом роли знака #. Например, строка «VR##Y#HELO#LO» должна быть напечатана в виде: «HELLO».
Результирующую строку вывести на экран.
Стандартных функций работы со строками не использовать.
*/

#include <iostream>
using namespace std;

int length(char*);
void cut(char*, int);
void FindGrid(char*);

int main()
{
    
    cout << "Enter strings and separate them with 'Enter'";
    cout << "\nTo end press 'Enter' twice\n\n";

    // Ввод данных
    int MaxLength = 100, n = 0;
    char** string = new char* [n + 1]; // Массив со строками

    while (true) {
        string[n] = new char[MaxLength];
        cin.getline(string[n], MaxLength);


        if (!string[n][0])
            break;

        // Работа со строкой
        FindGrid(string[n]);

        string = (char**)realloc(string, (++n + 1) * sizeof(char*));
    }

    // Вывод
    cout << "\nConverted: \n";
    for (int i = 0; i < n; i++) {
        cout << string[i] << "\n";
    }
    

    return 0;
}


int length(char* str) {
    // Длина строки

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}

void cut(char* str, int pos) {

    
    // В temp закидываем все символы str без #
    char* temp = new char[length(str)];
    int t = 0;

    for (int i = 0; i < pos - 1; i++)
        temp[t++] = str[i];

    for (int i = pos + 1; i < length(str); i++)
        temp[t++] = str[i];

    temp[t] = '\0';

  

    // Копируем temp в str
    for (int i = 0; i < length(temp); i++)
        str[i] = temp[i];

    str[length(temp)] = '\0';

    delete[] temp;
}

void FindGrid(char* str) {

    // Постоянно ищем #
    // Находим - отправляем в cut

    bool repeat = true;
    while (repeat) {

        repeat = false;
        int i = 0;

        while (i < length(str)) {

            if (str[i] == '#') {
                cut(str, i);
                break;
            }

            i++;
        }

        for (int j = 0; j < length(str) && !repeat; j++) {
            if (str[j] == '#')
                repeat = true;
        }
    }
}