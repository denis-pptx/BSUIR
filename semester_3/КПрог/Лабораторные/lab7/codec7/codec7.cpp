#include <iostream>
using namespace std;

int input() {
    char strNumber[4];
    cin >> strNumber;

    int number = 0;
    int ten = 1;

    int cx = strlen(strNumber);
    while (cx != 0) {
        int digit = strNumber[cx - 1] - 48;
        number += digit * ten;
        ten *= 10;
        cx--;
    }

    return number;
}
int main()
{
    const int arr_size = 5;
    int arr[arr_size];

    for (int i = 0; i < arr_size; i++)
        arr[i] = input();

    int max_item = 0;
    for (int i = 0; i < arr_size; i++)
        if (arr[i] > max_item)
            max_item = arr[i];
    
    const int max_symb = 30;

    for (int i = 0; i < arr_size; i++) {

        int symbols = max_symb  * arr[i] / max_item;

        for (int j = 0; j < symbols; j++) 
            cout << "#";
        
        cout << " [" << arr[i] << "]:[" << symbols << "]";

        cout << "\n";
    }
}

