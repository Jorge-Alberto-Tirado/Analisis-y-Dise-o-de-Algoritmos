#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// verificar si esta ordenado
int estaOrdenado(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1])
            return 0;
    }
    return 1;
}

// generar permutacion aleatoria
void shuffle(int A[], int n) {
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}

// permutation sort
void permutationSort(int A[], int n) {
    while (!estaOrdenado(A, n)) {
        shuffle(A, n);
    }
}

// ----------- MAIN -----------
int main() {

    srand(time(NULL)); // inicializar aleatoriedad

    FILE *archivo = fopen("datos.csv", "r");
    if (archivo == NULL) {
        printf("Error: no se pudo abrir datos.csv\n");
        return 1;
    }

    int max_datos = 100000;
    int *datos = (int *)malloc(max_datos * sizeof(int));
    int total = 0;

    while (total < max_datos && fscanf(archivo, "%d,", &datos[total]) == 1) {
        total++;
    }

    fclose(archivo);

    printf("Datos cargados: %d\n", total);

    int max_n, paso;

    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    if (max_n > total) {
        printf("Error: max_n supera los datos disponibles\n");
        free(datos);
        return 1;
    }

    printf("\nN,Tiempo_promedio(segundos)\n");

    for (int k = paso; k <= max_n; k += paso) {

        // ⚠️ limite de seguridad
        if (k > 10) {
            printf("n demasiado grande para permutation sort\n");
            break;
        }

        double tiempo_total = 0;

        for (int rep = 0; rep < 30; rep++) {

            int *v = (int *)malloc(k * sizeof(int));

            // copiar datos
            for (int i = 0; i < k; i++) {
                v[i] = datos[i];
            }

            clock_t inicio = clock();

            permutationSort(v, k);

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            tiempo_total += tiempo;

            free(v);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        printf("%d,%f\n", k, tiempo_promedio);
    }

    free(datos);

    return 0;
}
