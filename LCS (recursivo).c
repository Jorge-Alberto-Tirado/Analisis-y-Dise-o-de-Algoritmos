#include <stdio.h>
#include <string.h>

// contador global
long long contador = 0;

// funcion LCS recursiva
int LCS(char A[], char B[], int i, int j) {
    contador++;

    // caso base
    if (i == 0 || j == 0)
        return 0;

    // si coinciden
    if (A[i - 1] == B[j - 1])
        return 1 + LCS(A, B, i - 1, j - 1);

    // si no coinciden
    int x = LCS(A, B, i - 1, j);
    int y = LCS(A, B, i, j - 1);

    return (x > y) ? x : y;
}

// ----------- MAIN -----------
int main() {

    char A[100], B[100];

    printf("Ingresa string A: ");
    scanf("%s", A);

    printf("Ingresa string B: ");
    scanf("%s", B);

    int n = strlen(A);
    int m = strlen(B);

    contador = 0;

    int resultado = LCS(A, B, n, m);

    printf("\nLongitud LCS: %d\n", resultado);
    printf("Numero de llamadas a la funcion: %lld\n", contador);

    return 0;
}
