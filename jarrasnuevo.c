#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#include <time.h>

typedef struct {

    int x;      // Cantidad en la jarra de 4 litros
    int y;      // Cantidad en la jarra de 3 litros
    int padre;  // Indice del estado padre

} Estado;

Estado estados[MAX];

// visitado[x][y] indica si el estado ya fue generado
int visitado[5][4];



// Agregar un nuevo estado si no existe aun
int agregarEstado(int x, int y, int padre, int *n) {

    // Si no ha sido visitado
    if (!visitado[x][y]) {

        estados[*n].x = x;
        estados[*n].y = y;
        estados[*n].padre = padre;

        // Marcar como visitado
        visitado[x][y] = 1;

        // Insertar en ABIERTOS
        (*n)++;

        return 1;
    }

    return 0;
}


// Imprimir el camino solucion
void imprimirCamino(int idx) {

    if (idx == -1)
        return;

    imprimirCamino(estados[idx].padre);

    printf("(%d, %d)\n",
           estados[idx].x,
           estados[idx].y);
}
typedef struct {
    int nx;
    int ny;
} Sucesor;

int main(int argc, char *argv[]) {

    srand(time(NULL));

        if (argc != 3) {
        printf("Uso: %s x y\n", argv[0]);
        return 1;
    }

        int inicioX = atoi(argv[1]);
        int inicioY = atoi(argv[2]);

        if (inicioX < 0 || inicioX > 4 ||
        inicioY < 0 || inicioY > 3) {

        printf("Estado inicial invalido\n");
        return 1;
    }

    int n = 0;          // Total de estados generados
    int frente = 0;     // Inicio de la cola BFS

    // Estado inicial
    agregarEstado(inicioX, inicioY, -1, &n);

    // Mientras ABIERTOS no este vacia
    while (frente < n) {

        printf("\n=====================================\n");

        // ABIERTOS
        printf("Contenido de ABIERTOS:\n");

        for (int i = frente; i < n; i++) {

            printf("[%d] (%d, %d)\n",
                   i,
                   estados[i].x,
                   estados[i].y);
        }

        // CERRADOS
        printf("\nContenido de CERRADOS:\n");

        for (int i = 0; i < frente; i++) {

            printf("[%d] (%d, %d)\n",
                   i,
                   estados[i].x,
                   estados[i].y);
        }

        printf("=====================================\n");

        // Nodo actual
        Estado actual = estados[frente];

        printf("Nodo ACTUAL: (%d, %d)\n",
               actual.x,
               actual.y);

        // Verificar estado final
        if (actual.x == 2) {

            printf("\nSOLUCION ENCONTRADA\n\n");

            imprimirCamino(frente);

            return 0;
        }

        int x = actual.x;
        int y = actual.y;


               // Generacion de sucesores aleatorios

        Sucesor sucesores[6];
        int total = 0;

        // Llenar jarra de 4
        sucesores[total].nx = 4;
        sucesores[total].ny = y;
        total++;

        // Llenar jarra de 3
        sucesores[total].nx = x;
        sucesores[total].ny = 3;
        total++;

        // Vaciar jarra de 4
        sucesores[total].nx = 0;
        sucesores[total].ny = y;
        total++;

        // Vaciar jarra de 3
        sucesores[total].nx = x;
        sucesores[total].ny = 0;
        total++;

        // Verter 4 -> 3
        int transfer = (x + y >= 3) ? (3 - y) : x;

        sucesores[total].nx = x - transfer;
        sucesores[total].ny = y + transfer;
        total++;

        // Verter 3 -> 4
        transfer = (x + y >= 4) ? (4 - x) : y;

        sucesores[total].nx = x + transfer;
        sucesores[total].ny = y - transfer;
        total++;

        // Revolver sucesores (Fisher-Yates)
        for (int i = total - 1; i > 0; i--) {

            int j = rand() % (i + 1);

            Sucesor temp = sucesores[i];
            sucesores[i] = sucesores[j];
            sucesores[j] = temp;
        }

        // Insertar sucesores ya revueltos
        for (int i = 0; i < total; i++) {

            agregarEstado(
                sucesores[i].nx,
                sucesores[i].ny,
                frente,
                &n
            );
        }

        // Mover ACTUAL de ABIERTOS a CERRADOS
        frente++;
    }

    printf("No se encontro solucion\n");

    return 0;
}
