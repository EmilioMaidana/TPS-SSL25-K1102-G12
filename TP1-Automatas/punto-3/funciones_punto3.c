#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../punto-1/funciones_punto1.h"
#include "../punto-2/funciones_punto2.h"
#include "../punto-3/funciones_punto3.h"
#include "../funciones_comunes/funcionesComunes.h"

// Devuelve la columna de transicion segun el caracter 
int columnas(char c){
    if(elCaracterEsNumero(c)) return 0;
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    return 3; // Cualquier otro -> error
}

int verificarExpresion(char* expresion) {
    static int tt[5][4] = {
        {1, 4, 4, 4},
        {4, 2, 2, 4},
        {3, 4, 4, 4},
        {4, 2, 2, 4},
        {4, 4, 4, 4}
    };

    int e = 0;
    for(int i = 0; expresion[i] != '\0'; i++) {
        int col = columnas(expresion[i]);
        e = tt[e][col];
        if(e == 4) return 0; // Estado de rechazo
    }

    return (e == 3);
}

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

void infijaAPostfija(char* expresionInfija, char* expresionPostfija, int cantOperadores) {
    char pilaOperadores[cantOperadores];  // Pila para almacenar operadores
    int indiceTopePila = -1;              // Tope de la pila de operadores (inicialmente vacia)
    int indicePostfija = 0;               // Indice para agregar a la expresion postfija

    for(int i = 0; expresionInfija[i] != '\0'; i++){
        char caracterActual = expresionInfija[i];

        if(isdigit(caracterActual)){
            // Si es un numero lo agregamos directamente a la expresio postfija
            expresionPostfija[indicePostfija++] = caracterActual;
        } else {
            // Si es un operador, verificamos su precedencia
            while(indiceTopePila >= 0 &&
                    precedencia(pilaOperadores[indiceTopePila]) >= precedencia(caracterActual)){
                // Sacamos los operadores de >= precedencia y los ponemos en la expresion postfija
                expresionPostfija[indicePostfija++] = pilaOperadores[indiceTopePila--]; 
            }
            // Apilamos el operador actual
            pilaOperadores[++indiceTopePila] = caracterActual;
        }
    }

    // Vaciar cualquier operador restante en la pila
    while(indiceTopePila >= 0){
        expresionPostfija[indicePostfija++] = pilaOperadores[indiceTopePila--];
    }

    // Finaliza la postfija con \0
    expresionPostfija[indicePostfija] = '\0';
}

int evaluarPostfija(char* expresionPostfija, int cantOperandos){
    int pilaOperandos[cantOperandos]; // Pila para almacenar numeros
    int indiceTopePila = -1;          // Tope de pila de operandos

    for(int i = 0; expresionPostfija[i] != '\0'; i++){
        char caracterActual = expresionPostfija[i];

        if(isdigit(caracterActual)){
            // Convertimos el caracter a numero y lo apilamos 
            pilaOperandos[++indiceTopePila] = charToInt(caracterActual);
        } else {
            // Operador: desapilamos los dos ultimos operandos
            int operandoB = pilaOperandos[indiceTopePila--];
            int operandoA = pilaOperandos[indiceTopePila--];

            // Aplicamos el operador
            int resultadoParcial = aplicarOperador(operandoA, operandoB, caracterActual);

            // Apilamos el resultado
            pilaOperandos[++indiceTopePila] = resultadoParcial;
        }
    }

    // El resultado final queda en la cima de la pila
    return pilaOperandos[indiceTopePila];
}

void convertirYEvaluarExpresion(char* cadena){
    int cantOperandos = 0, cantOperadores = 0;
    for(int i = 0; cadena[i]; i++){
        if(isdigit(cadena[i])) cantOperandos++;
        else if(cadena[i] == '+' || cadena[i] == '-' || cadena[i] == '*' || cadena[i] == '/') cantOperadores++;
    }
    char postfija[cantOperandos + cantOperadores + 1]; // Agrego el +1 por el \0
    infijaAPostfija(cadena, postfija, cantOperadores);

    printf("Expresion postfija: %s\n", postfija);

    int resultado = evaluarPostfija(postfija, cantOperandos);
    printf("Resultado: %d\n", resultado);
    
    escribirArchivoGenerico("salida_valida_punto3.txt", PUNTO3, cadena, resultado, 0, 0, postfija, 1);

}