printf("\nN,Max_Tesoro,Llamadas,Tiempo\n");

for (int n = n_max; n >= 1; n -= paso) {

    double tiempos[REP];
    int resultado;

    for (int r = 0; r < REP; r++) {

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                memo[i][j] = -1;

        contador = 0;

        clock_t ini = clock();
        resultado = LT_mem(n - 1, n - 1);
        clock_t fin = clock();

        tiempos[r] = (double)(fin - ini) / CLOCKS_PER_SEC;
    }

    printf("%d,%d,%lld,%f\n", n, resultado, contador, promedio(tiempos));
}
