#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso correcto: %s <numero_limite>\n", argv[0]);
        return 1;
    }
    int limite = atoi(argv[1]);    
    if (limite < 2) {
        printf("No existen numeros primos menores que 2.\n");
        return 0;
    }

    // Asignar memoria dinamica usando calloc (Usamos calloc porque inicializa todos los bytes en 0 automaticamente) 0 primo 1 no primo
    int *es_primo = (int *)calloc(limite + 1, sizeof(int));
    if (es_primo == NULL) {
        printf("Error No se pudo asignar memoria.\n");
        return 1;
    }

    // Implementar la Criba de Eratostenes y descartamos el 0 y el 1 por definicion matematica
    es_primo[0] = 1;
    es_primo[1] = 1;

    for (int p = 2; p * p <= limite; p++) {  // Si es_primo "p" no ha sido modificado, entonces es primo
        
        if (es_primo[p] == 0) {    // Marcar todos los multiplos de p como NO primos
            
            for (int i = p * p; i <= limite; i += p) {
                es_primo[i] = 1;
            }
        }
    }

    printf("Numeros primos encontrados hasta el %d:\n", limite);
    for (int p = 2; p <= limite; p++) {
        if (es_primo[p] == 0) {
            printf("%d ", p);
        }
    }
    printf("\n");
    free(es_primo);

    return 0;
}