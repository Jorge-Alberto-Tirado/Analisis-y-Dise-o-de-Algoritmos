#include <stdio.h>   // Biblioteca para printf
#include <stdlib.h>  // Biblioteca para malloc, free y atoi

// ================= ESTRUCTURA DEL NODO =================

// Cada nodo representa un elemento de la cola de prioridad
struct Nodo {

    // Informacion principal
    int dato;

    // Nivel de prioridad
    // Entre menor numero, mayor prioridad
    // Ejemplo:
    // 1 = urgente
    // 5 = poco urgente
    int prioridad;

    // Apuntador al siguiente nodo
    struct Nodo* siguiente;
};

// ================= INSERTAR CON PRIORIDAD =================

// Inserta un nodo manteniendo el orden de prioridades
void insertarConPrioridad(struct Nodo** cabeza, int dato, int prioridad) {

    // ================= CREACION DEL NUEVO NODO =================

    // malloc reserva memoria dinamica en RAM
    // sizeof(struct Nodo) calcula cuantos bytes ocupa un nodo
    struct Nodo* nuevoNodo =
        (struct Nodo*)malloc(sizeof(struct Nodo));

    // Guardamos el dato recibido
    nuevoNodo->dato = dato;

    // Guardamos la prioridad recibida
    nuevoNodo->prioridad = prioridad;

    // Inicialmente no apunta a nadie
    nuevoNodo->siguiente = NULL;

    // ================= CASO 1 =================
    // Lista vacia o el nuevo nodo tiene mayor prioridad

    // *cabeza == NULL
    // significa que la lista esta vacia

    // prioridad < (*cabeza)->prioridad
    // significa que el nuevo nodo es mas importante
    // que el actual primero

    if (*cabeza == NULL ||
        prioridad < (*cabeza)->prioridad) {

        // El nuevo nodo apunta a la antigua cabeza
        nuevoNodo->siguiente = *cabeza;

        // Ahora el nuevo nodo se convierte en cabeza
        *cabeza = nuevoNodo;

        return;
    }

    // ================= CASO 2 =================
    // Buscar la posicion correcta

    // Nodo auxiliar para recorrer la lista
    struct Nodo* actual = *cabeza;

    // Recorremos mientras:
    // 1. exista siguiente nodo
    // 2. la prioridad siguiente sea menor o igual

    while (actual->siguiente != NULL &&
           actual->siguiente->prioridad <= prioridad) {

        // Avanzamos al siguiente nodo
        actual = actual->siguiente;
    }

    // ================= INSERCION =================

    // El nuevo nodo apunta al siguiente de actual
    nuevoNodo->siguiente = actual->siguiente;

    // Actual ahora apunta al nuevo nodo
    actual->siguiente = nuevoNodo;
}

// ================= EXTRAER PRIORITARIO =================

// Extrae el nodo con mayor prioridad
int extraerPrioritario(struct Nodo** cabeza) {

    // Verificamos si esta vacia
    if (*cabeza == NULL) {

        printf("Error: La cola de prioridad esta vacia.\n");

        return -1;
    }

    // Guardamos temporalmente la cabeza
    struct Nodo* temp = *cabeza;

    // Respaldamos el dato
    int datoExtraido = temp->dato;

    // Movemos cabeza al siguiente nodo
    *cabeza = (*cabeza)->siguiente;

    // Liberamos memoria RAM
    free(temp);

    // Retornamos el dato
    return datoExtraido;
}

// ================= IMPRIMIR LISTA =================

// Imprime toda la lista
void imprimirLista(struct Nodo* cabeza) {

    // Nodo auxiliar para recorrer
    struct Nodo* actual = cabeza;

    // Mientras no lleguemos al final
    while (actual != NULL) {

        // Mostramos informacion del nodo
        printf("[Dato: %d | Prio: %d] -> ",
               actual->dato,
               actual->prioridad);

        // Avanzamos
        actual = actual->siguiente;
    }

    // Fin de lista
    printf("NULL\n");
}

// ================= LIBERAR MEMORIA =================

// Elimina toda la lista de memoria
void liberarLista(struct Nodo* cabeza) {

    struct Nodo* temp;

    while (cabeza != NULL) {

        // Guardamos el nodo actual
        temp = cabeza;

        // Avanzamos al siguiente
        cabeza = cabeza->siguiente;

        // Liberamos RAM
        free(temp);
    }
}

// ================= FUNCION PRINCIPAL =================

int main(int argc, char *argv[]) {

    // argc = cantidad de argumentos
    // argv = arreglo de cadenas

    // ================= FORMATO DE ENTRADA =================

    // Ejemplo:
    //
    // ./cola 500 3 100 1 900 5 200 1
    //
    // dato prioridad dato prioridad ...

    // Validamos cantidad minima
    if (argc < 3 || argc % 2 == 0) {

        printf("Uso:\n");

        printf("%s dato prioridad dato prioridad ...\n",
               argv[0]);

        return 1;
    }

    // Cabeza inicial vacia
    struct Nodo* miColaVIP = NULL;

    // ================= LEER ARGUMENTOS =================

    // Recorremos de dos en dos:
    // i     = dato
    // i + 1 = prioridad

    for (int i = 1; i < argc; i += 2) {

        // Convertimos texto a entero
        int dato = atoi(argv[i]);

        // Convertimos prioridad
        int prioridad = atoi(argv[i + 1]);

        // Insertamos ordenadamente
        insertarConPrioridad(
            &miColaVIP,
            dato,
            prioridad
        );
    }

    // ================= MOSTRAR RESULTADO =================

    printf("Estado de la Cola VIP:\n");

    imprimirLista(miColaVIP);

    // ================= EXTRAER PRIORITARIO =================

    printf("\nAtendiendo al cliente mas prioritario:\n");

    int atendido =
        extraerPrioritario(&miColaVIP);

    printf("Se extrajo el dato: %d\n",
           atendido);

    // ================= MOSTRAR ESTADO FINAL =================

    printf("\nEstado restante:\n");

    imprimirLista(miColaVIP);

    // ================= LIBERAR MEMORIA =================

    liberarLista(miColaVIP);

    return 0;
}
