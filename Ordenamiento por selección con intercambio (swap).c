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

    // CICLO 1: Leer todos los datos del archivo CSV
    // Va guardando numero por numero en el arreglo "datos"
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

    // CICLO 2: Variar el tamaño del problema (k)
    // Ejemplo: 100, 200, 300...
    for(int k = paso; k <= max_n; k += paso){

        int contador = 0;
        double tiempo_total = 0;

        // CICLO 3: Repetir 30 veces para sacar promedio
        for(int rep = 0; rep < 30; rep++){

            int *v = malloc(k * sizeof(int));

            // ICLO 4: Copiar los datos base al arreglo de trabajo
            // Esto evita modificar el arreglo original
            for(int i = 0; i < k; i++){
                v[i] = datos[i];
            }

            clock_t inicio = clock();

            // CICLO 5: Algoritmo principal (selection sort por maximos)
            // En cada iteracion se coloca el mayor al final del segmento no ordenado
            for(int i = 0; i < k - 1; i++){

                int idx_max = 0;

                // CICLO 6: Buscar el elemento maximo en el rango [0, k-i)
                // Cada vuelta reduce el rango porque el final ya esta ordenado
                for(int j = 1; j < k - i; j++){
                    if(v[j] > v[idx_max]){
                        idx_max = j;
                    }
                    contador++; // contar comparaciones
                }

                // INTERCAMBIO (SWAP)
                // Se coloca el maximo en la posicion final del segmento
                int aux = v[k - 1 - i];
                v[k - 1 - i] = v[idx_max];
                v[idx_max] = aux;
            }

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            tiempo_total += tiempo;

            free(v);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        int formula = k * (k - 1) / 2;

        printf("%d|%d|%d|%f\n", k, contador, formula, tiempo_promedio);
    }

    free(datos);

    return 0;
}
