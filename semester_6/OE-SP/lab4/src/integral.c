#include <math.h>

#define DX 0.00001

double compute_integral(double start, double end) {
    double result = 0.0;

    for (double x = start; x < end; x += DX) {
        result += sin(x) * DX;
    }

    return result;
}