#include "headers.h"

double eps = 0.0000000001;
void type1(Matrix<double> A) {

    double methodIsUseful = true;

    for (int k = 0; k < A.getRows() - 1; k++) {

        for (int i = 1 + k; i < A.getRows() && methodIsUseful; i++) {

            if (abs(A.at(k, k)) < eps)
                methodIsUseful = false;

            double q = A.at(i, k) / A.at(k, k);

            for (int j = k; j < A.getColumns(); j++)
                A.at(i, j) -= A.at(k, j) * q;
        }
    }

    string methodName = "Схема единственного деления";
    if (methodIsUseful) {
        A.print(methodName);

        vector<double> roots(A.getRows());

        for (int k = A.getRows() - 1; k >= 0; k--) {

            double difference = A.at(k, A.getColumns() - 1);

            for (int i = A.getRows() - 1; i > k; i--)
                difference -= A.at(k, i) * roots[i];

            roots[k] = difference / A.at(k, k);
        }

        print_roots(roots, "Корни");
    }
    else {
        cout << methodName << "\n";
        cout << "Данный метод не применим для матрицы с данными коэффициентами\n";
    }
}