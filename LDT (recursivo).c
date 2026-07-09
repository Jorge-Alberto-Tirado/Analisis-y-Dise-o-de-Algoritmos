#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define REP 30

int matriz[MAX][MAX];
long long contador = 0;

// funcion recursiva
int LT_rec(int i, int j) {
    contador++;

    if (i == 0 && j == 0)
        return matriz[0][0];

    if (i == 0)
        return matriz[i][j] + LT_rec(i, j - 1);

    if (j == 0)
        return matriz[i][j] + LT_rec(i - 1, j);

    int arriba = LT_rec(i - 1, j);
    int izquierda = LT_rec(i, j - 1);

    return matriz[i][j] + (arriba > izquierda ? arriba : izquierda);
}

double promedio(double t[]) {
    double suma = 0, min = t[0], max = t[0];

    for (int i = 0; i < REP; i++) {
        if (t[i] < min) min = t[i];
        if (t[i] > max) max = t[i];
        suma += t[i];
    }
    return (suma - min - max) / (REP - 2);
}

int main() {

    int n_max, paso;

    printf("Tamano maximo de la matriz: ");
    scanf("%d", &n_max);

    printf("Intervalo (paso): ");
    scanf("%d", &paso);

    srand(1);

    for (int i = 0; i < n_max; i++)
        for (int j = 0; j < n_max; j++)
            matriz[i][j] = rand() % 20 + 1;

    printf("\nN,Max_Tesoro,Llamadas,Tiempo\n");

    for (int n = n_max; n >= 1; n -= paso) {

        double tiempos[REP];
        int resultado;

        for (int r = 0; r < REP; r++) {

            contador = 0;

            clock_t ini = clock();

            resultado = LT_rec(n - 1, n - 1);

            clock_t fin = clock();

            tiempos[r] = (double)(fin - ini) / CLOCKS_PER_SEC;
        }

        printf("%d,%d,%lld,%f\n", n, resultado, contador, promedio(tiempos));

        if (n > 25) {
            printf("...\n");
            break;
        }
    }

    return 0;
}
