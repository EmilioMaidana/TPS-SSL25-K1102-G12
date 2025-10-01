    #include <stdio.h>
    #include <stdlib.h>
    #include "funciones_punto1.h"
    #include "../funciones_comunes/funcionesComunes.h"

    int main(){
        char* cadena = leerArchivo("cadena.txt");
        if(!cadena){
            return -1;
        }

        // Procesar la cadena
        if(esPalabra(cadena)) {
            printf("Cadena valida procesada.\n");
        } else {
            printf("Cadena invalida.\n");
        }

        free(cadena);
        return 0;
    }
