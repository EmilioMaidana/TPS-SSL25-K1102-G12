#include <stdio.h>
#include <stdlib.h>
#include "funciones_punto2.h"
#include "../funciones_comunes/funcionesComunes.h"

int main(){

    FILE* f = fopen("caracter_valido.txt", "r");
    if(f == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char c = fgetc(f); // Lee un carácter
    fclose(f);
    printf ("Caracter leido: %c\n", c);

    if(elCaracterEsNumero(c)) {
        int numero = charToInt(c);
        printf("El caracter es un numero valido.\n");
        printf("Numero leido: %d\n", numero);
        escribirArchivoGenerico("salida_valido_punto2.txt", PUNTO2, &c, numero, 0, 0, NULL, 1);
    } else{
        printf("El caracter no es un numero valido.\n");
        escribirArchivoGenerico("salida_invalido_punto2.txt", PUNTO2, &c, 0, 0, 0, NULL, 0);
    }

    return 0;
}