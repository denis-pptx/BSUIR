// Лабораторная 6, задача 7. Выполнена: Кончик Д. С.

/*
Задание 7.
В заданной строке S найти максимальную по длине подстроку, которая не является палиндромом.

Формат входных данных:
На вход задается строка S, состоящая из строчных букв латинского алфавита (1 ⩽ |S| ⩽ 105 ).

Формат выходных данных:
Выведите одно целое число — длина максимального непалиндрома.
Если такой подстроки не существует, то выведите -1.

Пример:		
aba
2

*/

#include <iostream>
using namespace std;

int length(char* str);
bool IsPalindrome(char* str);
int MaxStr(char* str);

int main()
{
	const int MAX = 100;
	char str[MAX];

	cout << "Enter string: ";
	cin >> str;

	int ans = MaxStr(str);

	if (ans == -1)
		cout << -1;
	else
		cout << ans;

	return 0;
}

int length(char* str) {
	// Длина строки

	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}

bool IsPalindrome(char* str) {
	int L = length(str);
	for (int i = 0; i < L / 2; i++) {
		if (str[i] != str[L - i - 1])
			return false;
	}
	return true;
}

int MaxStr(char* str) {
	// Длина строки
	int L = length(str);

	// Ответ
	int ans = -1;

	// Сюда помещаем строку и проверяем на палиндром
	char* test = new char[L];

	// Проверяем все возможные комбинации слов
	for (int i = 0; i < L; i++) {
		int t = 0;

		for (int j = i; j < L; j++) {
			test[t] = str[j];
			test[++t] = '\0';

			if (!IsPalindrome(test) && length(test) > ans)
				ans = length(test);
		}
	}

	return ans;
}