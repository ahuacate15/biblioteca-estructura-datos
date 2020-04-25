#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *getLine(int max) {
    char c, *buffer = malloc(sizeof(char) * max);
    int i = 0;

    while((c = getchar()) != '\n' && i < max - 1) 
        buffer[i++] = c;
    
    buffer[i] = '\0';

    return buffer;

}