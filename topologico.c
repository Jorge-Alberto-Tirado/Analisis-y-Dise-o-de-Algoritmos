#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>

typedef struct nodo{
    int color;
    int d;
    int f;
    int pi;
}TNodo;

int tiempo = 0;

void crearGrafo(int **matriz, int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = i + 1; j < vertices; j++){
            int enlace = rand() % 2;
            if(enlace){
                matriz[i][j] = 1;
            }
        }   
    }
}

void imprimirMatriz(int filas, int columnas, int **m) {
    printf("\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%2d ", m[i][j]);
        }
        printf("\n");
    }
}

void insertar(int *orden, int vertices, int u){
    for(int i = vertices - 1; i > 1; i--){
        orden[i] = orden[i-1];
    }
    orden[0] = u;
    return;
}

void dfsVisit(int **matriz, int u, int vertices, TNodo *nodos, int *orden){
    tiempo++;
    nodos[u].d = tiempo;
    nodos[u].color = 1;
    for(int v = 0; v < vertices; v++){
        if(matriz[u][v] == 1 && nodos[v].color == 0){
            nodos[v].pi = u;
            dfsVisit(matriz, v, vertices, nodos, orden);
        }
    }
    nodos[u].color = 2;
    tiempo++;
    nodos[u].f = tiempo;
    insertar(orden, vertices, u);
}

void dfs(int **matriz, int vertices){
    TNodo *V = (TNodo*)malloc(vertices * sizeof(TNodo));
    int *ordenTopologico = (int*)calloc(vertices, sizeof(int));
    
    for(int i = 0; i < vertices; i++){
        V[i].color = 0;
        V[i].d = -1;
        V[i].f = -1;
        V[i].pi = -1;
    }
    int tiempo = 0;

    for(int u = 0; u < vertices; u++){
        if(V[u].color == 0){
            dfsVisit(matriz, u, vertices, V, ordenTopologico);
        }
    }

    for(int i = 0; i< vertices; i++){
        printf("Nodo: %d [f:%d], ", ordenTopologico[i], V[ordenTopologico[i]].f);
    }

    free(V);
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    if(argc != 2){
        printf("Uso: %s <numero de vertices>", argv[0]);
        return 1;
    }
    
    int vertices = atoi(argv[1]);
    if(vertices <= 0){
        printf("Introduzca valor de vertices positivo");
        return 1;
    }
    
    int **matriz = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        matriz[i] = (int*)calloc(vertices, sizeof(int));
    }
    
    crearGrafo(matriz, vertices);

    imprimirMatriz(vertices, vertices, matriz);

    dfs(matriz, vertices);

    for (int i = 0; i < vertices; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}