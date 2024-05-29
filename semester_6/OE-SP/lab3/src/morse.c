#include "morse.h"
#include "morse_dictionary.h"
#include <ctype.h>
#include <string.h>

char* charToMorse(char c) {
    if (isalpha(c)) {
        c = toupper(c);
        return strdup(morseCode[c - 'A']);
    } else if (isdigit(c)) {
        return strdup(morseCode[c - '0' + 26]);
    } else if (c == ' ') {
        return strdup(" ");
    } else {
        return strdup(""); 
    }
}
