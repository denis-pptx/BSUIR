//
// pch.cpp
//

#include "pch.h"
int length(char* str) {
	// ����� ������

	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}

unsigned long long Fact(unsigned long long n) {
	// ���������
	if (n <= 1)
		return 1;

	return n * Fact(n - 1);
}

unsigned long long anagram(char* str) {

	if (strlen(str) == 0)
		return 0;

	// ����� ��������
	unsigned long long amount = Fact(length(str));

	// ������ � ����������� ����������
	char* unic = new char[length(str)];
	int u = 0; // �� �����

	unic[u++] = str[0];
	for (int i = u; i < length(str); i++) {
		bool add = true;

		// ���������, ���� �� str[i] � unic
		for (int j = 0; j < u; j++)
			if (unic[j] == str[i])
				add = false;

		if (add)
			unic[u++] = str[i];
	}

	// ������ � ����������� ���������� ������� ����������� ��������
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
		amount /= (unsigned long long int)Fact(unic_rep[i]);

	return amount;
}