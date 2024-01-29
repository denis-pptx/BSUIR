#include <iostream>
#include <cstring>
using namespace std;

string ToTernaryStr(int n) {
    // Перевод из int в string троичную систему

    string ternary = "";
    while (n) {
        ternary.insert(ternary.begin(), (n % 3) + '0');
        n /= 3;
    }

    return ternary;
}
int main()
{
    int n; cin >> n;

    // Перевод в троичную систему
    string ternary = ToTernaryStr(n);


    // Если бит 0, то забираем на него
    // единицу у более старшего бита

    int P = ternary.find("10");
    while (P != -1) {
        ternary.replace(P, 2, "03");
        P = ternary.find("10");
    }
 
    P = ternary.find("20");
    while (P != -1) {
        ternary.replace(P, 2, "13");
        P = ternary.find("20");
    }
    
    P = ternary.find("30");
    while (P != -1) {
        ternary.replace(P, 2, "23");
        P = ternary.find("30");
    }
   
    while (ternary.length() > 1 && ternary.front() == '0')
        ternary.erase(ternary.begin());

    if (ternary.size() == 0)
        ternary = "0";

    cout << ternary;

    return 0;
}