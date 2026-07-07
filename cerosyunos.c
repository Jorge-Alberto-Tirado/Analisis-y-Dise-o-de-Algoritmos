#include <stdio.h>
#include <string.h>

int main(){

    char cadena[100];
    int ceros = 0;
    int unos = 0;
    int cambio = 0;

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    for(int i = 0; i < strlen(cadena); i++){

        if(cadena[i] == '0' && cambio == 0){
            ceros++;
        }
        else if(cadena[i] == '1'){
            cambio = 1;
            unos++;
        }
        else{
            printf("La cadena no pertenece al lenguaje\n");
            return 0;
        }

        if(cambio == 1 && cadena[i] == '0'){
            printf("La cadena no pertenece al lenguaje\n");
            return 0;
        }
    }

    if(ceros == unos && ceros > 0){
        printf("La cadena pertenece al lenguaje\n");
    }
    else{
        printf("La cadena no pertenece al lenguaje\n");
    }

    return 0;
}
