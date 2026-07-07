#include <stdio.h>
#include <string.h>

#define MAX 200

// memo y contador
int memo[MAX][MAX];
long long contador = 0;

// LCS con memoizacion (top-down)
int LCS_mem(char A[], char B[], int i, int j) {
    contador++;

    if (i == 0 || j == 0)
        return 0;

    if (memo[i][j] != -1)
        return memo[i][j];

    if (A[i - 1] == B[j - 1])
        memo[i][j] = 1 + LCS_mem(A, B, i - 1, j - 1);
    else {
        int x = LCS_mem(A, B, i - 1, j);
        int y = LCS_mem(A, B, i, j - 1);
        memo[i][j] = (x > y) ? x : y;
    }

    return memo[i][j];
}

int main() {

    char A[MAX], B[MAX];

    printf("Ingresa cadena A: ");
    scanf("%s", A);

    printf("Ingresa cadena B: ");
    scanf("%s", B);

    int n = strlen(A);
    int m = strlen(B);

    int limite = (n < m) ? n : m;

    printf("\nTam\tA\t\tB\t\tTop-Down (Memoizacion)\n\n");

    for (int k = limite; k >= 1; k--) {

        char subA[MAX], subB[MAX];

        strncpy(subA, A, k);
        subA[k] = '\0';

        strncpy(subB, B, k);
        subB[k] = '\0';

        // inicializar memo
        for (int i = 0; i <= k; i++)
            for (int j = 0; j <= k; j++)
                memo[i][j] = -1;

        contador = 0;

        int lcs = LCS_mem(subA, subB, k, k);

        printf("%d\tLCS:%d Llamadas:%lld\n",
               k, lcs, contador);
    }

    return 0;
}
