//
// pch.cpp
//

#include "pch.h"
#include <cstring>
using namespace std;

void RomanDigit(int i, int rank, int* digit, string& add, string* symb) {
	// ������ � ������� �����

	if (digit[i] == rank) {
		add = symb[i];
	}
	else if (2 * digit[i] == rank) {
		add = symb[i] + symb[i];
	}
	else if (3 * digit[i] == rank) {
		add = symb[i] + symb[i] + symb[i];
	}
	else if (digit[i] + digit[i - 1] == rank) {
		add = symb[i] + symb[i - 1];
	}
	else if (digit[i] + 2 * digit[i - 1] == rank) {
		add = symb[i] + symb[i - 1] + symb[i - 1];
	}
	else if (digit[i] + 3 * digit[i - 1] == rank) {
		add = symb[i] + symb[i - 1] + symb[i - 1] + symb[i - 1];
	}
	else if (digit[i + 1] - digit[i] == rank) {
		add = symb[i] + symb[i + 1];
	}
	else if (digit[i + 1] - digit[i - 1] == rank) {
		add = symb[i - 1] + symb[i + 1];
	}
}


string ToRoman(int arabic) {
	int digit[] = { 1,    5,  10,  50,  100,  500, 1000 };
	string symb[] = { "I", "V", "X", "L", "C",  "D",  "M" };
	string l = "", r = "", roman, add;


	bool minus = false;
	if (arabic < 0) {
		arabic = -arabic;
		minus = true;
	}

	unsigned long long k = 10;
	while (arabic > 0) {

		l = ""; r = "", add = "";

		int rank = arabic % k; // ������
		arabic -= arabic % k;
		k *= 10;

		int i = 0; // ������� ���� ������ �����
		while (rank >= digit[i] && i < 7)
			i++;

		while (i >= 7) {
			// ������, ��� 1000
			// ����� � ������� - ����� * 1000
			l += "("; r += ")";
			rank /= 1000;
			arabic -= arabic % 1000;

			i = 0;
			while (rank >= digit[i] && i < 7)
				i++;
		}

		if (i != 0 && i < 7) {
			i--;
			RomanDigit(i, rank, digit, add, symb); // � �������

			// �������� ������
			add = l + add + r;

			// �������� ���������� ����� � �����
			roman = add + roman;

		}
	}

	if (minus) roman = '-' + roman;


	// �����: 0
	if (len(roman) == 0)
		roman = "nulla";

	return roman;
}

int len(string str) {
	// ����� ������

	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}
