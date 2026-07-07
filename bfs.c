#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>

typedef struct nodo{
    int color;
    int d;
    int pi;
}TNodo;

typedef struct cola{
    int inicio;
    int cantidad;
    int *nodos;
}TCola;


void crearGrafo(int **matriz, int vertices){
    for(int i = 0; i < vertices; i++){
        for(int j = i + 1; j < vertices; j++){
            int enlace = rand() % 2;
            if(enlace){
                matriz[i][j] = 1;
                matriz[j][i] = 1;
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

void encolar(TCola *cola, int nuevo, int maximo){
    if(cola->cantidad == maximo) return;

    int pos = (cola->inicio + cola->cantidad) % maximo;

    cola->nodos[pos] = nuevo;
    cola->cantidad++;    
}

int desencolar(TCola *lista, int maximo){
    if(lista->cantidad == 0) return -1;
    int nuevo = lista->nodos[lista->inicio];
    lista->inicio = (lista->inicio + 1) % maximo;
    lista->cantidad--;
    return nuevo;
}

void bfs(int **matriz, int vertices){
    TNodo *V = (TNodo*)malloc(vertices * sizeof(TNodo));

    for(int i = 0; i < vertices; i++){
        V[i].color = 0;
        V[i].d = INT_MAX;
        V[i].pi = -1;
    }
    V[0].color = 1;
    V[0].d = 0;

    TCola *Q = (TCola *)malloc(sizeof(TCola));;
    Q->inicio = 0;
    Q->cantidad = 0;
    Q->nodos = (int*)malloc(vertices * sizeof(int));

    encolar(Q, 0, vertices);

    while(Q->cantidad != 0){
    int u = desencolar(Q, vertices);
    
    for(int i = 0; i < vertices; i++){
        if(matriz[u][i] == 1 && V[i].color == 0){
            V[i].color = 1;
            V[i].d = V[u].d + 1;
            V[i].pi = u;
            encolar(Q, i, vertices);
            printf("Visitado: %d desde %d (Distancia: %d)\n", i, u, V[i].d);
        }
    }
        V[u].color = 2;
    }
    free(V);
    free(Q->nodos);
    free(Q);
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

    bfs(matriz, vertices);

    for (int i = 0; i < vertices; i++){
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}