#include <stdio.h>
#include <ctype.h>
#include <assert.h>
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
    if(e==4 && q >= '1' && q <= '8') return 6;
    if(e==5 && q >= '0' && q <= '8') return 6;
    if(e ==3 && q == 'x') return 3;
    if(e ==6 && (q >= '1' && q <= '9' || q >= 'A' && q<='F')) return 7;
    if(e==7 && (q >= '0' && q <= '9' || q >= 'A' && q<='F')) return 7;
    if ((e==2 || e==5 || e==7) && q == '#') return 8;
    return 9;
}

int esPalabra(char* cadena){     //aca el vector se pasa por referencia
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
    int e = 0;//estado inicial
    int i = 0; //iterador
    int c = cadena[i];// porque int c?? si en el array hay un char este se pasa a su valor en asccii, seguyn la profe porque los caracteres son un subconjunto de los enteros por lo que los caracteres se consumen como un tipo entero
    //while(c!='\0'){ //primer modelo en el que solo chequeo si llego a un estado de rechazo
        while (c != '\0' && e!=8){ // aca evaluo en cada iteracion si es que estoy en un estado de rechazo
            int eAnterior = e; 
            e = tt[e][columna(c,e)];
            i++;
            c=cadena[i];
        //if (eAnterior == 2 && e = 0) decimales ++
        //if (eAnterior == 5 && e = 0) octales ++
        //if (eAnterior == 7 && e = 0) hexadesimales ++
    }
    if (e==2 || e==5 || e==7) return 1;
    else return 0;
}

int main()
{
     FILE *archivo;
    char p;

    archivo = fopen("cadena.txt", "r");  // abrir en modo lectura ("r")
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return -1;
    }

    char buffer[10000];
    fscanf(archivo, "%s", buffer);
    printf("El archivo contiene lo siguiente:\n");
    for(int i = 0; buffer[i]!= '\0'; i++){
        printf( "%c", buffer[i]);
    }

    char c [10] = {"Hola"};
    char f [10] = {"+123"};
    char g [10] = {"-243"};
    char h [10] = {"0xAB118"};
    char j [10] = {"0o118"};
    char k [20] = {"+123#0xAB118#0o118"};
//pruebas
    assert(esPalabra(c) == 0);
    assert(esPalabra(f) == 1);
    assert(esPalabra(g) == 1);
    assert(esPalabra(h) == 1);
    assert(esPalabra(j) == 1);
    assert(esPalabra(k) == 1);
    assert(esPalabra(buffer) == 1);
    fclose(archivo);

// falta implementar que vaya contando la cantidad de numeros decimales, octales y hexadecimales tiene cada palabra
}