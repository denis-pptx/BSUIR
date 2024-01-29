#include "headers.h"


double** create_C() {
    double** C = new double* [5];
    C[0] = new double[5]{ 0.2000, 0, 0.2000, 0, 0 };
    C[1] = new double[5]{ 0, 0.2000, 0, 0.2000, 0 };
    C[2] = new double[5]{ 0.2000, 0, 0.2000, 0, 0.2000 };
    C[3] = new double[5]{ 0, 0.2000, 0, 0.2000, 0 };
    C[4] = new double[5]{ 0, 0, 0.2000, 0, 0.2000 };

    return C;
}

double** create_D() {
    double** D = new double* [5];
    D[0] = new double[5]{ 2.3300, 0.8100, 0.6700, 0.9200, -0.5300 };
    D[1] = new double[5]{ -0.5300, 2.3300, 0.8100, 0.6700, 0.9200 };
    D[2] = new double[5]{ 0.9200, -0.5300, 2.3300, 0.8100, 0.6700 };
    D[3] = new double[5]{ 0.6700, 0.9200, -0.5300, 2.3300, 0.8100 };
    D[4] = new double[5]{ 0.8100, 0.6700, 0.9200, -0.5300, 2.3300 };

    return D;
}

