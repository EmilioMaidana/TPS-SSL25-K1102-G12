#ifndef FUNCIONES_PUNTO3_H
#define FUNCIONES_PUNTO3_H

int precedencia(char operador);
int aplicarOperador(int a, int b, char operador);
int columnas(char c);
int verificarExpresion(char* expresion);
void infijaAPostfija(char* expresionInfija, char* expresionPostfija, int cantOperadores);
int evaluarPostfija(char* expresionPostfija, int cantOperandos);
void convertirYEvaluarExpresion(char* cadena);

#endif