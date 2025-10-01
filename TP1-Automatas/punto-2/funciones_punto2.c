#include <stdio.h>
#include <stdlib.h>
#include "funciones_punto2.h"
#include "../funciones_comunes/funcionesComunes.h"

int charToInt(char c) {
    return c - '0';
}

int elCaracterEsNumero(char c) {
    return c >= '0' && c <= '9' ? 1 : 0; 
}