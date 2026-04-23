#include <stdio.h>

int main(){

    int A[100], S[100];
    int n;
    int comparaciones = 0;

    printf("Cuantos numeros desea ordenar: ");
    scanf("%d", &n);

    printf("Ingrese los numeros:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    int tam = n;

    for(int k = 0; k < n; k++){

        int pos_min = 0;

        for(int i = 1; i < tam; i++){

            comparaciones++;

            if(A[i] < A[pos_min]){
                pos_min = i;
            }
        }

        S[k] = A[pos_min];

        for(int j = pos_min; j < tam-1; j++){
            A[j] = A[j+1];
        }

        tam--;
    }

    printf("\nArreglo ordenado:\n");
    for(int i = 0; i < n; i++){
        printf("%d ", S[i]);
    }

    printf("\n\nNumero de comparaciones: %d\n", comparaciones);

    return 0;
}
