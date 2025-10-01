#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "funciones_punto1.h"
#include "../funciones_comunes/funcionesComunes.h"

// Devuelve la columna de transicion segun el caracter y el estado
int columna(char c, int e){
    if((e == 0 || e == 1) && c >= '1' && c <= '9') return 5;
    if(e == 0 && c == '+') return 0;
    if(e == 0 && c == '-') return 1;
    if(e == 0 && c == '0') return 2;
    if(e == 3 && (c == 'x' || c == 'X')) return 3;
    if(e == 3 && (c == 'o' || c == 'O')) return 4;
    if(e == 2 && c >= '0' && c <= '9') return 5;
    if(e == 4 && c >= '1' && c <= '7') return 6;
    if(e == 5 && c >= '0' && c <= '7') return 6;
    if(e == 6 && (c >= '1' && c <= '9' || c >= 'A' && c <='F')) return 7;
    if(e == 7 && (c >= '0' && c <= '9' || c >= 'A' && c <='F')) return 7;
    if ((e == 2 || e == 5 || e == 7) && c == '#') return 8;
    return 9; // estado de error
}

int esPalabra(char* cadena){     
    static int tt[9][10]={                        
        {1,1,3,8,8,2,8,8,8,8},
        {8,8,8,8,8,2,8,8,8,8},
        {8,8,8,8,8,2,8,8,0,8},
        {8,8,8,6,4,8,8,8,8,8},
        {8,8,8,8,8,8,5,8,8,8},
        {8,8,8,8,8,8,5,8,0,8},
        {8,8,8,8,8,8,8,7,8,8},
        {8,8,8,8,8,8,8,7,0,8}, // numero 0 del vector que le pase
        {8,8,8,8,8,8,8,8,8,8},
    };
    
    int eAnterior;
    int e = 0;           // estado inicial
    int decimales = 0, octales = 0, hexadecimales = 0;

    for(int i = 0; cadena[i] != '\0'; i++) {
        char c = cadena[i];
        eAnterior = e;
        e = tt[e][columna(c, e)];

        if(e == 9 || e == 8) {
            escribirArchivoGenerico("salida_invalida.txt", PUNTO1, cadena, 0, 0, 0, NULL, 0);
            return 0;
        }
        
        // Contar cuando tenemos separador #
        if (c == '#') {
            if (eAnterior == 2) decimales++;
            else if (eAnterior == 5) octales++;
            else if (eAnterior == 7) hexadecimales++;
            e = 0; // Reiniciar estado para el siguiente numero
        }
    }

    // Contar el último número del estado final si la cadena llegó al \0
    if (e == 2) decimales++;
    else if (e == 5) octales++;
    else if (e == 7) hexadecimales++;

    escribirArchivoGenerico("salida_valida.txt", PUNTO1, cadena, decimales, octales, hexadecimales, NULL, 1);
    return 1;
}  