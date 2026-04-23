#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    //  leer archivo una sola vez
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

    printf("\nN,Instrucciones,Formula,Tiempo_promedio(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        int size_s = k;
        int contador = 0;
        double tiempo_total = 0;

        //  repetir 30 veces
        for(int rep = 0; rep < 30; rep++){

            int size = k;

            int *v = malloc(size * sizeof(int));
            int *s = malloc(size * sizeof(int));

            // copiar datos del archivo
            for(int i = 0; i < size; i++){
                v[i] = datos[i];
            }

            contador = 0;

            clock_t inicio = clock();

            while(size >= 1){

                int mayor = v[0];
                int indice = 0;

                for(int i = 1; i < size; i++){
                    if(v[i] > mayor){
                        mayor = v[i];
                        indice = i;
                    }
                    contador++;
                }

                //  BORRADO LOGICO (swap con ultimo)
                v[indice] = v[size - 1];

                // guardar en S
                size--;
                s[size] = mayor;
            }

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            tiempo_total += tiempo;

            free(v);
            free(s);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        //int formula = size_s * (size_s - 1) / 2;

        printf("%d,%d,%f\n", size_s, contador, tiempo_promedio);
    }

    free(datos);

    return 0;
}
