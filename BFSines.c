#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF 999999
#define NIL -1

// Arreglos globales para representar los atributos de los vertices
// En lugar de u.color, usaremos color[u]
int color[MAX_V];
int d[MAX_V];
int pi[MAX_V];

// Matriz de adyacencia para representar G.Adj
int adj[MAX_V][MAX_V];
int num_vertices;

// Implementacion basica de una cola (Queue) para BFS
int queue[MAX_V];
int front = 0;
int rear = 0;

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

int is_empty() {
    return front == rear;
}

// Funcion BFS
void BFS(int s) {
    // Lineas 1-4: Inicializar todos los vertices (excepto el origen)
    for (int u = 0; u < num_vertices; u++) {
        if (u != s) {
            color[u] = WHITE;
            d[u] = INF;
            pi[u] = NIL;
        }
    }

    //Configurar el vertice origen s
    color[s] = GRAY;
    d[s] = 0;
    pi[s] = NIL;

    //Vaciar la cola y encolar el origen
    front = 0;
    rear = 0;
    enqueue(s);

    //El ciclo de exploracion principal
    while (!is_empty()) {
        // Linea 11
        int u = dequeue();

        //Para cada vertice v en la lista de adyacencia de u
        for (int v = 0; v < num_vertices; v++) {
            if (adj[u][v] == 1) { // Verificamos si existe la arista

                //Si el nodo no ha sido visitado
                if (color[v] == WHITE) {
                    color[v] = GRAY;       //Lo marcamos como descubierto
                    d[v] = d[u] + 1;       //Aumentamos la distancia
                    pi[v] = u;             //Guardamos quien lo descubrio
                    enqueue(v);            //Lo metemos a la cola
                }
            }
        }
        //Nodo u completamente explorado
        color[u] = BLACK;
    }
}

int main() {
    // Configuracion de prueba
    num_vertices = 5;

    // Limpiar matriz de adyacencia
    for(int i = 0; i < num_vertices; i++) {
        for(int j = 0; j < num_vertices; j++) {
            adj[i][j] = 0;
        }
    }

    // Crear un grafo de prueba (1 representa conexion)
    // 0 esta conectado con 1 y 2
    adj[0][1] = 1; adj[1][0] = 1;
    adj[0][2] = 1; adj[2][0] = 1;
    // 1 esta conectado con 3
    adj[1][3] = 1; adj[3][1] = 1;
    // 2 esta conectado con 4
    adj[2][4] = 1; adj[4][2] = 1;

    printf("Iniciando BFS desde el vertice 0...\n\n");
    BFS(0);

    // Imprimir los resultados de las distancias y padres
    printf("Resultados del recorrido:\n");
    for(int i = 0; i < num_vertices; i++) {
        printf("Vertice %d: Distancia (d) = %d, Padre (pi) = %d\n", i, d[i], pi[i]);
    }

    return 0;
}
