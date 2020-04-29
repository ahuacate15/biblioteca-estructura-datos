/*
* @param max : maximo de caracteres leidos
* @description : obtengo el texto ingresado por teclado, incluyendo espacios en blanco
*/
char *getLine(int max);

/*
* @description : convierto una cadena de caracteres a minuscula
*/
char *lowerString(char *string);

/*
* @description : verifica que la cadena *string inicie en *search, es decir, se verifica que la cadena 'manifiesto socialista' 
* inicie con el caracter 'manifiesto', cuando esto ocurre la funcion retorna 0
* si la cadena 'manifiesto socialista' es comparada con 'manifiesta', la funcionar retorna -1 ya que el ultimo caracter no coincide  y 'o' es mayor que 'a'
* si la cadena 'manifiesto socialista' es comparada con 'manifiestp', la funcion retorna 1 ya que el ultimo caracter no coincide y la 'o' es menor que 'p'
*/
int searchStartOfString(char *string, char *search);
