#include <stdio.h>

#define VERTICES 7

/*
    PROGRAMA:
    Arbol de Expansion Minima usando KRUSKAL
    con MATRIZ DE PESOS

    Vertices:
    A=0 B=1 C=2 D=3 E=4 F=5 G=6
*/



// ESTRUCTURA PARA GUARDAR UNA ARISTA


struct Arista {
    int origen;
    int destino;
    int peso;
};


// ESTRUCTURA PARA UNION-FIND

struct Subconjunto {
    int padre;
    int nivel;
};

// Funcion find Busca la raiz del conjunto


int find(struct Subconjunto subconjuntos[], int vertice) {

    // Si el padre NO es el mismo vertice
    // seguimos buscando hacia arriba
    if (subconjuntos[vertice].padre != vertice) {

        // Compresion de ruta:
        // conectamos directamente a la raiz
        subconjuntos[vertice].padre =
            find(subconjuntos,
                 subconjuntos[vertice].padre);
    }

    return subconjuntos[vertice].padre;
}



//funcion union  Une dos conjuntos


void Union(struct Subconjunto subconjuntos[],int x,int y) {

    int raizX = find(subconjuntos, x);
    int raizY = find(subconjuntos, y);

    // El arbol mas pequeño se cuelga del grande

    if (subconjuntos[raizX].nivel < subconjuntos[raizY].nivel) {

        subconjuntos[raizX].padre = raizY;
    }

    else if (subconjuntos[raizX].nivel > subconjuntos[raizY].nivel) {

        subconjuntos[raizY].padre = raizX;
    }

    // Si tienen mismo nivel
    else {

        subconjuntos[raizY].padre = raizX;

        // aumenta el nivel
        subconjuntos[raizX].nivel++;
    }
}


// FUNCION PARA ORDENAR ARISTAS
// Bubble Sort para que sea facil de entender


void ordenarAristas(struct Arista aristas[],int totalAristas) {

    for (int i = 0; i < totalAristas - 1; i++) {

        for (int j = 0; j < totalAristas - 1 - i; j++) {

            // Si la arista actual pesa mas
            // se intercambian
            if (aristas[j].peso >
                aristas[j + 1].peso) {

                struct Arista temporal;

                temporal = aristas[j];

                aristas[j] = aristas[j + 1];

                aristas[j + 1] = temporal;
            }
        }
    }
}



// FUNCION PRINCIPAL KRUSKAL


void kruskal(int matriz[VERTICES][VERTICES]) {

    /*
        Primero convertiremos la matriz
        en una lista de aristas
    */

    struct Arista aristas[50];

    int totalAristas = 0;



    // EXTRAER ARISTAS DE LA MATRIZ


    for (int i = 0; i < VERTICES; i++) {

        for (int j = i + 1; j < VERTICES; j++) {

            /*
                Si el peso es diferente de 0
                significa que SI existe conexion
            */

            if (matriz[i][j] != 0) {

                aristas[totalAristas].origen = i;

                aristas[totalAristas].destino = j;

                aristas[totalAristas].peso =
                    matriz[i][j];

                totalAristas++;
            }
        }
    }



    // ORDENAR ARISTAS POR PESO


    ordenarAristas(aristas, totalAristas);



    // CREAR SUBCONJUNTOS


    struct Subconjunto subconjuntos[VERTICES];

    for (int i = 0; i < VERTICES; i++) {

        subconjuntos[i].padre = i;

        subconjuntos[i].nivel = 0;
    }



    // AQUI GUARDAREMOS EL MST


    struct Arista resultado[VERTICES];

    int aristasUsadas = 0;

    int indice = 0;

    int costoTotal = 0;



    // ALGORITMO KRUSKAL


    while (aristasUsadas < VERTICES - 1 &&
           indice < totalAristas) {

        // Tomamos la siguiente arista mas barata
        struct Arista actual = aristas[indice];

        indice++;

        // Buscar a que conjunto pertenece cada vertice
        int raizOrigen =
            find(subconjuntos, actual.origen);

        int raizDestino =
            find(subconjuntos, actual.destino);


        /*
            Si tienen diferente raiz
            NO forman ciclo
        */

        if (raizOrigen != raizDestino) {

            resultado[aristasUsadas] = actual;

            aristasUsadas++;

            costoTotal += actual.peso;

            // Unir conjuntos
            Union(subconjuntos,
                  raizOrigen,
                  raizDestino);
        }
    }



    // IMPRIMIR RESULTADO


    printf("\n");
    printf("ARBOL DE EXPANSION MINIMA\n");
    printf("-------------------------\n");

    for (int i = 0; i < aristasUsadas; i++) {

        printf("%c -- %c == %d\n",

               resultado[i].origen + 'A',

               resultado[i].destino + 'A',

               resultado[i].peso);
    }

    printf("\nCosto Total: %d\n",
           costoTotal);
}




// FUNCION MAIN


int main() {

    /*
        MATRIZ DE PESOS

           A  B  C  D  E  F  G
    */

    int matriz[VERTICES][VERTICES] = {

    //A  B  C  D  E  F  G

      {0, 4, 3, 0, 0, 0, 0}, // A
      {4, 0, 0, 6, 5, 0, 0}, // B
      {3, 0, 0, 0, 7, 8, 0}, // C
      {0, 6, 0, 0, 2, 0, 9}, // D
      {0, 5, 7, 2, 0, 4, 6}, // E
      {0, 0, 8, 0, 4, 0, 3}, // F
      {0, 0, 0, 9, 6, 3, 0}  // G
    };


    // Ejecutar Kruskal
    kruskal(matriz);

    return 0;
}
