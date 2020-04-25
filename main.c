#include <stdio.h>
#include <stdlib.h>
#include "sede.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	//prueba de metodos de sedes
	ListaSede *lista = initListSede();

    requestNewSede(lista);
    printListSedes(lista);
    
	return 0;
}
