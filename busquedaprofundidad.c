#include <stdio.h>

#define NUM_NODOS 5

// Matriz de adyacencia que representa nuestro grafo
// 0 significa no hay camino, 1 significa hay camino
int grafo[NUM_NODOS][NUM_NODOS] = {
    {0, 1, 1, 0, 0}, // Nodo 0 se conecta con 1 y 2
    {1, 0, 0, 1, 0}, // Nodo 1 se conecta con 0 y 3
    {1, 0, 0, 0, 1}, // Nodo 2 se conecta con 0 y 4
    {0, 1, 0, 0, 0}, // Nodo 3 se conecta solo con 1
    {0, 0, 1, 0, 0}  // Nodo 4 se conecta solo con 2
};

// Arreglo para llevar el registro de los nodos ya explorados
// Funciona exactamente como tu lista de CERRADOS
int visitados[NUM_NODOS] = {0, 0, 0, 0, 0};

// Funcion recursiva para la Busqueda en Profundidad (DFS)
void busquedaProfundidad(int nodoActual) {
    // Marcamos el nodo actual como visitado inmediatamente
    visitados[nodoActual] = 1;
    printf("Explorando las profundidades del nodo: %d\n", nodoActual);

    // Revisamos a todos los posibles vecinos de este nodo
    for (int i = 0; i < NUM_NODOS; i++) {
        // Preguntamos dos cosas:
        // Hay conexion real (1)? Y el vecino NO ha sido visitado (0)?
        if (grafo[nodoActual][i] == 1 && visitados[i] == 0) {

            // Si ambas son ciertas, nos hundimos mas en la madriguera
            // La magia de la recursividad hace el trabajo de la Pila aqui
            busquedaProfundidad(i);
        }
    }
}

int main() {
    printf("Iniciando Busqueda en Profundidad (DFS)...\n");
    printf("Que la suerte este siempre de tu lado.\n\n");

    // Lanzamos el algoritmo empezando desde el nodo raiz (0)
    busquedaProfundidad(0);

    printf("\nBusqueda terminada. Sobrevivimos al laberinto.\n");
    return 0;
}
