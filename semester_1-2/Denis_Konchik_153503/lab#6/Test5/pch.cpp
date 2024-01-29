//
// pch.cpp
//

#include "pch.h"

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