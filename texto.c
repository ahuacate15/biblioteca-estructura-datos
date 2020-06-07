#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

char *getLine(int max) {
    char c, *buffer = malloc(sizeof(char) * max);
    int i = 0;

	//la lectura de caracteres se detiene cuando se presiona enter o cuando se llega al maximo de caracteres permitidosd
    while((c = getchar()) != '\n' && i < max - 1)
        buffer[i++] = c;
    
    buffer[i] = '\0';
    fflush(stdin);

    return buffer;

}

char *lowerString(char *string) {
	int i = 0, total = strlen(string);
	char *lower = calloc(total, sizeof(char));
	
	for(i=0; i<total; i++) 
		lower[i] = tolower(string[i]);
		
	return lower;
}

/*
* @description : verifica que la cadena *string inicie en *search, es decir, se verifica que la cadena 'manifiesto socialista' 
* inicie con el caracter 'manifiesto', cuando esto ocurre la funcion retorna 0
* si la cadena 'manifiesto socialista' es comparada con 'manifiesta', la funcionar retorna 1 ya que el ultimo caracter no coincide  y 'o' es mayor que 'a'
* si la cadena 'manifiesto socialista' es comparada con 'manifiestp', la funcion retorna -1 ya que el ultimo caracter no coincide y la 'o' es menor que 'p'
*/
int searchStartOfString(char *string, char *search) {
	int lengthFiltro = strlen(search);
	int coincide = 0, i = 0;
	
	for(i=0; i<lengthFiltro; i++) {
		if(string[i] != search[i]) {
			coincide = string[i] > search[i] ? -1 : 1;
			break;
		}
	}
	
	return coincide;
}