#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//nota: siempre se reciben caracteres, la nocion del int es una transformacion de
//caracter a entero si, este caracter se consumio por medio del
//flujo de entrada(cin para los amigo o scanf)


//1) Dada una cadena que contenga varios números que pueden ser decimales, octales o hexadecimales, con o sin signo para el caso de los decimales, separados por el carácter ‘#’, reconocer los tres grupos de constantes enteras, indicando si hubo un error léxico, en caso de ser correcto contar la cantidad de cada grupo.
//Debe diagramar y entregar el o los autómatas utilizados y las matrices de transición.
//La cadena debe ingresar por línea de comando o por archivo.


int columna (char q,int e){
    if((e==0||e==1) && q >= '1' && q <= '9') return 5;
    if(e==0 && q == '+') return 0;
    if(e==0 && q == '-') return 1;
    if((e==2) && q >= '0' && q <= '9') return 5;
    if(e ==0 && q == '0') return 2;
    if(e ==3 && q == 'o') return 4;
    if(e==4 && q >= '1' && q <= '7') return 6;
    if(e==5 && q >= '0' && q <= '7') return 6;
    if(e ==3 && q == 'x') return 3;
    if(e ==6 && (q >= '1' && q <= '9' || q >= 'A' && q<='F')) return 7;
    if(e==7 && (q >= '0' && q <= '9' || q >= 'A' && q<='F')) return 7;
    if ((e==2 || e==5 || e==7) && q == '#') return 8;
    return 9;
}

int esPalabra(char* cadena, int printValues){     //aca el vector se pasa por referencia y si printValues == 1 muestra por pantalla los valores evaluados y cuantos numeros registró
    static int tt[9][10]={         //como un vector apuntando a la posicion
                         {1,1,3,8,8,2,8,8,8,8},
                         {8,8,8,8,8,2,8,8,8,8},
                         {8,8,8,8,8,2,8,8,0,8},
                         {8,8,8,6,4,8,8,8,8,8},
                         {8,8,8,8,8,8,5,8,8,8},
                         {8,8,8,8,8,8,5,8,0,8},
                         {8,8,8,8,8,8,8,7,8,8},
                         {8,8,8,8,8,8,8,7,0,8},
                         {8,8,8,8,8,8,8,8,8,8},
                          //numero 0 del vector que le pase

    };
    int eAnterior;
    int e = 0;//estado inicial
    int i = 0; //iterador
    int c = cadena[i];
    int decimales = 0;
    int octales = 0;
    int hexadecimales = 0;
    /* modelo con complicaciones
    if(printValues == 1){
          while (c != '\0' && e!=8){ // aca evaluo en cada iteracion si es que estoy en un estado de rechazo
            eAnterior = e;
            e = tt[e][columna(c,e)];
            if ((eAnterior == 2 && e == 0)||(e == 2 && (cadena[i+1] == '\0'))) decimales ++;
            if ((eAnterior == 5 && e == 0)||(e == 5 && (cadena[i+1] == '\0'))) octales ++;
            if ((eAnterior == 7 && e == 0)||(e == 7 && (cadena[i+1] == '\0'))) hexadecimales ++;
            i++;
            c=cadena[i];
        }*/
    if (printValues == 1) {
        while (c != '\0' && e != 8) {
            eAnterior = e;
            e = tt[e][columna(c, e)];
            i++;
            c = cadena[i];

        // contar SOLO en separadores (#) o al final
        if (c == '#' || c == '\0') {
            if (eAnterior == 2) decimales++;
            else if (eAnterior == 5) octales++;
            else if (eAnterior == 7) hexadecimales++;
        }
        }
    }
    else{
        while (c != '\0' && e!=8){ //while(c!='\0'){ //primer modelo en el que solo chequeo si llego a un estado de rechazo
            // aca evaluo en cada iteracion si es que estoy en un estado de rechazo<- esta por lo visto es la que posee mejor performance cuando se presenta un archivo lo suficientemente grande
            e = tt[e][columna(c,e)];
            i++;
            c=cadena[i];
        }
    }
    if(printValues == 1 && (e==2 || e==5 || e==7)){
        printf("La cadena evaluada es la siguiente:\n");
        for(int i = 0; cadena[i]!= '\0'; i++){
        printf( "%c", cadena[i]);
    }
        printf("\n________________________________________________\n");
        printf("\nSe registraron %d numeros decimales\n",decimales);
        printf("\nSe registraron %d numeros octales\n",octales);
        printf("\nSe registraron %d numeros hexadecimales\n",hexadecimales);
        printf("\n________________________________________________\n");
    }
    else if (printValues == 1 && e != 2 && e != 5 && e != 7) {
        printf("\nError lexico\n");
    }
    if (e==2 || e==5 || e==7) return 1;
    else return 0;
    }



    /*// codigo ia
    int e = 0;
    int i = 0;
    int c = cadena[i];
    int decimales = 0;
    int octales = 0;
    int hexadecimales = 0;

    while (c != '\0' && e != 8){
        int eAnterior = e;
        e = tt[e][columna(c, e)];

        // Check for a complete number when a '#' is found or end of string
        if (e == 0 || (c == '\0' && (eAnterior == 2 || eAnterior == 5 || eAnterior == 7))) {
            if (eAnterior == 2) {
                decimales++;
            } else if (eAnterior == 5) {
                octales++;
            } else if (eAnterior == 7) {
                hexadecimales++;
            }
        }
        i++;
        c = cadena[i];
    }

    if(printValues == 1 && (e == 2 || e == 5 || e == 7)){
        if (e == 2) {
            decimales++;
        } else if (e == 5) {
            octales++;
        } else if (e == 7) {
            hexadecimales++;
        }

        printf("\n________________________________________________\n");
        printf("\nSe registraron %d numeros decimales\n",decimales);
        printf("\nSe registraron %d numeros octales\n",octales);
        printf("\nSe registraron %d numeros hexadecimales\n",hexadecimales);
        printf("\n________________________________________________\n");
    }
    else if (printValues == 1 && e != 2 && e != 5 && e != 7) {
        printf("\nError lexico\n");
    }

    if (e == 2 || e == 5 || e == 7) return 1;
    else return 0;
    */



int main()
{
    /*
     FILE *archivo;
    char p;

    archivo = fopen("cadena.txt", "r");  // abrir en modo lectura ("r")
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char buffer[10000];
    fscanf(archivo, "%s", buffer);
    */
    FILE *archivo = fopen("cadena.txt", "r");
    if (archivo == NULL) {
    printf("Error al abrir el archivo.\n");
    return -1;
    }

    // mover al final para saber la longitud
    fseek(archivo, 0, SEEK_END);
    long length = ftell(archivo);  // cantidad de bytes
    rewind(archivo);               // volver al inicio

    // reservar memoria dinámica
    char *buffer = malloc((length + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Error al reservar memoria.\n");
        fclose(archivo);
        return -1;
    }

    // leer todo el archivo en el buffer
    //fread(buffer, 1, length, archivo);
    //buffer[length] = '\0'; ESTO DA ERROR PORQUE LEE TAMBIEN UN /n
    fgets(buffer, length + 1, archivo);
    buffer[strcspn(buffer, "\n")] = '\0'; // recorta el salto de línea
    //printf("El archivo contiene:\n%s\n", buffer);

    char c [10] = {"Hola"};
    char f [10] = {"+123"};
    char g [10] = {"-243"};
    char h [10] = {"0xAB118"};
    char j [10] = {"0o117"};
    char k [20] = {"+123#0xAB118#0o117"};
//pruebas
    assert(esPalabra(c,0) == 0);
    assert(esPalabra(f,0) == 1);
    assert(esPalabra(g,0) == 1);
    assert(esPalabra(h,0) == 1);
    assert(esPalabra(j,0) == 1);
    assert(esPalabra(k,0) == 1);
    assert(esPalabra(buffer,0) == 1);
    esPalabra(buffer,0); //prueba donde se imprimen la cantidad de valores de cada uno en el archivo
    esPalabra(k,1);
    esPalabra(h,1);
    fclose(archivo);
    printf("\n\n Las pruebas se completaron con Exito\n");

    free(buffer);
    fclose(archivo);
// falta implementar que vaya contando la cantidad de numeros decimales, octales y hexadecimales tiene cada palabra
}
