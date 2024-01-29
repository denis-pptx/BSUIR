#include <iostream>
#include <cmath>
#include <Windows.h>
using namespace std;

double PI = acos(-1);

double Y(double x) {
	//return 0.25 * (x * x - PI * PI / 3);

	double result = 0;
	double three = 3;
	double four = 0.25;
	__asm {
		FLD x
		FLD x
		FMUL

		FLD PI
		FLD PI
		FMUL

		FLD three
		FDIV

		FSUB

		FLD four 
		FMUL

		FSTP result
	}

	return result;
}

double S(double x, int n) {
	double sum = 0;

	/*for (int k = 1; k <= n; k++) {
		double item = cos(k * x) / (k * k);

		double fitem = 0;
		double fk = (double)k;
		__asm {
			FLD x
			FLD fk
			FMUL
			FCOS
			FLD fk
			FLD fk
			FMUL
			FDIV
			FST fitem
		}

		if (k % 2 == 0) {
			sum += item;
		}
		else {
			sum -= item;
		}
	}*/
	
	for (int k = 1; k <= n; k++) {
		double item = 0;
		double dk = (double)k;
		__asm {
			FLD x
			FLD dk
			FMUL
			FCOS
			FLD dk
			FLD dk
			FMUL
			FDIV
			FSTP item
		}
		if (k % 2 == 0) {
			_asm {
				FLD sum
				FLD item
				FADD
				FSTP sum
			}
		}
		else {
			_asm {
				FLD sum
				FLD item
				FSUB
				FSTP sum
			}
		}
	}

	return sum;
}

int get_n_from_sub(double x, double eps) {
	int n = 1;

	while (fabs(Y(x) - S(x, n++)) > eps);

	return n;
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double a, b, h, eps;

	cout << "Введите a: ";
	cin >> a;
	cout << "Введите b: ";
	cin >> b;
	cout << "Введите h: ";
	cin >> h;
	cout << "Введите eps: ";
	cin >> eps;

	cout << endl << endl;
	int iter = 1;

	cout << "|------|---|------|------|---|" << endl;
	cout << "| iter | x | S(x) | Y(x) | n |" << endl;
	cout << "|------|---|------|------|---|" << endl;

	for (double x = a; a < b; x += h) {
		int n = get_n_from_sub(x, eps);
		cout << "| " << iter++ << " | " << x << " | " << Y(x) << " | " << S(x, n) << " | " << n << " | " << endl;
	}
	return 0;
}
