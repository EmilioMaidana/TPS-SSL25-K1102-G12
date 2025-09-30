#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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
            FILE* fSalidaInvalida = fopen("salida_invalida.txt", "w");
            if(fSalidaInvalida) {
                fprintf(fSalidaInvalida, "Error lexico en la cadena:\n%s\n", cadena);
                fclose(fSalidaInvalida);
            }
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
    
    FILE* fSalidaValida = fopen("salida_valida.txt", "w");
    if(fSalidaValida) {
        fprintf(fSalidaValida, 
            "La cadena evaluada es la siguiente:\n%s"
            "\n________________________________________________\n"
            "\nSe registraron %d numeros decimales\n"
            "\nSe registraron %d numeros octales\n"
            "\nSe registraron %d numeros hexadecimales"
            "\n________________________________________________\n", 
            cadena, decimales, octales, hexadecimales);  
        fclose(fSalidaValida);
    }

    return 1;
}  

int main(){

    FILE* archivo = fopen("cadena.txt", "r");
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
