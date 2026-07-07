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

void minHeapify(struct MinHeap* minHeap, unsigned int idx) {
    unsigned int masPequeno = idx;
    unsigned int izq = 2 * idx + 1;
    unsigned int der = 2 * idx + 2;

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


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso correcto: %s <archivo_codificado.bin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* in = fopen(argv[1], "rb");
    if (!in) {
        fprintf(stderr, "Error: No se pudo abrir el archivo %s.\n", argv[1]);
        return EXIT_FAILURE;
    }

    unsigned int totalCaracteresOriginales;
    int tamanoAlfabeto;

    fread(&totalCaracteresOriginales, sizeof(unsigned int), 1, in);
    fread(&tamanoAlfabeto, sizeof(int), 1, in);

    if (tamanoAlfabeto == 0 || totalCaracteresOriginales == 0) {
        fclose(in);
        return EXIT_SUCCESS;
    }

    char caracteres[55];
    unsigned int frecuencias[55];

    for (int i = 0; i < tamanoAlfabeto; i++) {
        fread(&caracteres[i], sizeof(char), 1, in);
        fread(&frecuencias[i], sizeof(unsigned int), 1, in);
    }

    struct Nodo* raiz = construirArbolHuffman(caracteres, frecuencias, tamanoAlfabeto);
    struct Nodo* nodoActual = raiz;

    unsigned char byte;
    unsigned int caracteresImpresos = 0;

    while (fread(&byte, sizeof(unsigned char), 1, in) == 1) {

        for (int i = 7; i >= 0; i--) {

            int bit = (byte >> i) & 1;

            if (bit == 0) {
                nodoActual = nodoActual->izq;
            } else {
                nodoActual = nodoActual->der;
            }

            if (!(nodoActual->izq) && !(nodoActual->der)) {
                
                putchar(nodoActual->caracter);
                caracteresImpresos++;
                
                nodoActual = raiz;

                if (caracteresImpresos == totalCaracteresOriginales) {
                    break;
                }
            }
        }
        
        if (caracteresImpresos == totalCaracteresOriginales) {
            break;
        }
    }

    printf("\n");

    fclose(in);
    return EXIT_SUCCESS;
}