#include <stdio.h>
#include <stdlib.h>
#define CAPACIDAD_INICIAL 10000 //esta capacidad inicial me parecio razonable

// Estructura de la Pila Dinamica
typedef struct {
    int *elementos; 
    int tope;
    int capacidad;  
} PilaDinamica;


void inicializar(PilaDinamica *p) {
    p->capacidad = CAPACIDAD_INICIAL;
    p->tope = -1;
    p->elementos = (int *)malloc(p->capacidad * sizeof(int));
    if (p->elementos == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
}

int estaVacia(PilaDinamica *p) {
    return p->tope == -1;
}

// Asignar memoria dinamica usandou realloc para sea autoexpandible
void push(PilaDinamica *p, int valor) {
    // Si llegamos al limite de nuestra capacidad actual duplicamos el tamaño de la capacidad teorica
    if (p->tope >= p->capacidad - 1) {
        p->capacidad = p->capacidad * 2;
        
        p->elementos = (int *)realloc(p->elementos, p->capacidad * sizeof(int));
        if (p->elementos == NULL) {
            printf("Error de desbordamiento.\n");
            exit(1);
        }
    }
    
    p->tope++;
    p->elementos[p->tope] = valor;
}

// Extraccion 
int pop(PilaDinamica *p) {
    if (estaVacia(p)) {
        printf("Error logico: Intentando sacar de una pila vacia.\n");
        exit(1);
    }
    int valor = p->elementos[p->tope];
    p->tope--;
    return valor;
}

// Limpieza obligatoria para evitar Memory Leaks
void liberarMemoria(PilaDinamica *p) {
    free(p->elementos);
    p->elementos = NULL;
    p->capacidad = 0;
    p->tope = -1;
}

// la funcion de ackermann
int ackermann_iterativo(int m, int n) {
    PilaDinamica p;
    inicializar(&p); 
    push(&p, m);
    while (!estaVacia(&p)) {
        m = pop(&p);
        if (m == 0) {
            n = n + 1;
        } 
        else if (m > 0 && n == 0) {
            push(&p, m - 1);
            n = 1;
        } 
        else if (m > 0 && n > 0) {
            push(&p, m - 1);
            push(&p, m);
            n = n - 1;
        }
    }
    
    liberarMemoria(&p); 
    return n;
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso correcto: %s <numero_m> <numero_n>\n", argv[0]);
        return 1;
    }

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    if (m < 0 || n < 0) {
        printf("Error: Solo se permiten numeros enteros positivos.\n");
        return 1;
    }
    
    printf("Calculando Ackermann(%d, %d)\n", m, n);
    
    int resultado = ackermann_iterativo(m, n);
    
    printf("El resultado de A(%d, %d) es: %d\n", m, n, resultado);
    return 0;
}