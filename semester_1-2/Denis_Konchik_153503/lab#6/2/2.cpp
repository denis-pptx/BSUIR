// Лабораторная 6, задача 2. Выполнена: Кончик Д. С.

/*
[Вариант 14]
Найти наибольшее количество предложений текста, в которых есть одинаковые слова.
Рассматривать строки как указатель типа char.
*/


#include <iostream>
#include <cctype>
using namespace std;

void LowRegister(char*);
bool IsSameWords(char**, int&);

int main()
{

    int TextSymbols = 1000; // Максимальное число символов в тексте
    int MaxLength = 25; // Максимальная длина слова

    char* text = new char[TextSymbols + 1]; // Массив с текстом
    cout << "Enter your text. Words are separated with spaces, sentences with dots.\n";
    cin.getline(text, TextSymbols); // Ввод текста

    int SameWords = 0; // Число предложений с одинаковыми словами

    int i = 0, j = 0, amount = 0, k, num; 
    char** word = 0; // Массив слов в предложении
    char* str = 0; // Будет храниться слово

    while (i < strlen(text) - 1) { // Проход текста

        j = i;
        amount = 0; // Число слов в предложении

        while (true) { // Проход предложения

            if (text[i] == ' ') {
                amount++;
            } else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
                amount++;
                break;
            }

            i++;
        }

        word = new char* [amount]; // Массив слов предложения
        for (int j = 0; j < amount; j++) 
            word[j] = new char[MaxLength + 1];
        
        num = 0; // Номер слова в массиве слов данного предложения
        while (j < i) { // Еще раз проходим предложение
            
            

            str = new char[MaxLength + 1]; // Сюда копируем по слову из предложения
            k = 0; // Индекс символов слова str

          
            while (text[j] != ' ' && text[j] != '.' && text[j] != '!' && text[j] != '?' && 
                text[j] != ',' && text[j] != ';' && text[j] != ':') {                        // (1)

                str[k++] = text[j++];
            } 
            j++;

            if (text[j] == ' ') // Если после слова был один из знаков (1)
                j++; // Скипаем его

            str[k] = '\0';
           
            strcpy(word[num++], str);
            delete[] str;
        }

        // Если есть одинаковые слова
        if (IsSameWords(word, amount))
            SameWords++;
        


        for (int j = 0; j < amount; j++) {
            delete[] word[j];
        } delete[] word;

        i += 2;
    }

    
   
    cout << "Amount of sentences with repetitive words: " << SameWords << "\n";
    
    delete[] text;

    return 0;
}




void LowRegister(char* word) {

    for (int i = 0; i < strlen(word); i++) {
        if (isupper(word[i]))
            word[i] = tolower(word[i]);
    }
}

bool IsSameWords(char** word, int& amount) {

    // Проверка на повторяющиеся слова
    if (amount == 1)
        return false;

    int index = amount - 1; // Максимальный индекс
    for (int i = 0; i < index; i++) {
        for (int j = index; j > i; j--) {

            LowRegister(word[j]);
            LowRegister(word[i]);

            // Сравниваем
            if (!strcmp(word[j], word[i]))
                return true;
        }
    }

    return false;
}
