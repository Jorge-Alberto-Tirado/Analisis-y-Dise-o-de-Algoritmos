#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX 32
#define PASO 2
#define CAPACIDAD 50
#define REP 3


// Arreglos globales


// Pesos y valores de los objetos
int pesos[N_MAX];
int valores[N_MAX];


// Contador de operaciones


// Cuenta cuantas combinaciones se evaluan
long long operaciones = 0;


// Funcion para promedio recortado
// Elimina el menor y el mayor tiempo

double promedio(double t[], int n) {

    double suma = 0.0;
    double minimo = t[0];
    double maximo = t[0];

    for (int i = 0; i < n; i++) {

        suma += t[i];

        if (t[i] < minimo)
            minimo = t[i];

        if (t[i] > maximo)
            maximo = t[i];
    }

    suma = suma - minimo - maximo;

    return suma / (n - 2);
}


// Fuerza bruta para mochila


int mochila_fuerza_bruta(int n, int capacidad) {

    int mejor_valor = 0;


    // Total de subconjuntos posibles
    // 2^n combinaciones


    long long total =
        1LL << n;


    // Probar TODAS las combinaciones


    for (long long mascara = 0;
         mascara < total;
         mascara++) {

        operaciones++;

        int peso_total = 0;
        int valor_total = 0;


        // Revisar cada bit de la mascara


        for (int i = 0; i < n; i++) {

            // Si el bit esta encendido
            // el objeto se incluye
            if (mascara & (1LL << i)) {

                peso_total += pesos[i];
                valor_total += valores[i];
            }
        }


        // Validar capacidad


        if (peso_total <= capacidad &&
            valor_total > mejor_valor) {

            mejor_valor = valor_total;
        }
    }

    return mejor_valor;
}


// Programa principal


int main() {

    srand(1);


    // Generar datos UNA sola vez


    for (int i = 0; i < N_MAX; i++) {

        // Pesos entre 1 y 15
        pesos[i] =
            rand() % 15 + 1;

        // Valores entre 10 y 100
        valores[i] =
            rand() % 91 + 10;
    }


    // Mostrar objetos generados


    printf("Objetos generados:\n");
    printf("Indice,Peso,Valor\n");

    for (int i = 0; i < N_MAX; i++) {

        printf("%d,%d,%d\n",
               i,
               pesos[i],
               valores[i]);
    }

    printf("\n");


    // Encabezado CSV


    printf(
        "Metodo,N,Resultado,Operaciones,Tiempo\n"
    );


    // Evaluar multiples tamanos


    for (int n = N_MAX;
         n >= 1;
         n -= PASO) {

        double tiempos[REP];

        int resultado = 0;


        // Repeticiones para promedio


        for (int r = 0; r < REP; r++) {

            operaciones = 0;

            clock_t inicio = clock();

            resultado =
                mochila_fuerza_bruta(
                    n,
                    CAPACIDAD
                );

            clock_t fin = clock();

            tiempos[r] =
                (double)(fin - inicio)
                / CLOCKS_PER_SEC;
        }


        // Tiempo promedio recortado


        double prom =
            promedio(tiempos, REP);


        // Imprimir resultados


        printf(
            "FuerzaBruta,%d,%d,%lld,%.8f\n",
            n,
            resultado,
            operaciones,
            prom
        );
    }

    return 0;
}
