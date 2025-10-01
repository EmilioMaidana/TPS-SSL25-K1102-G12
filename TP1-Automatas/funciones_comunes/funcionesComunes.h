#ifndef FUNCIONES_COMUNES_H
#define FUNCIONES_COMUNES_H

typedef enum {
    PUNTO1,
    PUNTO2,
    PUNTO3
} PuntoTP;

// datoExtra1 puede ser: decimales     / numero / resultado
// datoExtra2 puede ser: octales       / 0      / 0
// datoExtra3 puede ser: hexadecimales / 0      / 0
// postfija: unicamente para el pto. 3
// valido: si la cadena es valida o invalida

void escribirArchivoGenerico(char* nombreArchivo, PuntoTP puntoTP, char* cadena,
                             int datoExtra1, int datoExtra2, int datoExtra3,
                             char* postfija, int valido);

char* leerArchivo(const char* nombreArchivo);

#endif