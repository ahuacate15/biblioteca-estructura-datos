typedef struct customDate CustomDate;

typedef struct prestamo {
    Alumno *alumno;
    CustomDate *date;
    Libro *libro;
    int estado;
    struct Prestamo *siguiente;
} Prestamo;


typedef struct nodoPrestamo {
    int clave;
    Prestamo *prestamo;
    Prestamo *ultimoPrestamo;
    struct nodoPrestamo *izquierda;
    struct nodo *derecha;
} NodoPrestamo;


typedef struct arbolPrestamo {
    NodoPrestamo *raiz; //ordenado por fecha
    NodoPrestamo *raizAlumno; //ordenado por alumno
    int total;
} ArbolPrestamo;

ArbolPrestamo *initArbolPrestamo();
NodoPrestamo *buscarPrestamo(NodoPrestamo *nodo, int clave);
/*-------------prototipo de funciones para interfaces----------*/
void agregarPrestamoMENU(ArbolPrestamo *arbol, ListaAlumno *listaAlumno, Arbol *arbolLibro);
void buscarPrestamosMENU(ArbolPrestamo *arbol);
void imprimirPrestamo(NodoPrestamo *ptrPrestamo);

//---------DEVOLUCIONES-----------
void realizarDevolucion(ArbolPrestamo *arbol,ListaAlumno *listaAlumno,Arbol *arbolLibro);
int verificarPrestamo(NodoPrestamo *ptrPrestamo);
void imprimirPrestamoDetalle(NodoPrestamo *ptrPrestamo);
void cambioEstadoLibro(NodoPrestamo *ptrPrestamo);