#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){

    FILE *archivo = fopen("datos.csv", "r");
    if(archivo == NULL){
        printf("Error: no se pudo abrir datos.csv\n");
        return 1;
    }

    int max_datos = 100000;
    int *datos = malloc(max_datos * sizeof(int));
    int total = 0;

    // leer archivo
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

    printf("\nN,Instrucciones,Formula,Tiempo_promedio(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        int size_s = k;
        int contador = 0;
        double tiempo_total = 0;

        for(int rep = 0; rep < 30; rep++){

            int size = k;

            int *v = malloc(size * sizeof(int));
            int *s = malloc(size * sizeof(int));
            int *activo = malloc(size * sizeof(int));

            // COPIAR datos en lugar de generarlos
            for(int i = 0; i < size; i++){
                v[i] = datos[i];
                activo[i] = 1;
            }

            contador = 0;
            int elementos_restantes = size;

            clock_t inicio = clock();

            while(elementos_restantes >= 1){
                int mayor = -1;
                int indice = -1;

                for(int i = 0; i < size; i++){
                    if(activo[i] == 1){
                        contador++;

                        if(indice == -1 || v[i] > mayor){
                            mayor = v[i];
                            indice = i;
                        }
                    }
                }

                activo[indice] = 0;
                elementos_restantes--;

                s[elementos_restantes] = mayor;
            }

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            tiempo_total += tiempo;

            free(v);
            free(s);
            free(activo);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        int formula = size_s * (size_s - 1) / 2;

        printf("%d|%d|%d|%f\n", size_s, contador, formula, tiempo_promedio);
    }

    free(datos);

    return 0;
}
