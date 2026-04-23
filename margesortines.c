#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// funcion merge
void merge(int A[], int inicio, int medio, int fin) {
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = A[inicio + i];

    for (int j = 0; j < n2; j++)
        R[j] = A[medio + 1 + j];

    int i = 0, j = 0, k = inicio;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k++] = L[i++];
    }

    while (j < n2) {
        A[k++] = R[j++];
    }

    free(L);
    free(R);
}

// funcion merge sort
void mergeSort(int A[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = (inicio + fin) / 2;
        mergeSort(A, inicio, medio);
        mergeSort(A, medio + 1, fin);
        merge(A, inicio, medio, fin);
    }
}

int main(){

    FILE *archivo = fopen("datos.csv", "r");
    if(archivo == NULL){
        printf("Error: no se pudo abrir datos.csv\n");
        return 1;
    }

    int max_datos = 100000;
    int *datos = malloc(max_datos * sizeof(int));
    int total = 0;

    while(total < max_datos && fscanf(archivo, "%d,", &datos[total]) == 1){
        total++;
    }

    fclose(archivo);

    printf("Datos cargados: %d\n", total);

    int max_n, paso;

    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    if(max_n > total){
        printf("Error: max_n supera los datos disponibles\n");
        free(datos);
        return 1;
    }

    printf("\nN,Tiempo_promedio(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        double tiempo_total = 0;

        for(int rep = 0; rep < 30; rep++){

            int *v = malloc(k * sizeof(int));

            // copiar datos
            for(int i = 0; i < k; i++){
                v[i] = datos[i];
            }

            clock_t inicio = clock();

            mergeSort(v, 0, k - 1);

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
