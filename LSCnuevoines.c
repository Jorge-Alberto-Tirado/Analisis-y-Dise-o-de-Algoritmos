#include <stdio.h>

// contador de llamadas
long long contador = 0;

// funcion LCS con punteros
int LCSS(char *A, char *B) {
    contador++;

    // si A esta vacio
    if (A[0] == '\0')
        return 0;

    // si B esta vacio
    if (B[0] == '\0')
        return 0;

    // si coinciden
    if (A[0] == B[0])
        return 1 + LCSS(A + 1, B + 1);

    // casos
    int caso1 = LCSS(A + 1, B);
    int caso2 = LCSS(A, B + 1);

    return (caso1 > caso2) ? caso1 : caso2;
}

int main() {

    char A[100], B[100];

    printf("Ingresa string A: ");
    scanf("%s", A);

    printf("Ingresa string B: ");
    scanf("%s", B);

    contador = 0;

    int resultado = LCSS(A, B);

    printf("\nLongitud LCS: %d\n", resultado);
    printf("Numero de llamadas: %lld\n", contador);

    return 0;
}
