typedef struct libro Libro;
typedef struct arbol Arbol;

Libro *initializeLibro();
Libro *appendLibro(Libro *libro, char *titulo);
void testPrint(Libro *libro);
void test();
