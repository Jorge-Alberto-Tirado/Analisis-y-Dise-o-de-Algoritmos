#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_MAX 20
#define PASO 2
#define CAPACIDAD 50
#define REP 30

// =====================================================
// Variables globales
// =====================================================

// Arreglos para pesos y valores
int pesos[N_MAX];
int valores[N_MAX];

// Contadores de operaciones
long long llamadas_recursivas = 0;
long long llamadas_memo = 0;
long long iteraciones_bottom = 0;

// Tabla para memoizacion
int memo[N_MAX + 1][CAPACIDAD + 1];

// =====================================================
// Funcion para obtener el maximo entre dos valores
// =====================================================
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// =====================================================
// Funcion para calcular promedio recortado
// Elimina el menor y el mayor tiempo
// =====================================================
double promedio(double t[], int n) {

    double suma = 0.0;
    double min = t[0];
    double max = t[0];

    for (int i = 0; i < n; i++) {

        suma += t[i];

        if (t[i] < min)
            min = t[i];

        if (t[i] > max)
            max = t[i];
    }

    suma = suma - min - max;

    return suma / (n - 2);
}

// =====================================================
// Version recursiva pura
// =====================================================
int mochila_recursiva(int n, int capacidad) {

    llamadas_recursivas++;

    // Caso base
    if (n == 0 || capacidad == 0)
        return 0;

    // Si el peso excede la capacidad
    if (pesos[n - 1] > capacidad) {
        return mochila_recursiva(n - 1, capacidad);
    }

    // Tomar o no tomar el objeto
    int incluir =
        valores[n - 1] +
        mochila_recursiva(n - 1, capacidad - pesos[n - 1]);

    int excluir =
        mochila_recursiva(n - 1, capacidad);

    return maximo(incluir, excluir);
}

// =====================================================
// Version memoizada (Top-Down)
// =====================================================
int mochila_memo(int n, int capacidad) {

    llamadas_memo++;

    // Caso base
    if (n == 0 || capacidad == 0)
        return 0;

    // Si ya fue calculado
    if (memo[n][capacidad] != -1)
        return memo[n][capacidad];

    // Si el peso excede
    if (pesos[n - 1] > capacidad) {

        memo[n][capacidad] =
            mochila_memo(n - 1, capacidad);

        return memo[n][capacidad];
    }

    // Evaluar incluir o excluir
    int incluir =
        valores[n - 1] +
        mochila_memo(n - 1,
                     capacidad - pesos[n - 1]);

    int excluir =
        mochila_memo(n - 1, capacidad);

    memo[n][capacidad] =
        maximo(incluir, excluir);

    return memo[n][capacidad];
}

// =====================================================
// Version iterativa Bottom-Up
// =====================================================
int mochila_bottom_up(int n, int capacidad) {

    int **dp;

    // Reservar memoria dinamica
    dp = (int **) malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *) malloc((capacidad + 1) * sizeof(int));
    }

    // Construccion de la tabla
    for (int i = 0; i <= n; i++) {

        for (int w = 0; w <= capacidad; w++) {

            iteraciones_bottom++;

            // Casos base
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }

            else if (pesos[i - 1] <= w) {

                int incluir =
                    valores[i - 1] +
                    dp[i - 1][w - pesos[i - 1]];

                int excluir =
                    dp[i - 1][w];

                dp[i][w] =
                    maximo(incluir, excluir);
            }

            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int resultado = dp[n][capacidad];

    // Liberar memoria
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }

    free(dp);

    return resultado;
}

// =====================================================
// Funcion principal
// =====================================================
int main() {

    srand(1);

    // =================================================
    // Generar datos UNA sola vez
    // =================================================

    for (int i = 0; i < N_MAX; i++) {

        // Pesos entre 1 y 15
        pesos[i] = rand() % 15 + 1;

        // Valores entre 10 y 100
        valores[i] = rand() % 91 + 10;
    }

    // =================================================
    // Mostrar datos generados
    // =================================================

    printf("Objetos generados:\n");
    printf("Indice,Peso,Valor\n");

    for (int i = 0; i < N_MAX; i++) {
        printf("%d,%d,%d\n",
               i,
               pesos[i],
               valores[i]);
    }

    printf("\n");

    // =================================================
    // CABECERA CSV
    // =================================================

    printf("Metodo,N,Resultado,Operaciones,Tiempo\n");

    // =================================================
    // Ejecutar por intervalos
    // =================================================

    for (int n = N_MAX; n >= 1; n -= PASO) {

        // =================================================
        // RECURSIVO
        // =================================================

        double tiempos_rec[REP];
        int resultado_rec = 0;

        for (int r = 0; r < REP; r++) {

            llamadas_recursivas = 0;

            clock_t inicio = clock();

            resultado_rec =
                mochila_recursiva(n, CAPACIDAD);

            clock_t fin = clock();

            tiempos_rec[r] =
                (double)(fin - inicio) / CLOCKS_PER_SEC;
        }

        double prom_rec =
            promedio(tiempos_rec, REP);

        printf("Recursivo,%d,%d,%lld,%.8f\n",
               n,
               resultado_rec,
               llamadas_recursivas,
               prom_rec);

        // =================================================
        // MEMOIZACION
        // =================================================

        double tiempos_memo[REP];
        int resultado_memo = 0;

        for (int r = 0; r < REP; r++) {

            llamadas_memo = 0;

            // Reiniciar memo
            memset(memo, -1, sizeof(memo));

            clock_t inicio = clock();

            resultado_memo =
                mochila_memo(n, CAPACIDAD);

            clock_t fin = clock();

            tiempos_memo[r] =
                (double)(fin - inicio) / CLOCKS_PER_SEC;
        }

        double prom_memo =
            promedio(tiempos_memo, REP);

        printf("Memoizacion,%d,%d,%lld,%.8f\n",
               n,
               resultado_memo,
               llamadas_memo,
               prom_memo);

        // =================================================
        // BOTTOM UP
        // =================================================

        double tiempos_bottom[REP];
        int resultado_bottom = 0;

        for (int r = 0; r < REP; r++) {

            iteraciones_bottom = 0;

            clock_t inicio = clock();

            resultado_bottom =
                mochila_bottom_up(n, CAPACIDAD);

            clock_t fin = clock();

            tiempos_bottom[r] =
                (double)(fin - inicio) / CLOCKS_PER_SEC;
        }

        double prom_bottom =
            promedio(tiempos_bottom, REP);

        printf("BottomUp,%d,%d,%lld,%.8f\n",
               n,
               resultado_bottom,
               iteraciones_bottom,
               prom_bottom);
    }

    return 0;
}
