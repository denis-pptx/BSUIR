#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "headers.h"
using namespace std;
  
int k = 11;
double precision = 1e-4;

int main()
{
    setlocale(LC_ALL, "Ru");

    Matrix<double> test(create_Tet(), 3, 3);
    cout << test.rank();
    return 0;

    Matrix<double> C(create_C(), 5, 5);
    Matrix<double> D(create_D(), 5, 5);
    
    Matrix<double> A = k * C + D;
    vector<double> d = { 1.2, 2.2, 4.0, 0, -1.2 };
    Matrix<double> A_advanced = A + d;

    A.print("Исходная матрица");
    A_advanced.print("Расширенная матрица");

    if (A.rank() != A_advanced.rank() || A.rank() < A.getRows())
        cout << "\nРанг исходной матрицы: " << A.rank() <<
            "\nРанг расширенной матрицы: " << A_advanced.rank() << "\n";

    if (A.rank() != A_advanced.rank()) {

        cout << "\nРанг исходной матрицы не равен рангу расширенной матрицы." <<
            "\nСЛАУ не имеет решений.";
    }
    else if (A.rank() < A.getRows()) {
        cout << "\nРанги матриц равны и меньше числа неизвестных системы." <<
            "\nСЛАУ имеет бесконечно много решений.\n";
    }
    else if (!A.isDiagonalDominance()) {
        cout << "\nИсходная матрица не обладает свойством диагонального преобладания.\n"
            << "Решение методом [простых итераций / Зейделя] невозможно.\n";
    }
    else {
        int iterations = 0;
        vector<double> roots = simpleIterations(A_advanced, iterations);
        print_roots(roots, "Корни (метод простых итераций):");
        cout << "Количество итераций: " << iterations << "\n";
        //check_roots(A, roots, "Проверка. \nb1..b5 при подстановке корней:");

        iterations = 0;
        roots = seidelMethod(A_advanced, iterations);
        print_roots(roots, "Корни (метод Зейделя):");
        cout << "Количество итераций: " << iterations << "\n";
        //check_roots(A, roots, "Проверка. \nb1..b5 при подстановке корней:");
    }


}




