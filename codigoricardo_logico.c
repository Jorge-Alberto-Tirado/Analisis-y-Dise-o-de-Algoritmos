#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){
    int max_n, paso;

    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    printf("\nN,Instrucciones, Formula, Tiempo(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        int size = k;
        int size_s = size;

        int *v = malloc(size * sizeof(int));
        int *s = malloc(size * sizeof(int));

        //  CAMBIO 1: arreglo auxiliar para eliminacion logica
        int *activo = malloc(size * sizeof(int));
        // 1 = activo, 0 = eliminado

        // generar datos
        for(int i = 0; i < size; i++){
            v[i] = rand() % 10001;
            activo[i] = 1; //  CAMBIO 2: todos empiezan activos
        }

        int contador = 0;
        int elementos_restantes = size; //  CAMBIO 3: control logico

        clock_t inicio = clock();

        while(elementos_restantes >= 1){
            int mayor = -1;
            int indice = -1;
            // CAMBIO 4: buscar solo en elementos activos
            for(int i = 0; i < size; i++){
                if(activo[i] == 1){ // solo considerar activos
                    contador++;

                    if(indice == -1 || v[i] > mayor){
                        mayor = v[i];
                        indice = i;
                    }
                }
            }

            // CAMBIO 5: eliminacion logica (NO se mueve nada)
            activo[indice] = 0;

            elementos_restantes--;

            // insertar en s (igual que antes)
            s[elementos_restantes] = mayor;
        }

        clock_t fin = clock();
        double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        int formula = size_s * (size_s - 1) / 2;

        printf("%d, %d, %d, %f\n", size_s, contador, formula, tiempo);

        free(v);
        free(s);
        free(activo); // CAMBIO 6: liberar nuevo arreglo
    }

    return 0;
}
