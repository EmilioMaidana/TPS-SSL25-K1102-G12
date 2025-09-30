#include <stdio.h>
#include <stdlib.h>

int charToInt(char c) {
    return c - '0';
}

int main(){

    FILE* f = fopen("cadena2.txt", "r");
    if(f == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char c = fgetc(f); // Lee un carácter
    fclose(f);

    int numero = -1;
    if(c >= '0' && c <= '9'){
        numero = charToInt(c);
        FILE* fSalidaValida = fopen("salida_valida2.txt", "w");
        if(fSalidaValida != NULL){
            fprintf(fSalidaValida, "Numero leido: %d.\n", numero);
            fclose(fSalidaValida);
        }
    } else {
        FILE* fSalidaInvalida = fopen("salida_invalida2.txt", "w");
        if(fSalidaInvalida != NULL){
            fprintf(fSalidaInvalida, "El caracter leido no es un numero valido: %c.\n", c);
            fclose(fSalidaInvalida);
        }
    }

    return 0;
}