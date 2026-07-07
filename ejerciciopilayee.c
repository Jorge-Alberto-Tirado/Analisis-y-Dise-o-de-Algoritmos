#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

                                            // empieza esctuctura pila
struct Pila {
    int tope;
    char items[MAX];                        //arreglo de caracvteres
};
void push(struct Pila *p, char c) {         //aqui metemos los datos
    if (p->tope < MAX - 1) {                //verificamos que no este llena
        p->items[++(p->tope)] = c;          //incrementa trope y guarda datos
    }
}
char pop(struct Pila *p) {
    if (p->tope >= 0) {                    // otra vez verifica que no este vacia
        return p->items[(p->tope)--];      //deviuelve valor de la pila y decrementa
    }
    return '\0';
}
bool reconocerLenguajeX(char *cadena) {     //recibe una cadena y regreas true o false
    struct Pila pila;
    pila.tope = -1;
    int i = 0;                              //indice que recorre cadena
    int n = strlen(cadena);
                                            // Leer la parte L y meterla a la pila
    while (i < n && cadena[i] != ':') {     //recorre la cadena hasta encontrar los dos puntos
        push(&pila, cadena[i]);
        i++;
    }
                                            // Si no se encontro el separador o L esta vacio
    if (i == n || i == 0) {
        return false;
    }
                                            // Saltamos el caracter ':'
    i++;
                                            //  Comparar la parte R con lo que sale de la pila
    while (i < n) {
        char caracterPila = pop(&pila);     //saca lo ultimo que encontro
        if (cadena[i] != caracterPila) {
            return false;                   // No es el inverso
        }
        i++;
    }
                                            // Si la pila esta vacia, la secuencia es correcta
    return (pila.tope == -1);                //potr tercera vez revisamos que este vacia la pila
}
int main() {
    char secuencia[MAX];
    printf("Ingrese la secuencia del lenguaje X: ");
    scanf("%s", secuencia);

    if (reconocerLenguajeX(secuencia)) {
        printf("Esta SI es la secuencia\n");
    } else {
        printf("Esta NO es la secuencia\n");
    }
    return 0;
}
