#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// eliminar elemento por indice
void remover_elemento(int **vector, int *size, int indice){
    for(int i = indice; i < *size - 1; i++){
        (*vector)[i] = (*vector)[i + 1];
    }
    (*size)--;
    *vector = realloc(*vector, (*size) * sizeof(int));
}

int main(){
    int max_n, paso;

    // pedir datos
    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    printf("\nN,Instrucciones,Formula\n");

    for(int k = paso; k <= max_n; k += paso){

        int size = k;
        int size_s = size;

        int *v = malloc(size * sizeof(int));

        // llenar con numeros aleatorios
        for(int i = 0; i < size; i++){
            v[i] = rand() % 10001;
        }

        int *s = malloc(size * sizeof(int));

        int contador = 0;

        while(size >= 2){
            int mayor = v[0];
            int indice = 0;

            for(int i = 1; i < size; i++){
                if(v[i] > mayor){
                    mayor = v[i];
                    indice = i;
                }
                contador++;
            }

            remover_elemento(&v, &size, indice);
            s[size] = mayor;

            if(size == 1){
                size--;
                s[size] = v[0];
            }
        }

        int formula = size_s * (size_s - 1) / 2;

        printf("%d,%d,%d\n", size_s, contador, formula);

        free(v);
        free(s);
    }

    return 0;
}
