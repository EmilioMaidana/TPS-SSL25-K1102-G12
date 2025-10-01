#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "punto1_automatasTP_v2.h"
#include "punto2_automatasTP.h"

int precedencia(char operador) {
    if(operador == '+' || operador == '-') return 1;
    if(operador == '*' || operador == '/') return 2;
    return 0;
}

int aplicarOperador(int a, int b, char operador){
    switch(operador){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : 0;  // Con esto evitamos la division por cero
    }
    return 0;
}

// Devuelve la columna de transicion segun el caracter 
int columna(char c){
    if(c >= '0' && c <= '9') return 0;
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    return 3; // Cualquier otro -> error
}

int verificarExpresion(char* expresion) {
    // Estados: 0 = inicio/despues de operador, 1 = dentro de numero, 2 = error
    static int tt[3][4] = {
        {1, 1, 2, 2},
        {1, 0, 0, 2},
        {2, 2, 2, 2}
    };

    int e = 0;
    for(int i = 0; expresion[i] != '\0'; i++) {
        int col = columna(expresion[i]);
        e = tt[e][col];
        if(e == 2) return 0; // Estado de rechazo
    }

    return (e == 1); // Aceptada si termina en numero
}


int main(){

    FILE* archivo = fopen("cadena3.txt" ,"r");
    if (!archivo) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    // Calcular tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    rewind(archivo);

    // Reservar memoria
    char* buffer = malloc((length + 1) * sizeof(char));
    if(buffer == NULL) {
        printf("Error al reserver memoria. \n");
        fclose(archivo);
        return -1;
    }

    // Leer todo el archivo
    fread(buffer, sizeof(char), length, archivo);
    buffer[length] = '\0'; // Asegurar el fin de cadena
    fclose(archivo);

    // Procesar la cadena
    if(esPalabra(buffer)) {
        printf("Cadena valida procesada.\n");
    } else {
        printf("Cadena invalida.\n");
    }

    free(buffer);
    return 0;
}
