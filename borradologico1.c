#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// NUEVO
void remover_elemento(int *vector, int *size, int indice){
    vector[indice] = vector[*size - 1];
    (*size)--;
}

// Funcion que ejecuta el algoritmo y retorna la cantidad de comparaciones
long long ordenar_y_contar(int *A_original, int n) {

    int *A = (int *)malloc(n * sizeof(int));
    int *S = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
        A[i] = A_original[i];
    }

    int tamano_A = n;
    long long contador_instrucciones = 0;

    for(int i = n - 1; i >= 0; i--) {
        int max_idx = 0;

        for(int j = 1; j < tamano_A; j++) {
            contador_instrucciones++;
            if(A[j] > A[max_idx]) {
                max_idx = j;
            }
        }

        S[i] = A[max_idx];

        // NUEVO: eliminacion logica
        remover_elemento(A, &tamano_A, max_idx);
    }

    free(A);
    free(S);

    return contador_instrucciones;
}
