// Лабораторная 6, задача 4. Выполнена: Кончик Д. С.

/*
1 апреля 20XX года будет проведена реформа английского языка, позволяющая облегчить его освоение иностранцами 
и английскими школьниками. Во-первых, из алфавита уберут четыре буквы C, Q, W и X 
(на клавиатуре компьютера вместо них будут клавиши, вызывающие программы Word, eXcel и другие). 
Вместо 'c' перед буквами 'e', 'i', 'y' нужно будет писать букву 's', а в остальных случаях – букву 'k'. 
Вместо буквы 'q' нужно будет писать букву 'k', вместо сочетания 'qu' – 'kv', вместо 'x' – 'ks', а вместо 'w' – 'v'.
Во-вторых, сочетание букв 'ph' будет записываться как 'f', 'you' и 'oo' – как 'u', 'ee' – как 'i', 'th' – как 'z'. 

Кроме того, все двойные согласные (включая образовавшиеся после замен), вызывающие большие трудности у учащихся, 
станут одинарными, например, apple после реформы нужно писать как aple.
В связи с реформой нужно переработать огромное количество текстов.
Напишите программу,  выполняющую эту работу.

[Входные данные]
Во входном файле содержится текст на английском языке, без переносов слов. 
Длина строк не превышает 100 символов.
[Выходные данные]
В выходной файл вывести тот же текст, но уже соответствующий реформе. 
Если первая буква заменяемого сочетания букв была прописной, то первая буква замены должна быть также прописной. 
Вторая буква в заменах x→ks, qu→kv должна быть всегда строчной.

[Входные данные]
Too swift for Theex, too quick for Gallow
Too strong for young Prince Joseph to follow
[Выходные данные]
Tu svift for Ziks, tu kvik for Galov 
Tu strong for ung Prinse Josef to folov
*/

#include <iostream>
#include "TextEdit.h"
using namespace std;


void Full_Check(char* str) {
    // Поочередный вызов функций
    qu_to_kv(str);
    Check_C_W_Q(str);
    x_to_ks(str);
    ph_you_oo_ee_th(str);
    DeleteConsonants(str);
}

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
        Full_Check(string[n]);
 
        string = (char**)realloc(string, (++n + 1) * sizeof(char*));
    }

    // Вывод
    cout << "\nConverted: \n";
    for (int i = 0; i < n; i++) {
        cout << string[i] << "\n";
    }


    return 0;
}



