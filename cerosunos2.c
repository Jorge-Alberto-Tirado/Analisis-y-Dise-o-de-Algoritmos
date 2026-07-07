#include <stdio.h>
#include <string.h>

int main(){

    char cadena[100];
    int i, j;
    int valido = 1;

    printf("Ingrese la cadena: ");
    scanf("%s", cadena);

    int n = strlen(cadena);

    for(i = 0; i < n; i++){

        if(cadena[i] == '0'){

            cadena[i] = 'X';

            for(j = n-1; j >= 0; j--){
                if(cadena[j] == '1'){
                    cadena[j] = 'X';
                    break;
                }
            }

            if(j < 0){
                valido = 0;
                break;
            }
        }
    }

    for(i = 0; i < n; i++){
        if(cadena[i] != 'X'){
            valido = 0;
        }
    }

    if(valido)
        printf("La cadena pertenece al lenguaje\n");
    else
        printf("La cadena no pertenece al lenguaje\n");

    return 0;
}
