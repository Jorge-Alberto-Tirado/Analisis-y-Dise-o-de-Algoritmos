#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// contador global de llamadas
long long contador = 0;

// fibonacci recursivo
long long fibonacci(int n) {
    contador++;

    if (n <= 1)
        return n;

    return fibonacci(n - 1) + fibonacci(n - 2);
}
int main() {

    int max_n, paso;

    printf("Valor maximo de n: ");
    scanf("%d", &max_n);

    printf("Incremento: ");
    scanf("%d", &paso);

    printf("\nn,Tiempo_promedio(segundos),Llamadas\n");

    for (int n = paso; n <= max_n; n += paso) {

        double tiempo_total = 0;
        long long llamadas_total = 0;

        for (int rep = 0; rep < 30; rep++) {

            contador = 0;

            clock_t inicio = clock();

            fibonacci(n);

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            tiempo_total += tiempo;
            llamadas_total += contador;
        }

        double tiempo_promedio = tiempo_total / 30.0;
        long long llamadas_promedio = llamadas_total / 30;

        printf("%d,%f,%lld\n", n, tiempo_promedio, llamadas_promedio);
    }

    return 0;
}
