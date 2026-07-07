#include <stdio.h>
#include <stdlib.h>
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

// ==========================================
// Contadores de operaciones
// ==========================================

// Cuenta cuantas veces se ejecuta el ciclo interno
long long iteraciones = 0;

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
    double minimo = t[0];
    double maximo_t = t[0];

    for (int i = 0; i < n; i++) {

        suma += t[i];

        if (t[i] < minimo)
            minimo = t[i];

        if (t[i] > maximo_t)
            maximo_t = t[i];
    }

    suma = suma - minimo - maximo_t;

    return suma / (n - 2);
}

// ==========================================
// Mochila Bottom-Up
// ==========================================

int mochila_bottom_up(int n, int capacidad) {

    // ======================================
    // Crear matriz dinamica DP
    // ======================================

    int **dp =
        (int **) malloc(
            (n + 1) * sizeof(int *)
        );

    for (int i = 0; i <= n; i++) {

        dp[i] =
            (int *) malloc(
                (capacidad + 1)
                * sizeof(int)
            );
    }

    // ======================================
    // Construccion de tabla DP
    // ======================================

    for (int i = 0; i <= n; i++) {

        for (int w = 0; w <= capacidad; w++) {

            // ==================================
            // Contar iteracion
            // Cada vuelta del ciclo cuenta
            // como una operacion importante
            // ==================================

            iteraciones++;

            // Caso base
            if (i == 0 || w == 0) {

                dp[i][w] = 0;
            }

            // Si el objeto cabe
            else if (pesos[i - 1] <= w) {

                int incluir =
                    valores[i - 1] +
                    dp[i - 1][
                        w - pesos[i - 1]
                    ];

                int excluir =
                    dp[i - 1][w];

                dp[i][w] =
                    maximo(
                        incluir,
                        excluir
                    );
            }

            // Si no cabe
            else {

                dp[i][w] =
                    dp[i - 1][w];
            }
        }
    }

    int resultado = dp[n][capacidad];

    // ======================================
    // Liberar memoria
    // ======================================

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }

    free(dp);

    return resultado;
}

// ==========================================
// Programa principal
// ==========================================

int main() {

    srand(1);

    // ======================================
    // Generar datos UNA sola vez
    // ======================================

    for (int i = 0; i < N_MAX; i++) {

        pesos[i] = rand() % 15 + 1;
        valores[i] = rand() % 91 + 10;
    }

    // ======================================
    // Encabezado CSV
    // ======================================

    printf("Metodo,N,Resultado,Iteraciones,Tiempo\n");

    // ======================================
    // Evaluar multiples tamanos
    // ======================================

    for (int n = N_MAX; n >= 1; n -= PASO) {

        double tiempos[REP];

        int resultado = 0;

        // ==================================
        // Repeticiones para medir tiempo
        // ==================================

        for (int r = 0; r < REP; r++) {

            // Reiniciar contador
            iteraciones = 0;

            clock_t inicio = clock();

            resultado =
                mochila_bottom_up(
                    n,
                    CAPACIDAD
                );

            clock_t fin = clock();

            tiempos[r] =
                (double)(fin - inicio)
                / CLOCKS_PER_SEC;
        }

        // ==================================
        // Calcular promedio recortado
        // ==================================

        double prom =
            promedio(tiempos, REP);

        // ==================================
        // Imprimir resultados
        // ==================================

        printf(
            "BottomUp,%d,%d,%lld,%.8f\n",
            n,
            resultado,
            iteraciones,
            prom
        );
    }

    return 0;
}
