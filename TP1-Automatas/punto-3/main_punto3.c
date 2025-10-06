#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../punto-1/funciones_punto1.h"
#include "../punto-2/funciones_punto2.h"
#include "../punto-3/funciones_punto3.h"
#include "../funciones_comunes/funcionesComunes.h"

int main(){
    char* cadena = leerArchivo("cadena_valida.txt");
    if(!cadena){
        return -1;
    }

    if(!verificarExpresion(cadena)) {
        printf("Cadena invalida: %s\n", cadena);
        escribirArchivoGenerico("salida_invalida_punto3.txt", PUNTO3, cadena, 0, 0, 0, NULL, 0);
        return 0;
    }
    
    printf("Expresion: %s\n", cadena);

    convertirYEvaluarExpresion(cadena);

    free(cadena);
    return 0;
}
