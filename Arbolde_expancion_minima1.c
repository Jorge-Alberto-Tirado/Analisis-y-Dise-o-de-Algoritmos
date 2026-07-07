#include <stdio.h>
#include <stdlib.h>

// Estructura para representar una arista
struct Edge {
    int origen, destino, peso;
};

// Estructura para representar el grafo
struct Graph {
    int vertices, aristas;
    struct Edge* edge;
};

// Estructura para representar un subconjunto para Union-Find
struct Subcon {
    int padre;
    int nivel;
};

// Funcion para crear un grafo
struct Graph* createGraph(int ver, int ari) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vertices = ver;
    graph->aristas = ari;
    graph->edge = (struct Edge*) malloc(graph->aristas * sizeof(struct Edge));
    return graph;
}

// Funcion para encontrar el conjunto de un elemento i (con compresion de ruta)
int find(struct Subcon subsets[], int i) {
    if (subsets[i].padre != i)
        subsets[i].padre = find(subsets, subsets[i].padre);
    return subsets[i].padre;
}

// Funcion que une dos subconjuntos (por rango)
void Union(struct Subcon subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].nivel < subsets[rootY].nivel) {
        subsets[rootX].padre = rootY;
    } else if (subsets[rootX].nivel > subsets[rootY].nivel) {
        subsets[rootY].padre = rootX;
    } else {
        subsets[rootY].padre = rootX;
        subsets[rootX].nivel++;
    }
}

// Funcion para comparar dos aristas (usada en qsort)
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->peso - b1->peso;
}

// Funcion principal para construir el Arbol de Expansion Minima
void KruskalMST(struct Graph* graph) {
    int vertices = graph->vertices;
    struct Edge result[vertices]; // Aqui guardaremos el MST resultante
    int e = 0; // Indice para result[]
    int i = 0; // Indice para las aristas ordenadas

    // Paso 1: Ordenar todas las aristas de menor a mayor peso
    qsort(graph->edge, graph->aristas, sizeof(graph->edge[0]), compareEdges);

    // Asignar memoria para los subconjuntos
    struct Subcon* subsets = (struct Subcon*) malloc(vertices * sizeof(struct Subcon));

    // Inicializar subconjuntos con elementos individuales (cada vertice es su propio arbol)
    for (int v = 0; v < vertices; ++v) {
        subsets[v].padre = v;
        subsets[v].nivel = 0;
    }

    // Paso 2: Iterar sobre las aristas ordenadas
    while (e < vertices - 1 && i < graph->aristas) {
        // Tomar la arista mas pequeña
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.origen);
        int y = find(subsets, next_edge.destino);

        // Si incluir esta arista no forma un ciclo, se agrega al resultado
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Imprimir el resultado
    printf("Aristas en el Arbol de Expansion Minima:\n");
    int minimumCost = 0;
    for (i = 0; i < e; ++i) {
        // Convertimos los indices (0 a 6) nuevamente a letras (A a G) para la impresion
        printf("%c -- %c == %d\n", result[i].origen + 'A', result[i].destino + 'A', result[i].peso);
        minimumCost += result[i].peso;
    }
    printf("Costo Total: %d\n", minimumCost);

    // Liberar memoria (porque somos personas civilizadas)
    free(subsets);
}

int main() {
    /* Mapeo de vertices:
       A=0, B=1, C=2, D=3, E=4, F=5, G=6
       Grafo con 7 vertices y 11 aristas
    */
    int vertices = 7;
    int aristas = 11;
    struct Graph* graph = createGraph(vertices, aristas);

    // A-B
    graph->edge[0].origen = 0; graph->edge[0].destino = 1; graph->edge[0].peso = 4;
    // A-C
    graph->edge[1].origen = 0; graph->edge[1].destino = 2; graph->edge[1].peso = 3;
    // B-D
    graph->edge[2].origen = 1; graph->edge[2].destino = 3; graph->edge[2].peso = 6;
    // B-E
    graph->edge[3].origen = 1; graph->edge[3].destino = 4; graph->edge[3].peso = 5;
    // C-E
    graph->edge[4].origen = 2; graph->edge[4].destino = 4; graph->edge[4].peso = 7;
    // C-F
    graph->edge[5].origen = 2; graph->edge[5].destino = 5; graph->edge[5].peso = 8;
    // D-E
    graph->edge[6].origen = 3; graph->edge[6].destino = 4; graph->edge[6].peso = 2;
    // D-G
    graph->edge[7].origen = 3; graph->edge[7].destino = 6; graph->edge[7].peso = 9;
    // E-F
    graph->edge[8].origen = 4; graph->edge[8].destino = 5; graph->edge[8].peso = 4;
    // E-G
    graph->edge[9].origen = 4; graph->edge[9].destino = 6; graph->edge[9].peso = 6;
    // F-G
    graph->edge[10].origen = 5; graph->edge[10].destino = 6; graph->edge[10].peso = 3;

    KruskalMST(graph);

    free(graph->edge);
    free(graph);
    return 0;
}
