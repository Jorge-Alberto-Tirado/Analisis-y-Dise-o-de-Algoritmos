#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Nodo {
    char caracter;
    unsigned frecuencia;
    struct Nodo *izq, *der;
};
struct MinHeap {
    unsigned tamano;
    unsigned capacidad;
    struct Nodo** arreglo;
};
struct Nodo* nuevoNodo(char caracter, unsigned frecuencia) {
    struct Nodo* temp = (struct Nodo*)malloc(sizeof(struct Nodo));
    // Validacion de memoria
    if (!temp) {
        fprintf(stderr, "Error: Memoria insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    temp->caracter = caracter;
    temp->frecuencia = frecuencia;
    temp->izq = temp->der = NULL;
    return temp;
}
void intercambiarNodos(struct Nodo** a, struct Nodo** b) {
    struct Nodo* t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct MinHeap* minHeap, int idx) {
    int masPequeno = idx;
    int izq = 2 * idx + 1;
    int der = 2 * idx + 2;
    if (izq < minHeap->tamano && 
        minHeap->arreglo[izq]->frecuencia < minHeap->arreglo[masPequeno]->frecuencia) {
        masPequeno = izq;
    }
    if (der < minHeap->tamano && 
        minHeap->arreglo[der]->frecuencia < minHeap->arreglo[masPequeno]->frecuencia) {
        masPequeno = der;
    }
    if (masPequeno != idx) {
        intercambiarNodos(&minHeap->arreglo[masPequeno], &minHeap->arreglo[idx]);
        minHeapify(minHeap, masPequeno);
    }
}
struct Nodo* extraerMinimo(struct MinHeap* minHeap) {
    struct Nodo* temp = minHeap->arreglo[0];
    
    minHeap->arreglo[0] = minHeap->arreglo[minHeap->tamano - 1];
    --minHeap->tamano;
    
    minHeapify(minHeap, 0);
    
    return temp;
}
void insertarMinHeap(struct MinHeap* minHeap, struct Nodo* minHeapNodo) {
    ++minHeap->tamano;
    int i = minHeap->tamano - 1;
    while (i && minHeapNodo->frecuencia < minHeap->arreglo[(i - 1) / 2]->frecuencia) {
        minHeap->arreglo[i] = minHeap->arreglo[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    
    minHeap->arreglo[i] = minHeapNodo;
}
struct MinHeap* crearYConstruirMinHeap(char caracter[], unsigned frecuencia[], int tamano) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (!minHeap) exit(EXIT_FAILURE);
    
    minHeap->tamano = tamano;
    minHeap->capacidad = tamano;
    minHeap->arreglo = (struct Nodo**)malloc(tamano * sizeof(struct Nodo*));
    if (!minHeap->arreglo) exit(EXIT_FAILURE);

    for (int i = 0; i < tamano; ++i) {
        minHeap->arreglo[i] = nuevoNodo(caracter[i], frecuencia[i]);
    }

    int n = minHeap->tamano - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }

    return minHeap;
}

struct Nodo* construirArbolHuffman(char caracter[], unsigned frecuencia[], int tamano) {
    struct Nodo *izq, *der, *padre;

    struct MinHeap* minHeap = crearYConstruirMinHeap(caracter, frecuencia, tamano);

    while (minHeap->tamano != 1) {
        izq = extraerMinimo(minHeap);
        der = extraerMinimo(minHeap);

        padre = nuevoNodo('$', izq->frecuencia + der->frecuencia);
        padre->izq = izq;
        padre->der = der;

        insertarMinHeap(minHeap, padre);
    }

    struct Nodo* raiz = extraerMinimo(minHeap);
    
    free(minHeap->arreglo);
    free(minHeap);
    
    return raiz;
}

int procesarArchivoTexto(const char* nombreArchivo, char caracteresActivos[], unsigned frecuenciasActivas[], unsigned *totalCaracteresOriginales) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s.\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }

    unsigned frecuenciasGlobales[256] = {0};
    int c;
    *totalCaracteresOriginales = 0;

    while ((c = fgetc(archivo)) != EOF) {
        frecuenciasGlobales[c]++;
        (*totalCaracteresOriginales)++;
    }
    
    fclose(archivo);

    int tamano = 0;
    for (int i = 0; i < 256; i++) {
        if (frecuenciasGlobales[i] > 0) {
            caracteresActivos[tamano] = (char)i;
            frecuenciasActivas[tamano] = frecuenciasGlobales[i];
            tamano++;
        }
    }
    
    return tamano;
}

char diccionario[256][256] = {0};

void generarDiccionario(struct Nodo* raiz, char* codigoActual, int profundidad) {
    if (!raiz) return;

    if (!(raiz->izq) && !(raiz->der)) {
        codigoActual[profundidad] = '\0'; // Terminamos la cadena
        strcpy(diccionario[(unsigned char)raiz->caracter], codigoActual);
        return;
    }

    codigoActual[profundidad] = '0';
    generarDiccionario(raiz->izq, codigoActual, profundidad + 1);

    codigoActual[profundidad] = '1';
    generarDiccionario(raiz->der, codigoActual, profundidad + 1);
}
void comprimirYGuardar(const char* archivoEntrada, const char* archivoSalida, 
                       char caracteres[], unsigned frecuencias[], 
                       int tamanoAlfabeto, unsigned totalCaracteres) {
    
    FILE* in = fopen(archivoEntrada, "r");
    FILE* out = fopen(archivoSalida, "wb");
    if (!in || !out) exit(EXIT_FAILURE);

    fwrite(&totalCaracteres, sizeof(unsigned), 1, out);
    
    fwrite(&tamanoAlfabeto, sizeof(int), 1, out);
    
    for (int i = 0; i < tamanoAlfabeto; i++) {
        fwrite(&caracteres[i], sizeof(char), 1, out);
        fwrite(&frecuencias[i], sizeof(unsigned), 1, out);
    }

    unsigned char buffer = 0;
    int bitsEnBuffer = 0;
    int c;

    while ((c = fgetc(in)) != EOF) {
        char* codigo = diccionario[c];
        
        for (int i = 0; codigo[i] != '\0'; i++) {
            buffer = buffer << 1;
            
            if (codigo[i] == '1') {
                buffer = buffer | 1; 
            }
            bitsEnBuffer++;

            if (bitsEnBuffer == 8) {
                fwrite(&buffer, sizeof(unsigned char), 1, out);
                buffer = 0;
                bitsEnBuffer = 0;
            }
        }
    }

    if (bitsEnBuffer > 0) {
        buffer = buffer << (8 - bitsEnBuffer);
        fwrite(&buffer, sizeof(unsigned char), 1, out);
    }

    fclose(in);
    fclose(out);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Error. Uso correcto: %s <archivo_original> <archivo_comprimido>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char caracteresActivos[55];
    unsigned frecuenciasActivas[55];
    unsigned totalCaracteres = 0;

    int tamanoAlfabeto = procesarArchivoTexto(argv[1], caracteresActivos, frecuenciasActivas, &totalCaracteres);

    if (tamanoAlfabeto == 0) {
        fprintf(stderr, "El archivo esta mas vacio que mis esperanzas de encontrar codigo sin bugs.\n");
        return EXIT_FAILURE;
    }

    struct Nodo* raiz = construirArbolHuffman(caracteresActivos, frecuenciasActivas, tamanoAlfabeto);

    char bufferCodigo[256];
    generarDiccionario(raiz, bufferCodigo, 0);

    comprimirYGuardar(argv[1], argv[2], caracteresActivos, frecuenciasActivas, tamanoAlfabeto, totalCaracteres);

    printf("Exito. Mensaje codificado y guardado en: %s\n", argv[2]);

    return EXIT_SUCCESS;
}
