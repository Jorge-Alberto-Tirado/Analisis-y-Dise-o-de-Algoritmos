#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 
#include <time.h>

#define MAX 1000
#define REPETICIONES 5

long long instrucciones = 0;
int matriz_global[MAX][MAX];

// Funcion que representa el EXTRACT-MIN(Q)
// Busca linealmente el vertice con la distancia minima que no este en el arbol
int extractMin(int key[], int inMST[], int vertices)
{
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < vertices; v++)
    {
        instrucciones++; // Contamos cada comparacion

        // Si el vertice v sigue en Q (inMST == 0) y su peso es menor al minimo actual
        if (inMST[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

int prim(int matriz[MAX][MAX], int vertices)
{
    // pi[u]: Almacena el arbol final
    int padre[MAX];

    // key[u]: Almacena el peso minimo para conectar el nodo
    int key[MAX];

    // Nuestro conjunto Q. 0 = esta en Q, 1 = ya lo sacamos
    int inMST[MAX];

    // Inicializar todo en infinito
    for (int i = 0; i < vertices; i++)
    {
        instrucciones++;
        key[i] = INT_MAX;
        inMST[i] = 0;
        padre[i] = -1; // NIL
    }

    //El nodo raiz es el primero (indice 0)
    key[0] = 0;

    //Bucle principal. Iteramos vertices - 1 veces porque el MST de V vertices siempre tiene V-1 aristas.
    for (int count = 0; count < vertices - 1; count++)
    {
        //Extraer el nodo u con la menor llave de Q
        int u = extractMin(key, inMST, vertices);

        // Validacion por si el grafo es disconexo y no hay mas aristas
        if (u == -1) break;

        // Lo sacamos de Q
        inMST[u] = 1;

        //Actualizar las llaves de los vertices adyacentes a u
        for (int v = 0; v < vertices; v++)
        {
            instrucciones++;

            // Evaluamos:
            // 1. Si hay arista entre u y v (matriz[u][v] > 0)
            // 2. Si el vertice v sigue en Q (inMST[v] == 0)
            // 3. Si el peso de esta arista es MENOR a la llave que tenia guardada v
            if (matriz[u][v] > 0 && inMST[v] == 0 && matriz[u][v] < key[v])
            {
                padre[v] = u;         // Linea 10: pi[v] = u
                key[v] = matriz[u][v]; // Linea 11: key[v] = w(u,v)
            }
        }
    }

    // Calcular el costo total sumando las aristas elegidas
    int costoTotal = 0;
    for (int i = 1; i < vertices; i++)
    {
        if (padre[i] != -1 && matriz[i][padre[i]] > 0)
        {
            costoTotal += matriz[i][padre[i]];
        }
    }

    return costoTotal;
}

// Reutilizamos lector de CSV
void leerCSV(char nombreArchivo[], int matriz[MAX][MAX])
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo CSV. Seguro lo borraste.\n");
        exit(1);
    }

    char linea[20000];
    int fila = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL && fila < MAX)
    {
        int columna = 0;
        char *token = strtok(linea, ",");

        while (token != NULL && columna < MAX)
        {
            matriz[fila][columna] = atoi(token);
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

    for (int i = 0; i < REPETICIONES; i++)
    {
        suma += tiempos[i];
        if (tiempos[i] > mayor) mayor = tiempos[i];
        if (tiempos[i] < menor) menor = tiempos[i];
    }
    return (suma - mayor - menor) / (REPETICIONES - 2);
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Iniciando programa de Prim (Version Lineal)...\n");
    printf("Leyendo matriz...\n");

    leerCSV("Coordenadas.csv", matriz_global);

    printf("Matriz cargada.\n");

    int inicio, fin, intervalo;

    printf("\nTamano inicial: ");
    scanf("%d", &inicio);

    printf("Tamano final: ");
    scanf("%d", &fin);

    printf("Intervalo: ");
    scanf("%d", &intervalo);

    if (inicio > MAX) { printf("Ajustando inicio a %d...\n", MAX); inicio = MAX; }
    if (fin > MAX) { printf("Ajustando fin a %d...\n", MAX); fin = MAX; }
    if (inicio < 2) inicio = 2;
    if (fin < 2) fin = 2;
    if (intervalo <= 0) intervalo = 1;

    FILE *salida = fopen("ResultadosPrim_Lineal.csv", "w");

    if (salida == NULL) {
        printf("Fallo al crear el archivo de resultados.\n");
        return 1;
    }

    fprintf(salida, "Vertices,Costo,Instrucciones,Tiempo_ms\n");
    printf("\n%-10s %-12s %-18s %-12s\n", "Vertices", "Costo", "Instrucciones", "Tiempo(ms)");
    printf("----------------------------------------------------------\n");

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

            costo = prim(matriz_global, vertices);

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
    printf("\nResultados guardados en ResultadosPrim_Lineal.csv. Tu procesador te saluda.\n");

    return 0;
}
