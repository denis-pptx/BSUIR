#if !defined(TEXTEDIT_H)
#define TEXTEDIT_H

#include <iostream> // ��� isalpha

int length(char* str) {
    // ����� ������

    int count = 0;
    while (str[count] != '\0')
        count++;

    return count;
}



void Check_C_W_Q(char* str) {
    int i = 0;
    while (str[i] != '\0') {

        if (str[i] == 'c') {

            if (str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'y')
                str[i] = 's';
            else
                str[i] = 'k';
        }
        else if (str[i] == 'C') {

            if (str[i + 1] == 'e' || str[i + 1] == 'i' || str[i + 1] == 'y')
                str[i] = 'S';
            else
                str[i] = 'K';
        }
        else if (str[i] == 'W') {
            str[i] = 'V';
        }
        else if (str[i] == 'w') {
            str[i] = 'v';
        }
        else if (str[i] == 'Q') {
            str[i] = 'K';
        }
        else if (str[i] == 'q') {
            str[i] = 'k';
        }

        i++;
    }
}

void qu_to_kv(char* str) {
    int i = 0;
    while (str[i] != '\0') {

        if (str[i] == 'q' && str[i + 1] == 'u') {
            str[i] = 'k';
            str[i + 1] = 'v';

        }
        else if (str[i] == 'Q' && str[i + 1] == 'u') {
            str[i] = 'Q';
            str[i + 1] = 'v';
        }

        i++;
    }
}

void x_to_ks(char* str) {
    int i = 0;
    while (str[i]) {
        if (str[i] == 'x' || str[i] == 'X') {

            int L = length(str); // ����� �������������� ������

            // ������� ����� ��� ����� 'k' ����� 'x' � ������� '\0'
            str = (char*)realloc(str, (L + 2) * sizeof(char));

            if (str[i] == 'x')
                str[i] = 'k';
            else
                str[i] = 'K';


            // ������� ���������� ������ ������ �� 1
            for (int j = L; j > i; j--)
                str[j] = str[j - 1];

            // ����� 'k' ������ 's'
            str[i + 1] = 's';

            str[L + 1] = '\0';

            i++; // ������� �������� ����� k
        }

        i++;
    }
}

void ph_you_oo_ee_th(char* str) {
    int i = 0;
    while (str[i]) {
        if ((str[i] == 'p' || str[i] == 'P') && str[i + 1] == 'h') {

            int L = length(str); // ����� �������������� ������

            if (str[i] == 'p')
                str[i] = 'f';
            else
                str[i] = 'F';

            // �������� ������ �� 1 ������ �����
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];

            str[L - 1] = '\0'; // ����� ������    
        }
        else if ((str[i] == 'y' || str[i] == 'Y') && str[i + 1] == 'o' && str[i + 2] == 'u') {

            int L = length(str); // ����� �������������� ������

            if (str[i] == 'y')
                str[i] = 'u';
            else
                str[i] = 'U';

            // �������� ������ �� 1 ������ ����� ��� ����
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];

            str[L - 2] = '\0'; // ����� ������    
        }
        else if ((str[i] == 'O' || str[i] == 'o') && str[i + 1] == 'o') {

            int L = length(str); // ����� �������������� ������

            if (str[i] == 'o')
                str[i] = 'u';
            else
                str[i] = 'U';

            // �������� ������ �� 1 ������ �����
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];

            str[L - 1] = '\0'; // ����� ������    
        }
        else if ((str[i] == 'E' || str[i] == 'e') && str[i + 1] == 'e') {

            int L = length(str); // ����� �������������� ������

            if (str[i] == 'e')
                str[i] = 'i';
            else
                str[i] = 'I';

            // �������� ������ �� 1 ������ �����
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];

            str[L - 1] = '\0'; // ����� ������    
        }
        else if ((str[i] == 'T' || str[i] == 't') && str[i + 1] == 'h') {

            int L = length(str); // ����� �������������� ������

            if (str[i] == 't')
                str[i] = 'z';
            else
                str[i] = 'Z';

            // �������� ������ �� 1 ������ �����
            for (int j = i + 1; j < L - 1; j++)
                str[j] = str[j + 1];

            str[L - 1] = '\0'; // ����� ������    
        }
        i++;
    }
}

bool IsDoubleConsonants(char current, char next) {

    // �������� �� �����
    if (!isalpha(current) || !isalpha(next))
        return false;

    current = tolower(current);
    next = tolower(next);

    // ��� ��������� �����
    char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z' };
    
    // ���� ������� � ��������� ������� �����
    if (current == next) {
        // ���������, ����� ��� ���� ����������
        for (int i = 0; i < 20; i++)
            if (consonants[i] == current && consonants[i] == next)
                return true;
    }

    return false;

}

void DeleteConsonants(char* str) {
    // �������� ������� ���������

    bool repeat = true;
    int i = 0;

    // ���������, ���� ���� �������
    while (repeat) {
        repeat = false;
        i = 0;
        while (str[i]) {
            if (IsDoubleConsonants(str[i], str[i + 1])) {
                repeat = true;

                int L = length(str); // ����� �������������� ������

                // �������� ������ �� 1 ������ �����
                for (int j = i + 1; j < L - 1; j++)
                    str[j] = str[j + 1];

                str[L - 1] = '\0'; // ����� ������    
            }

            i++;
        }
    }
}


#endif