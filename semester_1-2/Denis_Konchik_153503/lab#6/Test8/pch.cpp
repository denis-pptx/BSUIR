//
// pch.cpp
//

#include "pch.h"

bool check(char* s, char* t) {

	// ������ ����� �� ������ ������ � ���������
	for (int j = 0; j < length(s); j++) {

		bool Possibly = chip(s, t, j, 0);

		if (Possibly)
			return true;
	}

	return false;
}

int length(char* str) {
	// ����� ������

	int count = 0;
	while (str[count] != '\0')
		count++;

	return count;
}


bool chip(char* s, char* t, int i, int k) {

	

	int rep = 0; // ������� �����������

	if (s[i] == t[k])
		rep++;
	else
		return false;


	if (i < length(s) && k < length(t)) {
		while (i < length(s) - 1 && k < length(t) - 1 && s[i + 1] == t[k + 1]) { // ������
			i++;
			k++;
			rep++;
		}
		while (i > 0 && k < length(t) - 1 && s[i - 1] == t[k + 1]) { // �����
			i--;
			k++;
			rep++;
		}
	}


	if (rep == length(t))
		return true;
	else
		return false;
}