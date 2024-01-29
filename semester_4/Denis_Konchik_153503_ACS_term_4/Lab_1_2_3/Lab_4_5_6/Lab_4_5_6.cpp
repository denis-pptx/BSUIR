#include <iostream>
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"
using namespace std;


void Operation(void(*operation)(float, float), float a, float b) {
    try {
        operation(a, b);
    }
    catch (string ex) {
        cout << "Error: " << ex << "\n\n";
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    
    float a;
    cout << "a = "; 
    cin >> a;
    
    float b;
    cout << "b = "; 
    cin >> b;

    cout << "\n\n";
    Operation(Addition, a, b);

    cout << "\n\n";
    Operation(Subtraction, a, b);

    cout << "\n\n";
    Operation(Multiplication, a, b);

    cout << "\n\n";
    Operation(Division, a, b);
    
    return 0;
}
