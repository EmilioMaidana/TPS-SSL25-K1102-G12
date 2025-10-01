#include <stdio.h>
#include <stdlib.h>
#include "funciones_punto2.h"
#include "../funciones_comunes/funcionesComunes.h"

int main(){

    FILE* f = fopen("cadena2.txt", "r");
    if(f == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char c = fgetc(f); // Lee un carácter
    fclose(f);

    if(elCaracterEsNumero(c)) {
        int numero = charToInt(c);
        printf("El caracter es un numero valido.\n");
        escribirArchivoGenerico("salida_valida2.txt", PUNTO2, NULL, numero, 0, 0, NULL, 1);
    } else{
        printf("El caracter no es un numero valido.\n");
        escribirArchivoGenerico("salida_invalida2.txt", PUNTO2, NULL, 0, 0, 0, NULL, 0);
    }

    return 0;
}