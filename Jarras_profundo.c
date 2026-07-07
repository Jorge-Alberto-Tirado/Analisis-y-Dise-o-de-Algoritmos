#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

typedef struct {
    int x;      // Cantidad en la jarra de 4 litros
    int y;      // Cantidad en la jarra de 3 litros
} Sucesor;

// visitado[x][y] indica si el estado ya fue visitado en la rama actual
int visitado[5][4];

// Imprimir camino solucion
void imprimirCamino(int caminoX[],int caminoY[],int profundidad) {

    printf("\nCAMINO SOLUCION:\n\n");
    for (int i = 0; i <= profundidad; i++) {
        printf("(%d, %d)\n",
               caminoX[i],
               caminoY[i]);
    }
}
int existeSucesor(Sucesor sucesores[],
                  int total,
                  int x,
                  int y) {

    for (int i = 0; i < total; i++) {

        if (sucesores[i].x == x &&
            sucesores[i].y == y) {

            return 1;
        }
    }

    return 0;
}
// busqueda por profundidad
int dfs(int x,int y,int profundidad,int limite,int caminoX[],int caminoY[]) {

    printf("\n=====================================\n");
    printf("Nodo ACTUAL: (%d, %d)\n",x,y);
    printf("Profundidad ACTUAL: %d\n",profundidad);
    printf("=====================================\n");

    // Guardar camino actual
    caminoX[profundidad] = x;
    caminoY[profundidad] = y;

printf("\nPILA ACTUAL :\n");
for (int i = 0; i <= profundidad; i++) {
printf("[%d] (%d, %d)\n",i,caminoX[i],caminoY[i]);
    }

    // Verificar estado final
    if (x == 2) {

        printf("\nSOLUCION ENCONTRADA\n");

        imprimirCamino(caminoX,caminoY,profundidad);

        return 1;
    }

    if (profundidad >= limite)
        return 0;

    // Marcar como visitado
    visitado[x][y] = 1;

//printf("\nElementos analizados:\n");
//for (int i = 0; i <= profundidad; i++) {
//printf("[%d] (%d, %d)\n",i,caminoX[i],caminoY[i]);
//}

    // Generacion de sucesores aleatorios

    Sucesor sucesores[6];

    int total = 0;


        // Llenar jarra de 4
    if (x < 4) {

        if (!existeSucesor(sucesores,total,4,y) &&!visitado[4][y]) {

            sucesores[total].x = 4;
            sucesores[total].y = y;

            total++;
        }
    }

    // Llenar jarra de 3
    if (y < 3) {

        if (!existeSucesor(sucesores,total,x,3) &&!visitado[x][3]) {

            sucesores[total].x = x;
            sucesores[total].y = 3;

            total++;
        }
    }

    // Vaciar jarra de 4
    if (x > 0) {

        if (!existeSucesor(sucesores,total,0,y) &&!visitado[0][y]) {

            sucesores[total].x = 0;
            sucesores[total].y = y;

            total++;
        }
    }

    // Vaciar jarra de 3
    if (y > 0) {

        if (!existeSucesor(sucesores,total,x,0) &&!visitado[x][0]) {

            sucesores[total].x = x;
            sucesores[total].y = 0;

            total++;
        }
    }

    // Verter 4 -> 3
    if (x > 0 && y < 3) {

        int transfer = (x + y >= 3)
                        ? (3 - y)
                        : x;

        int nx = x - transfer;
        int ny = y + transfer;

        if (!existeSucesor(sucesores,total,nx,ny) &&!visitado[nx][ny]) {

            sucesores[total].x = nx;
            sucesores[total].y = ny;

            total++;
        }
    }

    // Verter 3 -> 4
    if (y > 0 && x < 4) {

        int transfer = (x + y >= 4)
                        ? (4 - x)
                        : y;

        int nx = x + transfer;
        int ny = y - transfer;

        if (!existeSucesor(sucesores,total,nx,ny) &&!visitado[nx][ny]) {

            sucesores[total].x = nx;
            sucesores[total].y = ny;

            total++;
        }
    }

    // Revolver sucesores
    for (int i = total - 1; i > 0; i--) {

        int j = rand() % (i + 1);
        Sucesor temp = sucesores[i];
        sucesores[i] = sucesores[j];
        sucesores[j] = temp;
    }

printf("\nSucesores generados:\n");
for (int i = 0; i < total; i++) {
    printf("[%d] (%d, %d)\n",i,sucesores[i].x,sucesores[i].y);
}

    // Explorar sucesores
    for (int i = 0; i < total; i++) {

        int nx = sucesores[i].x;
        int ny = sucesores[i].y;

        // Si no ha sido visitado
        if (!visitado[nx][ny]) {

            if (dfs(nx,ny,profundidad + 1,limite,caminoX,caminoY)) {

                return 1;
            }
        }
    }

    // Desmarcar al regresar
    visitado[x][y] = 0;

    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc != 3) {

        printf("Uso: %s x y\n",
               argv[0]);

        return 1;
    }

    int inicioX = atoi(argv[1]);
    int inicioY = atoi(argv[2]);

    // Validar estado inicial
    if (inicioX < 0 || inicioX > 4 ||
        inicioY < 0 || inicioY > 3) {

        printf("Estado inicial invalido\n");

        return 1;
    }

    int limite = 20;

    int caminoX[MAX];
    int caminoY[MAX];

    // Estado inicial
    if (!dfs(inicioX,inicioY,0,limite,caminoX,caminoY)) {

        printf("\nNo se encontro solucion\n");
    }

    return 0;
}
