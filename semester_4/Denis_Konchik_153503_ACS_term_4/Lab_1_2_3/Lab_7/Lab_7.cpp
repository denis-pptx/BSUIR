#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double a, b, c;

    cout << "Введите коэффициент a: ";
    cin >> a;
    cout << "Введите коэффициент b: ";
    cin >> b;
    cout << "Введите коэффициент c: ";
    cin >> c;

    if (a == 0)
    {
        double r = 0;
        __asm {
            FLD b
            FLD c
            FDIV
            FCHS
            FST r
        }
        std::cout << "Уравнение имеет один корень: " << r << endl;
    }
    else
    {
        double four = 4;
        double D = 0;
        __asm {
            FLD b
            FLD b
            FMUL
            FLD four
            FLD a
            FLD c
            FMUL
            FMUL
            FSUB
            FST D
        }

        if (D < 0)
        {
            std::cout << "Уравнение не имеет действительных корней." << endl;
        }
        else if (fabs(D) < 1e-15)
        {
            double r = 0;
            __asm {
                FLD b
                FCHS
                FLD a
                FLD a
                FADD
                FDIV
                FST r
            }

            std::cout << "Уравнение имеет один корень: " << r << endl;
        }
        else
        {
            double r1 = 0;
            __asm
            {
                FLD b
                FCHS
                FLD D
                FSQRT
                FSUB
                FLD a
                FLD a
                FADD
                FDIV
                FST r1
            }

            double r2 = 0;
            __asm
            {
                FLD b
                FCHS
                FLD D
                FSQRT
                FADD
                FLD a
                FLD a
                FADD
                FDIV
                FSTP r2
            }

            cout << "Уравнение имеет два корня: " << r1 << " и " << r2 << endl;
        }
    }

    return 0;
}
