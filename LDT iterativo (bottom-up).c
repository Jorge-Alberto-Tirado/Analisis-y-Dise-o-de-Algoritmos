#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define REP 30

int matriz[MAX][MAX], dp[MAX][MAX];

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
    scanf("%d %d", &n_max, &paso);

    srand(1);

    for (int i = 0; i < n_max; i++)
        for (int j = 0; j < n_max; j++)
            matriz[i][j] = rand() % 20 + 1;

    printf("N,Resultado,Iteraciones,Tiempo\n");

    for (int n = n_max; n >= 1; n -= paso) {

        double tiempos[REP];
        int resultado;
        long long contador;

        for (int r = 0; r < REP; r++) {

            contador = 0;

            clock_t ini = clock();

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    contador++;

                    if (i == 0 && j == 0)
                        dp[i][j] = matriz[i][j];
                    else if (i == 0)
                        dp[i][j] = matriz[i][j] + dp[i][j - 1];
                    else if (j == 0)
                        dp[i][j] = matriz[i][j] + dp[i - 1][j];
                    else {
                        int a = dp[i - 1][j];
                        int b = dp[i][j - 1];
                        dp[i][j] = matriz[i][j] + (a > b ? a : b);
                    }
                }
            }

            resultado = dp[n - 1][n - 1];

            clock_t fin = clock();

            tiempos[r] = (double)(fin - ini) / CLOCKS_PER_SEC;
        }

        printf("%d,%d,%lld,%f\n", n, resultado, contador, promedio(tiempos));
    }

    return 0;
}
