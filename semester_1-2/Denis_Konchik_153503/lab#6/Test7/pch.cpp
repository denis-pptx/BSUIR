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

bool IsPalindrome(char* str) {
	int L = length(str);
	for (int i = 0; i < L / 2; i++) {
		if (str[i] != str[L - i - 1])
			return false;
	}
	return true;
}

int MaxStr(char* str) {
	// ����� ������
	int L = length(str);

	// �����
	int ans = -1;

	// ���� �������� ������ � ��������� �� ���������
	char* test = new char[L];

	// ��������� ��� ��������� ���������� ����
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