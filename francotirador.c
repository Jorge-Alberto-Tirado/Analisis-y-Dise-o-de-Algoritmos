#include <stdio.h>
#include <stdlib.h>


#define MAX 10

// ================= ESTRUCTURA DE LA COLA =================

// Definicion de la estructura de la cola circular
typedef struct {

    // Arreglo donde se guardan los elementos
    int elementos[MAX];

    // Indice del primer elemento
    int frente;

    // Indice del ultimo elemento insertado
    int final;

} TCola;

// ================= FUNCIONES BASICAS =================

// Inicializa la cola
void inicializarCola(TCola* cola) {

    // -1 significa que la cola esta vacia
    cola->frente = -1;

    // -1 significa que no existe ultimo elemento
    cola->final = -1;
}

// Verifica si la cola esta vacia
int colaVacia(TCola* cola) {

    // Si frente vale -1, no hay elementos
    if (cola->frente == -1) {
        return 1; // verdadero
    }

    // En otro caso no esta vacia
    return 0;
}

// Verifica si la cola esta llena
int colaLlena(TCola* cola) {

    // Formula circular:
    // si avanzar final una posicion hace que choque con frente
    // entonces la cola esta llena
    if ((cola->final + 1) % MAX == cola->frente) {
        return 1;
    }

    return 0;
}

// ================= INSERTAR ELEMENTOS =================

// Inserta un elemento al final de la cola
void encolar(TCola* cola, int dato) {

    // Verificamos si ya no cabe nada
    if (colaLlena(cola)) {

        printf("Error: La cola esta llena.\n");

        // Salimos de la funcion
        return;
    }

    // Si la cola estaba vacia
    if (cola->frente == -1) {

        // El frente inicia en 0
        cola->frente = 0;
    }

    // Avanzamos el indice final de forma circular
    // Ejemplo:
    // si final esta en 9 y MAX es 10:
    // (9 + 1) % 10 = 0
    cola->final = (cola->final + 1) % MAX;

    // Guardamos el dato en la nueva posicion
    cola->elementos[cola->final] = dato;
}

// ================= ELIMINAR ELEMENTOS =================

// Saca el elemento del frente
int desencolar(TCola* cola) {

    // Si no hay elementos
    if (colaVacia(cola)) {

        printf("Error: La cola esta vacia.\n");

        return -1;
    }

    // Guardamos temporalmente el elemento frontal
    int dato = cola->elementos[cola->frente];

    // Si solo habia un elemento
    if (cola->frente == cola->final) {

        // Reiniciamos la cola completamente
        cola->frente = -1;
        cola->final = -1;

    } else {

        // Avanzamos el frente circularmente
        cola->frente = (cola->frente + 1) % MAX;
    }

    // Retornamos el elemento eliminado
    return dato;
}

// ================= EXTRACCION SELECTIVA =================

// Elimina todas las apariciones de un valor
void extraerSelectivo(TCola* original, int valorABorrar) {

    // Cola auxiliar temporal
    TCola auxiliar;

    // Inicializamos la auxiliar vacia
    inicializarCola(&auxiliar);

    // Variable temporal
    int datoTemporal;

    // Mientras existan elementos
    while (!colaVacia(original)) {

        // Sacamos un dato de la cola original
        datoTemporal = desencolar(original);

        // Si NO es el valor a eliminar
        if (datoTemporal != valorABorrar) {

            // Lo conservamos en la auxiliar
            encolar(&auxiliar, datoTemporal);
        }

        // Si si es el valor, simplemente no se guarda
    }

    // Regresamos los sobrevivientes a la cola original
    while (!colaVacia(&auxiliar)) {

        // Sacamos de auxiliar y metemos a original
        encolar(original, desencolar(&auxiliar));
    }
}

// ================= IMPRIMIR COLA =================

// Imprime la cola sin destruirla
void imprimirCola(TCola* cola) {

    // Cola auxiliar para respaldar los datos
    TCola auxiliar;

    // Inicializamos auxiliar
    inicializarCola(&auxiliar);

    // Variable temporal
    int dato;

    printf("Contenido de la cola: ");

    // Mientras existan elementos
    while (!colaVacia(cola)) {

        // Sacamos elemento
        dato = desencolar(cola);

        // Lo imprimimos
        printf("%d ", dato);

        // Lo guardamos temporalmente
        encolar(&auxiliar, dato);
    }

    // Restauramos la cola original
    while (!colaVacia(&auxiliar)) {

        encolar(cola, desencolar(&auxiliar));
    }

    printf("\n");
}

// ================= FUNCION PRINCIPAL =================

int main(int argc, char *argv[]) {

    // argc = cantidad de argumentos
    // argv = arreglo de cadenas

    // Ejemplo:
    // ./cola 99 10 99 20
    //
    // argv[0] = "./cola"
    // argv[1] = "99"
    // argv[2] = "10"
    // argv[3] = "99"
    // argv[4] = "20"

    // Verificamos que existan suficientes parametros
    if (argc < 3) {

        printf("Uso: %s valorABorrar elemento1 elemento2 ...\n", argv[0]);

        return 1;
    }

    // Declaramos la cola principal
    TCola miCola;

    // Inicializamos la cola vacia
    inicializarCola(&miCola);

    // Convertimos el primer parametro a entero
    // Este sera el valor que queremos eliminar
    int valorABorrar = atoi(argv[1]);

    // Recorremos los elementos recibidos
    for (int i = 2; i < argc; i++) {

        // Validamos no exceder capacidad
        if (i - 2 >= MAX) {

            printf("Error: Se excedio el tamano maximo de la cola (%d).\n", MAX);

            break;
        }

        // Convertimos texto a entero
        int numero = atoi(argv[i]);

        // Insertamos en la cola
        encolar(&miCola, numero);
    }

    // Mostramos la cola original
    printf("Cola original:\n");

    imprimirCola(&miCola);

    // Mensaje informativo
    printf("\nExtrayendo el valor %d...\n", valorABorrar);

    // Eliminamos el valor indicado
    extraerSelectivo(&miCola, valorABorrar);

    // Mostramos resultado final
    printf("\nCola despues de la extraccion:\n");

    imprimirCola(&miCola);

    // Fin correcto del programa
    return 0;
}
