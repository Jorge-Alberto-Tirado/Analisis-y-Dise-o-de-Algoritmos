#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100000

// arreglo para memoizacion
long long F[MAX];
// contador de llamadas
long long contador = 0;
// funcion fibonacci con memoizacion
long long fibonacci(int n) {
    contador++;
    // si ya esta calculado
    if (F[n] != -1)
        return F[n];
    if (n <= 1)
        F[n] = n;
    else
        F[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return F[n];
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
            // inicializar memoizacion
            for (int i = 0; i <= n; i++) {
                F[i] = -1;
            }
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
