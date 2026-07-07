#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    printf("\nN,Instrucciones,Formula,Tiempo(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        int size = k;
        int size_s = size;

        int *v = malloc(size * sizeof(int));

        // generar datos (NO se mide)
        for(int i = 0; i < size; i++){
            v[i] = rand() % 10001;
        }

        int *s = malloc(size * sizeof(int));

        int contador = 0;

        //  INICIO DEL TIEMPO (solo algoritmo)
        clock_t inicio = clock();

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

        // FIN DEL TIEMPO
        clock_t fin = clock();

        // calcular tiempo en segundos
        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        int formula = size_s * (size_s - 1) / 2;

        printf("%d, %d, %d, %f\n", size_s, contador, formula, tiempo);

        free(v);
        free(s);
    }

    return 0;
}
