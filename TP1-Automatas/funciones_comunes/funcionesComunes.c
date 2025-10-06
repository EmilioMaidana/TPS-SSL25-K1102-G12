#include <stdio.h>
#include <stdlib.h>
#include "funcionesComunes.h"

void escribirArchivoGenerico(char* nombreArchivo, PuntoTP puntoTP, char* cadena,
                             int datosExtra1, int datosExtra2, int datosExtra3,
                             char* postfija, int valido)  {

    FILE* f = fopen(nombreArchivo, "w");
    if(f) {
        if(valido) {
            switch(puntoTP) {
                case PUNTO1:
                    fprintf(f, "La cadena evaluada es la siguiente:\n%s"
                               "\n________________________________________________\n"
                               "\nSe registraron %d numeros decimales\n"
                               "\nSe registraron %d numeros octales\n"
                               "\nSe registraron %d numeros hexadecimales"
                               "\n________________________________________________\n",
                               cadena, datosExtra1, datosExtra2, datosExtra3);
                    break;
                case PUNTO2:
                    fprintf(f,"Caracter leido: %c\n", *cadena);
                    fprintf(f,"El caracter es un numero valido.\n");
                    fprintf(f, "Numero leido: %d.\n", datosExtra1);
                    break;
                case PUNTO3:
                    fprintf(f, "Expresion: %s\n", cadena);
                    fprintf(f, "Expresion postfija: %s\n", postfija);
                    fprintf(f, "Resultado final: %d\n", datosExtra1);
                    break;
            }
        } else {
            switch(puntoTP) {
                case PUNTO1:
                    fprintf(f, "Error lexico en la cadena:\n%s\n", cadena);
                    break;
                case PUNTO2:
                    fprintf(f,"Caracter leido: %c\n", *cadena);
                    fprintf(f, "El caracter leido no es un numero valido.\n");
                    break;
                case PUNTO3:
                    fprintf(f, "Cadena invalida: %s\n", cadena);
                    break;
            }
        }
        fclose(f);
    } else {
        printf("No se pudo abrir el archivo %s para escritura.\n", nombreArchivo);
    }
}

char* leerArchivo(const char* nombreArchivo){
    FILE* archivo = fopen(nombreArchivo ,"r");
    if (!archivo) {
        printf("Error al abrir el archivo.\n");
        return NULL;
    }

    // Calcular tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);
    rewind(archivo);

    // Reservar memoria
    char* buffer = malloc((length + 1) * sizeof(char));
    if(buffer == NULL) {
        printf("Error al reservar memoria. \n");
        fclose(archivo);
        return NULL;
    }

    // Leer todo el archivo
    fread(buffer, sizeof(char), length, archivo);
    buffer[length] = '\0'; // Asegurar el fin de cadena
    fclose(archivo);

    return buffer;
}
