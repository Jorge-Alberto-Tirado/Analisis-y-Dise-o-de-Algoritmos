#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo{
    int valor;
    struct nodo *sig;
} TNodo;
// insertar ordenado modo ascendente o descendente
void insertarOrdenado(TNodo **inicioLista, int valor, int ascendente){
    TNodo *nuevoNodo = (TNodo*)malloc(sizeof(TNodo));// esta linea devuelve una direccion de memoria y la guarda en nuevonodo
    nuevoNodo->valor = valor;//aqui le ponemos el valor al nodo
    nuevoNodo->sig = NULL; //el siguiente estara vacio
    // lista vacia
    if(*inicioLista == NULL){
        *inicioLista = nuevoNodo;//aqui el puntero deel inicio esnuevonodo
        return;
    }
    // insertar al inicio
    if(ascendente){
        if(valor <= (*inicioLista)->valor){ // si el valor es menor debe ir al inicio
            nuevoNodo->sig = *inicioLista; //el siguiente nodo se comvierte en el inicio
            *inicioLista = nuevoNodo;
            return;
        }
    } else {
        if(valor >= (*inicioLista)->valor){ //este if es poara desendente
            nuevoNodo->sig = *inicioLista;
            *inicioLista = nuevoNodo;
            return;
        }
    }

    TNodo *actual = *inicioLista; //se crea nuevo puntero auxiliar

    // recorrer lista
    while(actual->sig != NULL){
        if(ascendente){
            if(actual->sig->valor >= valor) break;
        } else {
            if(actual->sig->valor <= valor) break;
        }
        actual = actual->sig;
    }

    // insertar en medio o final
    nuevoNodo->sig = actual->sig;
    actual->sig = nuevoNodo;
}

// imprimir lista
void imprimirLista(TNodo *inicioLista){
    TNodo *actual = inicioLista;
    while(actual != NULL){
        printf("%d ", actual->valor);
        actual = actual->sig;
    }
    printf("\n");
}
int main(){
    srand(time(NULL));
    int tipo;
    printf("1 = Ascendente, 0 = Descendente: ");
    scanf("%d", &tipo);
    int numListas = 1; //rand() % 20 + 1;
    //printf("\nSe generaron %d listas:\n\n", numListas);
    for(int i = 0; i < numListas; i++){
        TNodo *lista = NULL;
        int numNodos = rand() % 20 + 1; // rango de nodos o cantidad de datos en la leista
        printf("Lista %d: ", i + 1);
        for(int j = 0; j < numNodos; j++){
            int valor = rand() % 100 + 1; // valores aleatorios miesntras quepa en nuentra lista entre 1 al 20
            insertarOrdenado(&lista, valor, tipo); // llamamos a nuetras funcion de ordenamiento
        }
        imprimirLista(lista);
    }
    return 0;
}
