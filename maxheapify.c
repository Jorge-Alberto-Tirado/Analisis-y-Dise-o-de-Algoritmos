#include <stdio.h>

// Funcion utilitaria para intercambiar valores en memoria
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A: El arreglo de enteros
// n: El tamano actual del heap (A.heap-size en el pseudocodigo)
// i: El indice del nodo que queremos "hundir"
void maxHeapify(int A[], int n, int i) {
    int largest = i;       // Asumimos que la raiz actual es la mas grande
    int l = 2 * i + 1;     // Indice del hijo izquierdo (base 0)
    int r = 2 * i + 2;     // Indice del hijo derecho (base 0)

    // Si el hijo izquierdo existe y es mayor que el padre actual
    if (l < n && A[l] > A[largest]) {
        largest = l;
    }

    // Si el hijo derecho existe y es mayor que el "largest" actual
    if (r < n && A[r] > A[largest]) {
        largest = r;
    }

    // Si el mas grande no resulto ser el padre original
    if (largest != i) {
        // Hacemos el intercambio
        swap(&A[i], &A[largest]);

        // Llamada recursiva para arreglar el desastre en el sub-arbol
        maxHeapify(A, n, largest);
    }
}
