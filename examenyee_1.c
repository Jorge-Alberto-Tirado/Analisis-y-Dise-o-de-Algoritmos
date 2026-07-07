#include <stdio.h>
#include <stdlib.h>

// Ya no definimos un limite estatico, solo una capacidad inicial razonable
#define CAPACIDAD_INICIAL 1000

// Estructura de la Pila Dinamica
typedef struct {
    int *elementos; // Apuntador que manejara el arreglo dinamico
    int tope;
    int capacidad;  // Controla cuanto espacio tenemos reservado actualmente
} PilaDinamica;

// 1. Inicializacion pidiendo memoria al Sistema Operativo
void inicializar(PilaDinamica *p) {
    p->capacidad = CAPACIDAD_INICIAL;
    p->tope = -1;
    // Pedimos el primer bloque de memoria con malloc
    p->elementos = (int *)malloc(p->capacidad * sizeof(int));

    if (p->elementos == NULL) {
        printf("Error fatal: El Sistema Operativo nos nego la memoria inicial.\n");
        exit(1);
    }
}

int estaVacia(PilaDinamica *p) {
    return p->tope == -1;
}

// 2. Insercion con AUTO-EXPANSION (La magia de realloc)
void push(PilaDinamica *p, int valor) {
    // Si llegamos al limite de nuestra capacidad actual...
    if (p->tope >= p->capacidad - 1) {
        // Duplicamos el tamaño de la capacidad teorica
        p->capacidad = p->capacidad * 2;

        // realloc intenta expandir el bloque de memoria actual
        // o lo mueve completo a un lugar mas grande si es necesario
        p->elementos = (int *)realloc(p->elementos, p->capacidad * sizeof(int));

        if (p->elementos == NULL) {
            printf("Error de desbordamiento: RAM agotada. Ackermann gano la batalla.\n");
            exit(1);
        }
    }

    // Una vez asegurado el espacio, insertamos normalmente
    p->tope++;
    p->elementos[p->tope] = valor;
}

// 3. Extraccion normal
int pop(PilaDinamica *p) {
    if (estaVacia(p)) {
        printf("Error logico: Intentando sacar de una pila vacia.\n");
        exit(1);
    }
    int valor = p->elementos[p->tope];
    p->tope--;
    return valor;
}

// 4. Limpieza obligatoria para evitar Memory Leaks
void liberarMemoria(PilaDinamica *p) {
    free(p->elementos);
    p->elementos = NULL;
    p->capacidad = 0;
    p->tope = -1;
}

// La funcion de Ackermann usando la Pila Dinamica
int ackermann_iterativo(int m, int n) {
    PilaDinamica p;
    inicializar(&p); // Arrancamos motores

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
            // Regla recursiva invertida para la pila LIFO
            push(&p, m - 1);
            push(&p, m);
            n = n - 1;
        }
    }

    // Destruimos la evidencia antes de irnos
    liberarMemoria(&p);
    return n;
}

// main con recepcion de argumentos
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

    printf("Calculando Ackermann(%d, %d) con memoria dinamica...\n", m, n);

    int resultado = ackermann_iterativo(m, n);

    printf("El resultado de A(%d, %d) es: %d\n", m, n, resultado);
    return 0;
}
