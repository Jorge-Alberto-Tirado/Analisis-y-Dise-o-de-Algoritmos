#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_MAX 5000
#define PASO 200
#define CAPACIDAD 50
#define REP 30

// ==========================================
// Arreglos globales
// ==========================================

int pesos[N_MAX];
int valores[N_MAX];

// Tabla memo
int memo[N_MAX + 1][CAPACIDAD + 1];

// Contador
long long llamadas = 0;

// ==========================================
// Funcion maximo
// ==========================================

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// ==========================================
// Promedio recortado
// ==========================================

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

// ==========================================
// Mochila memoizada
// ==========================================

int mochila_memo(int n, int capacidad) {

    llamadas++;

    // Caso base
    if (n == 0 || capacidad == 0)
        return 0;

    // Si ya esta calculado
    if (memo[n][capacidad] != -1)
        return memo[n][capacidad];

    // Si no cabe
    if (pesos[n - 1] > capacidad) {

        memo[n][capacidad] =
            mochila_memo(
                n - 1,
                capacidad
            );

        return memo[n][capacidad];
    }

    // Tomar objeto
    int incluir =
        valores[n - 1] +
        mochila_memo(
            n - 1,
            capacidad - pesos[n - 1]
        );

    // No tomar objeto
    int excluir =
        mochila_memo(
            n - 1,
            capacidad
        );

    memo[n][capacidad] =
        maximo(incluir, excluir);

    return memo[n][capacidad];
}

// ==========================================
// Programa principal
// ==========================================

int main() {

    srand(1);

    // Generar datos una sola vez
    for (int i = 0; i < N_MAX; i++) {

        pesos[i] = rand() % 15 + 1;
        valores[i] = rand() % 91 + 10;
    }

    printf("Metodo,N,Resultado,Operaciones,Tiempo\n");

    for (int n = N_MAX; n >= 1; n -= PASO) {

        double tiempos[REP];
        int resultado = 0;

        for (int r = 0; r < REP; r++) {

            llamadas = 0;

            // Reiniciar memo
            memset(memo, -1, sizeof(memo));

            clock_t inicio = clock();

            resultado =
                mochila_memo(
                    n,
                    CAPACIDAD
                );

            clock_t fin = clock();

            tiempos[r] =
                (double)(fin - inicio)
                / CLOCKS_PER_SEC;
        }

        double prom =
            promedio(tiempos, REP);

        printf(
            "Memoizacion,%d,%d,%lld,%.8f\n",
            n,
            resultado,
            llamadas,
            prom
        );
    }

    return 0;
}
