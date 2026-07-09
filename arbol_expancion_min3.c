#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 1000
#define REPETICIONES 5

long long instrucciones = 0;

// Declarar la matriz afuera del main en el segmento global
int matriz_global[MAX][MAX];

struct Arista
{
    int origen;
    int destino;
    int peso;
};

struct Subconjunto
{
    int padre;
    int nivel;
};

int find(struct Subconjunto subconjuntos[], int vertice)
{
    instrucciones++;

    if (subconjuntos[vertice].padre != vertice)
    {
        instrucciones++;
        // Compresion de caminos para optimizar la busqueda
        subconjuntos[vertice].padre =
            find(subconjuntos,
                 subconjuntos[vertice].padre);
    }

    return subconjuntos[vertice].padre;
}

void Union(struct Subconjunto subconjuntos[],
           int x,
           int y)
{
    instrucciones++;

    int raizX = find(subconjuntos, x);
    int raizY = find(subconjuntos, y);

    // Union por rango evaluando el nivel de profundidad
    if (subconjuntos[raizX].nivel <
        subconjuntos[raizY].nivel)
    {
        subconjuntos[raizX].padre = raizY;
    }
    else if (subconjuntos[raizX].nivel >
             subconjuntos[raizY].nivel)
    {
        subconjuntos[raizY].padre = raizX;
    }
    else
    {
        subconjuntos[raizY].padre = raizX;
        subconjuntos[raizX].nivel++;
    }
}

int compararAristas(const void *a,
                    const void *b)
{
    struct Arista *a1 = (struct Arista *)a;
    struct Arista *b1 = (struct Arista *)b;

    return a1->peso - b1->peso;
}

int kruskal(int matriz[MAX][MAX],
            int vertices)
{
    struct Arista *aristas =
        malloc(vertices * vertices *
               sizeof(struct Arista));

    if (aristas == NULL)
    {
        printf("Error de memoria en aristas\n");
        exit(1);
    }

    int totalAristas = 0;

    // Recorrido de matriz triangular superior para grafos no dirigidos
    for (int i = 0; i < vertices; i++)
    {
        instrucciones++;

        for (int j = i + 1; j < vertices; j++)
        {
            instrucciones++;

            if (matriz[i][j] > 0)
            {
                instrucciones++;

                aristas[totalAristas].origen = i;
                aristas[totalAristas].destino = j;
                aristas[totalAristas].peso =
                    matriz[i][j];

                totalAristas++;
            }
        }
    }

    qsort(aristas,
          totalAristas,
          sizeof(struct Arista),
          compararAristas);

    struct Subconjunto *subconjuntos =
        malloc(vertices *
               sizeof(struct Subconjunto));

    if (subconjuntos == NULL)
    {
        printf("Error de memoria en subconjuntos\n");
        free(aristas);
        exit(1);
    }

    for (int i = 0; i < vertices; i++)
    {
        instrucciones++;

        subconjuntos[i].padre = i;
        subconjuntos[i].nivel = 0;
    }

    int aristasUsadas = 0;
    int indice = 0;
    int costoTotal = 0;

    // Construccion del Arbol de Expansion Minima
    while (aristasUsadas < vertices - 1 &&
           indice < totalAristas)
    {
        instrucciones++;

        struct Arista actual =
            aristas[indice++];

        int raizOrigen =
            find(subconjuntos,
                 actual.origen);

        int raizDestino =
            find(subconjuntos,
                 actual.destino);

        if (raizOrigen != raizDestino)
        {
            instrucciones++;

            costoTotal += actual.peso;
            aristasUsadas++;

            Union(subconjuntos,
                  raizOrigen,
                  raizDestino);
        }
    }

    free(aristas);
    free(subconjuntos);

    return costoTotal;
}

void leerCSV(char nombreArchivo[],
             int matriz[MAX][MAX])
{
    FILE *archivo =
        fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo CSV. Comprueba el nombre y la ruta.\n");
        exit(1);
    }

    char linea[20000];
    int fila = 0;

    while (fgets(linea,
                 sizeof(linea),
                 archivo) != NULL &&
           fila < MAX)
    {
        int columna = 0;

        char *token =
            strtok(linea, ",");

        while (token != NULL &&
               columna < MAX)
        {
            matriz[fila][columna] =
                atoi(token);

            token = strtok(NULL, ",");
            columna++;
        }

        fila++;
    }

    fclose(archivo);
}

double promedioSinExtremos(double tiempos[])
{
    double suma = 0.0;

    double mayor = tiempos[0];
    double menor = tiempos[0];

    for (int i = 0;
         i < REPETICIONES;
         i++)
    {
        suma += tiempos[i];

        if (tiempos[i] > mayor)
            mayor = tiempos[i];

        if (tiempos[i] < menor)
            menor = tiempos[i];
    }
    return (suma - mayor - menor) /
           (REPETICIONES - 2);
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Iniciando programa...\n");
    printf("Leyendo matriz...\n");

    leerCSV("Coordenadas.csv", matriz_global);

    printf("Matriz cargada con exito.\n");

    int inicio;
    int fin;
    int intervalo;

    printf("\nTamano inicial: ");
    scanf("%d", &inicio);

    printf("Tamano final: ");
    scanf("%d", &fin);

    printf("Intervalo: ");
    scanf("%d", &intervalo);

    // GUARDIANES DE MEMORIA: Evitan que le pidas peras al olmo
    if (inicio > MAX) {
        printf("-> Ojo: Tu maximo es %d. Ajustando inicio a %d...\n", MAX, MAX);
        inicio = MAX;
    }
    if (fin > MAX) {
        printf("-> Ojo: Tu maximo es %d. Ajustando fin a %d...\n", MAX, MAX);
        fin = MAX;
    }
    if (inicio < 2) inicio = 2; // Kruskal no puede unir 1 solo vertice
    if (fin < 2) fin = 2;
    if (intervalo <= 0) intervalo = 1; // Para evitar bucles infinitos

    FILE *salida = fopen("ResultadosKruskal.csv", "w");

    if (salida == NULL) {
        printf("Fallo al crear el archivo de resultados.\n");
        return 1;
    }

    fprintf(salida, "Vertices,Costo,Instrucciones,Tiempo_ms\n");
    printf("\n%-10s %-12s %-18s %-12s\n", "Vertices", "Costo", "Instrucciones", "Tiempo(ms)");
    printf("----------------------------------------------------------\n");

    // BUCLE INTELIGENTE
    int condicion_subida = (inicio <= fin);

    for (int vertices = inicio;
         (condicion_subida ? (vertices <= fin) : (vertices >= fin));
         (condicion_subida ? (vertices += intervalo) : (vertices -= intervalo)))
    {
        double tiempos[REPETICIONES];
        long long instruccionesProm = 0;
        int costo = 0;

        for (int r = 0; r < REPETICIONES; r++)
        {
            instrucciones = 0;
            clock_t inicioTiempo = clock();

            costo = kruskal(matriz_global, vertices);

            clock_t finTiempo = clock();

            tiempos[r] = ((double)(finTiempo - inicioTiempo) * 1000.0) / CLOCKS_PER_SEC;
            instruccionesProm += instrucciones;
        }

        instruccionesProm /= REPETICIONES;
        double tiempoPromedio = promedioSinExtremos(tiempos);

        printf("%-10d %-12d %-18lld %-12.4f\n", vertices, costo, instruccionesProm, tiempoPromedio);
        fprintf(salida, "%d,%d,%lld,%.4f\n", vertices, costo, instruccionesProm, tiempoPromedio);
    }

    fclose(salida);
    printf("\nResultados guardados con exito. Por fin.\n");

    return 0;
}
