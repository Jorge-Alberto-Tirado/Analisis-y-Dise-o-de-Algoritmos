#include <stdio.h>
#include <string.h>
int main(){
    char cadena[100];
    char pila[100];
    int top = -1;
   printf("Ingrese la cadena: ");
    scanf("%s", cadena);
    int n = strlen(cadena);
    //filtro 1 detecta cuando la cadena es numero impar
    if(n % 2 != 0){
    printf("La cadena NO pertenece al lenguaje\n");
    return 0;
    }
    int fase = 0;
    for(int i = 0; i < n; i++){
        if(cadena[i] == '0' && fase == 0){
            top++;
            pila[top] = '0';
        }
        else if(cadena[i] == '1'){
            fase = 1;
    //filtro 2 este detecta cuando la cadena inicia en 1
            if(top == -1){
                printf("La cadena no pertenece al lenguaje\n");
                return 0;
            }
            top--;
        }
        else{
                //filtro 3 detecta cuando tiene un cero despues del 1
            printf("La cadena no pertenece al lenguaje\n");
            return 0;
        }
    }
    //filtro 4  se verifica la pila vacia
    if(top == -1)
        printf("La cadena pertenece al lenguaje\n");
    else
        printf("La cadena no pertenece al lenguaje\n");
    return 0;
}
