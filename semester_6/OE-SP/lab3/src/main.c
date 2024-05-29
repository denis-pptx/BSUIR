#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morse.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <sourceFilePath> <destinationFilePath>\n", argv[0]);
        return 1;
    }

    char *sourceFilePath = argv[1];
    char *destinationFilePath = argv[2];

    FILE *sourceFile = fopen(sourceFilePath, "r");
    FILE *destinationFile = fopen(destinationFilePath, "w");

    if (sourceFile == NULL || destinationFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char c;
    while ((c = fgetc(sourceFile)) != EOF) {
        char* morse = charToMorse(c);
        fputs(morse, destinationFile);
        fputs(" ", destinationFile); 
    }

    printf("Text successfully converted to Morse code.\n");

    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}
