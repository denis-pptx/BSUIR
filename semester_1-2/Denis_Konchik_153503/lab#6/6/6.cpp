// Лабораторная 6, задача 6. Выполнена: Кончик Д. С.

/*
Анаграммой слова называется любая перестановка всех букв слова.
Например, из слова SOLO можно получить 12 анаграмм: SOLO, LOSO,
OSLO, OLSO, OSOL, OLOS, SLOO, LSOO, OOLS,  OOSL, LOOS, SOOL.

Напишите программу, которая выводит количество различных анаграмм, 
которые могут получиться из этого слова.

[Входные данные]
Слово, количество букв в котором не превышает 14.

[Выходные данные]
Количество различных анаграмм.

[Входные данные #1]					[Выходные данные #1]
SOLO								12

*/

#include <iostream>
#define ll unsigned long long int
using namespace std;


// Число анаграмм - факториал количества символов
// делить на факториал повторений каждого уникального символа

int length(char* str);
ll Fact(ll n);
int anagram(char* str);

int main()
{
	const int MAX = 100;
	char str[MAX];

	cout << "Enter word: ";
	cin >> str;

	int amount = anagram(str);

	cout << "Amount of anagrams: " << amount << "\n";
	
	return 0;
}


int length(char* str) {
	// Длина строки

	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}

ll Fact(ll n) {
	// Факториал
	if (n <= 1)
		return 1;

	return n * Fact(n - 1);
}

int anagram(char* str) {
	if (strlen(str) == 0)
		return 0;

	// Число анаграмм
	ll amount = Fact(length(str));

	// Массив с уникальными элементами
	char* unic = new char[length(str)];
	int u = 0; // их число

	unic[u++] = str[0];
	for (int i = u; i < length(str); i++) {
		bool add = true;

		// Проверяем, есть ли str[i] в unic
		for (int j = 0; j < u; j++)
			if (unic[j] == str[i])
				add = false;

		if (add)
			unic[u++] = str[i];
	}

	// Массив с количеством повторений каждого уникального элемента
	int* unic_rep = new int[u];
	for (int i = 0; i < u; i++)
		unic_rep[i] = 0;

	for (int i = 0; i < u; i++) {
		for (int j = 0; j < length(str); j++) {

			if (str[j] == unic[i])
				unic_rep[i]++;

		}
	}


	for (int i = 0; i < u; i++)
		amount /= Fact(unic_rep[i]);

	return amount;
}