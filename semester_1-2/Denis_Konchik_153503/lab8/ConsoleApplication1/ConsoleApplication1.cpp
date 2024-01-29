
#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	int n, i;
	double a;
	FILE* f; //описываем файловую переменную
	//создаем двоичный файл в режиме записи

	fopen_s(&f, "D:\\noobs.dat", "wb");

	//ввод числа n
	cout << "n = "; cin >> n;
	fwrite(&n, sizeof(int), 1, f);
	//цикл для ввода n вещественных чисел
	for (i = 0; i < n; i++)
	{
		//ввод очередного вещественного числа
		cout << "a = ";
		cin >> a;
		//запись вешественного числа в двоичный файл
		fwrite(&a, sizeof(double), 1, f);
	}
	//закрываем файл
	fclose(f);
	system("pause");
	return 0;
}