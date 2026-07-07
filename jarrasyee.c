#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int x; // jarra 4 litros
    int y; // jarra 3 litros
    int padre;
} Estado;

Estado estados[MAX];
// Paso 1: Hacer CERRADOS vacio (visitado inicializado en 0)
int visitado[5][4];

// Funcion que encapsula el Paso 2.4.2.1 (NUEVOS-SUCESORES) y 2.4.2.2 (GESTIONA-COLA)
int agregarEstado(int x, int y, int padre, int *n) {
    // Solo se agregan nodos que no estan en ABIERTOS ni en CERRADOS
    if (!visitado[x][y]) {
        estados[*n].x = x;
        estados[*n].y = y;
        estados[*n].padre = padre;
        // Se marca como visitado (equivale a mover a CERRADOS mas tarde)
        visitado[x][y] = 1;
        // GESTIONA-COLA: Se inserta al final de la cola (Busqueda en Anchura)
        (*n)++;
        return 1;
    }
    return 0;
}

void imprimirCamino(int idx) {
    if (idx == -1) return;
    imprimirCamino(estados[idx].padre);
    printf("(%d, %d)\n", estados[idx].x, estados[idx].y);
}

int main() {
    // Paso 1: Hacer ABIERTOS la "cola" formada por el nodo inicial
    int n = 0;
    int frente = 0;

    // Se inserta el ESTADO-INICIAL (0,0) en ABIERTOS
    agregarEstado(1, 1, -1, &n);

    // Paso 2: Mientras que ABIERTOS no este vacia
    while (frente < n) {
        // Paso 2.1: Hacer ACTUAL el primer nodo de ABIERTOS
        Estado actual = estados[frente];

        // Paso 2.4: Si ES-ESTADO-FINAL(ESTADO(ACTUAL))
        if (actual.x == 2) {
            // Paso 2.4.1: devolver el nodo ACTUAL y terminar
            printf("Solucion encontrada:\n");
            imprimirCamino(frente);
            return 0;
        }

        // Paso 2.4.2: En caso contrario, expandir sucesores
        int x = actual.x;
        int y = actual.y;

        // Generacion de NUEVOS-SUCESORES
        // Llenar, vaciar y verter (cada agregarEstado es un sucesor potencial)

        agregarEstado(4, y, frente, &n); // Llenar jarra de 4
        agregarEstado(x, 3, frente, &n); // Llenar jarra de 3
        agregarEstado(0, y, frente, &n); // Vaciar jarra de 4
        agregarEstado(x, 0, frente, &n); // Vaciar jarra de 3

        int transfer = (x + y >= 3) ? (3 - y) : x;
        agregarEstado(x - transfer, y + transfer, frente, &n); // Verter 4 -> 3

        transfer = (x + y >= 4) ? (4 - x) : y;
        agregarEstado(x + transfer, y - transfer, frente, &n); // Verter 3 -> 4

        // Paso 2.2 y 2.3: Hacer ABIERTOS el resto de ABIERTOS y poner ACTUAL en CERRADOS
        frente++;
    }

    // Paso 3: Devolver FALLO
    printf("No se encontro solucion\n");
    return 0;
}
