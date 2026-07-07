#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N_MAX 50
#define PASO 2
#define CAPACIDAD 50
#define REP 30

// ==========================================
// Arreglos globales
// ==========================================

int pesos[N_MAX];
int valores[N_MAX];

// Contador de llamadas recursivas
long long llamadas = 0;

// ==========================================
// Funcion para obtener el maximo
// ==========================================

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// ==========================================
// Promedio recortado
// Elimina el menor y el mayor tiempo
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
// Mochila recursiva pura
// ==========================================

int mochila_recursiva(int n, int capacidad) {

    llamadas++;

    // Caso base
    if (n == 0 || capacidad == 0)
        return 0;

    // Si el objeto no cabe
    if (pesos[n - 1] > capacidad) {
        return mochila_recursiva(n - 1, capacidad);
    }

    // Tomar objeto
    int incluir =
        valores[n - 1] +
        mochila_recursiva(
            n - 1,
            capacidad - pesos[n - 1]
        );

    // No tomar objeto
    int excluir =
        mochila_recursiva(
            n - 1,
            capacidad
        );

    return maximo(incluir, excluir);
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

    printf("N,Resultado,Operaciones,Tiempo\n");

    for (int n = N_MAX; n >= 1; n -= PASO) {

        double tiempos[REP];
        int resultado = 0;

        for (int r = 0; r < REP; r++) {

            llamadas = 0;

            clock_t inicio = clock();

            resultado =
                mochila_recursiva(
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
            "%d,%d,%lld,%.8f\n",
            n,
            resultado,
            llamadas,
            prom
        );
    }

    return 0;
}
