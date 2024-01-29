// Лабораторная 6, задача 5. Выполнена: Кончик Д. С.

/*
Во многих прикладных задачах, таких как поиск в сети или расшифровка генома, требуется совершать некоторые действия со строками. 
Например, часто требуется по некоторым данным о строке восстановить ее саму.
Вам даны две строки S1 и S2. Известно, что одна из них была суффиксом искомой строки S, а другая — ее префиксом. 
Также известна длина искомой строки L, а также то, что строка S состояла только из строчных букв латинского алфавита.
Необходимо определить число строк, удовлетворяющих этим ограничениям. Так как это число может быть достаточно большим, 
то необходимо вывести его по модулю m.

[Входные данные]
Первая строка содержит одно целое число t (1 ≤ t ≤ 100) — количество наборов входных данных, которые необходимо обработать.
Описание каждого из наборов входных данных содержит три строки. 
Первая из них содержит два целых числа: L и m (1 ≤ L ≤ 109, 1 ≤ m ≤ 104). 
Вторая и третья строки содержат соответственно строки S1 и S2. Они непусты, состоят из строчных букв латинского алфавита, 
их длины не превышают 200 символов.

[Выходные данные]
Для каждого набора входных данных выведите в отдельной строке остаток от деления числа строк, удовлетворяющих требованиям 
условия, на m.

[Входные данные]				[Выходные данные]
3								752 							
14 1000							0
cup russia						1
7 123
russian codecup
7 15
codec decup
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


int FuncVar(int L, int M, char* S1, char* S2);

int main()
{
	const int MAX_STR = 200;

	int L, M;
	char S1[MAX_STR], S2[MAX_STR]; 

	int t; cin >> t;
	int* arr = new int[t];

	for (int i = 0; i < t; i++) {
		cin >> L >> M >> S1 >> S2;

		
		arr[i] = FuncVar(L, M, S1, S2);	
	}
	
	cout << endl;
	for (int i = 0; i < t; i++) {
		cout << arr[i] << endl;
	}

	return 0;
}




int FuncVar(int L, int M, char* S1, char* S2) {
	if (L == 0)
		return 0;

	// Всего вариантов строк
	unsigned long long variants = 0;

	// Всего пустых мест в слове
	int spaces = L - (strlen(S1) + strlen(S2));
	if (spaces > 0) {
		// *2 - поменять префикс и суффикс местами
		variants += pow(26, spaces) * 2;
	}
	else if (spaces == 0) {
		variants += 2;
	}
	else {

		// Наложение строк

		int NeedOverlay = strlen(S1) + strlen(S2) - L;

		if (NeedOverlay > 0) {
			int i = strlen(S1) - NeedOverlay, j = 0;
			bool Overlay = true;
			while (i < strlen(S1) && j < strlen(S2))
				if (S1[i++] != S2[j++]) {
					Overlay = false;
					break;
				}

			if (Overlay && S1[strlen(S1) - 1] == S2[j - 1])
				variants++;


			i = strlen(S2) - NeedOverlay, j = 0;
			Overlay = true;
			while (i < strlen(S2) && j < strlen(S1))
				if (S2[i++] != S1[j++]) {
					Overlay = false;
					break;
				}


			if (Overlay && S2[strlen(S2) - 1] == S1[j - 1])
				variants++;


		}
	}



	return variants % M;
}