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
        printf("Número leído: %d\n", numero);
    } else {
        printf("El carácter leído no es un número válido.\n");
    }

    return 0;
}