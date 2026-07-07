#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX 1000
#define REPETICIONES 5

long long instrucciones = 0;
int matriz_global[MAX][MAX];

// --- MIN-HEAP SIMPLIFICADO (Estilo Lazy) ---

struct MinHeapNode
{
    int v;
    int key;
};

struct MinHeap
{
    int size;
    int capacity;
    struct MinHeapNode *array;
};

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode *)malloc(capacity * sizeof(struct MinHeapNode));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode *a, struct MinHeapNode *b)
{
    instrucciones++;
    struct MinHeapNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    instrucciones++;

    if (left < minHeap->size && minHeap->array[left].key < minHeap->array[smallest].key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].key < minHeap->array[smallest].key)
        smallest = right;

    if (smallest != idx)
    {
        instrucciones++;
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Nueva funcion para aventar duplicados al Heap en O(log N)
void insert(struct MinHeap *minHeap, int v, int key)
{
    instrucciones++;
    if (minHeap->size == minHeap->capacity)
    {
        printf("Heap lleno. Esto no deberia pasar.\n");
        return;
    }

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i].v = v;
    minHeap->array[i].key = key;

    // Burbujear hacia arriba
    while (i != 0 && minHeap->array[i].key < minHeap->array[(i - 1) / 2].key)
    {
        instrucciones++;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct MinHeapNode extractMin(struct MinHeap *minHeap)
{
    instrucciones++;
    if (minHeap->size == 0)
    {
        struct MinHeapNode empty = {-1, -1};
        return empty;
    }

    if (minHeap->size == 1)
    {
        minHeap->size--;
        return minHeap->array[0];
    }

    struct MinHeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

// --- ALGORITMO DE PRIM (Con el truco de C++) ---

int primLazyHeap(int matriz[MAX][MAX], int vertices)
{
    int padre[MAX];
    int key[MAX];
    int inMST[MAX]; // Arreglo booleano para identificar basura en el heap

    // La capacidad ahora es V*V porque aventaremos duplicados
    struct MinHeap *minHeap = createMinHeap(vertices * vertices);

    for (int v = 0; v < vertices; ++v)
    {
        instrucciones++;
        padre[v] = -1;
        key[v] = INT_MAX;
        inMST[v] = 0;
    }

    key[0] = 0;
    insert(minHeap, 0, 0);

    while (minHeap->size > 0)
    {
        instrucciones++;

        struct MinHeapNode minNode = extractMin(minHeap);
        int u = minNode.v;

        // EL TRUCO MAGICO DEL C++:
        // Si el nodo ya fue procesado antes, lo ignoramos por completo
        if (inMST[u]) continue;

        inMST[u] = 1;

        for (int v = 0; v < vertices; ++v)
        {
            instrucciones++;
            if (matriz[u][v] > 0 && !inMST[v] && matriz[u][v] < key[v])
            {
                key[v] = matriz[u][v];
                padre[v] = u;
                // En vez de actualizar, simplemente insertamos un duplicado
                insert(minHeap, v, key[v]);
            }
        }
    }

    int costoTotal = 0;
    for (int i = 1; i < vertices; ++i)
    {
        if (padre[i] != -1 && matriz[i][padre[i]] > 0)
        {
            costoTotal += matriz[i][padre[i]];
        }
    }

    free(minHeap->array);
    free(minHeap);

    return costoTotal;
}

void leerCSV(char nombreArchivo[], int matriz[MAX][MAX])
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        printf("Fallo al abrir CSV.\n");
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

    printf("Iniciando programa de Prim (Version Lazy C++)...\n");
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

    FILE *salida = fopen("ResultadosPrim_Lazy.csv", "w");
    if (salida == NULL) return 1;

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
            costo = primLazyHeap(matriz_global, vertices);
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
    printf("\nResultados guardados.\n");

    return 0;
}
