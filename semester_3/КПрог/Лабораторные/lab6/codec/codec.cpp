#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{

    char string[100];
    cout << "Source string: ";
    cin.getline(string, 100);
    //strcpy(string, "hello my name is denis\0");

    cout << "Paste before:  ";
    char sfind[20];
    cin.getline(sfind, 20);
    //strcpy(sfind, "hello\0");

    cout << "Pasting word:  ";
    char spaste[20];
    cin.getline(spaste, 20);
    //strcpy(spaste, "isss");

    

    int string_size = strlen(string);
    int sfind_size = strlen(sfind);
    int spaste_size = strlen(spaste);


    int place = 0; // Индекс места, где начинается искомое слово 
    bool found = false;
    
    for (int i = 0; i < string_size - sfind_size + 1; i++) {
        if (i == 0 || string[i - 1] == ' ') {
            if (string[i + sfind_size] == ' ' || string[i + sfind_size] == '\0') {

                if (string[i] == sfind[0]) {

                    int k = 0;
                    for (int j = i; j < i + sfind_size; j++) {
                        if (string[j] != sfind[k++]) {
                            break;
                        }
                    }
                    if (k == sfind_size) {
                        place = i;
                        found = true;
                        break;
                    }
                }


            }
        }
    }

    if (found) {
        //cout << found << " " << place << " " << string[place] << endl;

        int new_string_size = string_size + spaste_size + 1;
        string[new_string_size] = '\0';

        int k = string_size - 1;
        for (int i = new_string_size - 1; i > place; i--) {
            string[i] = string[k--];
        }

        //cout << string_size << " + " << spaste_size << " + 1 = " << new_string_size << "\n";
        //cout << string << "\n";

        k = 0;
        for (int i = place; i < place + spaste_size; i++) {
            string[i] = spaste[k++];
        }
        string[place + spaste_size] = ' ';
    }

    cout << "Result:        ";
    cout << string << "\n";

}

