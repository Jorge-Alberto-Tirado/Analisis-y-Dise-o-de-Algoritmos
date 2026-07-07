#include <stdio.h>
#include <string.h>

#define MAX 200

int main() {

    char A[MAX], B[MAX];

    printf("Ingresa cadena A: ");
    scanf("%s", A);

    printf("Ingresa cadena B: ");
    scanf("%s", B);

    int n = strlen(A);
    int m = strlen(B);

    int limite = (n < m) ? n : m;

    printf("\nTam\tA\t\tB\t\tBottom-Up (Iterativo)\n\n");

    for (int k = limite; k >= 1; k--) {

        char subA[MAX], subB[MAX];

        strncpy(subA, A, k);
        subA[k] = '\0';

        strncpy(subB, B, k);
        subB[k] = '\0';

        int dp[MAX][MAX];
        long long contador = 0;

        // inicializar bordes
        for (int i = 0; i <= k; i++)
            dp[i][0] = 0;

        for (int j = 0; j <= k; j++)
            dp[0][j] = 0;

        // llenar tabla
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= k; j++) {

                contador++; // contar iteraciones

                if (subA[i - 1] == subB[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = (dp[i - 1][j] > dp[i][j - 1])
                                ? dp[i - 1][j]
                                : dp[i][j - 1];
            }
        }

        printf("%d\tLCS:%d Iteraciones:%lld\n",
               k, dp[k][k], contador);
    }

    return 0;
}
