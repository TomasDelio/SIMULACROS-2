#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int numCamiseta;
    char nombre[30];
    char equipo[30];
    int edad;
} jugadorScaloneta;


const int col= 3;
const int fila= 3;
int cargarMatrizChar (char matriz[][100],int filas,int col);
void cargarJugadores(char Scaloneta[]);
void verarchi(char Scaloneta[]);
void mostrarEquipos(char Scaloneta[], char nombreEquipos[]);
int cantid(char Scaloneta[]);
void buscajugador(char Scaloneta[], int dato);
int pasaje(char Scaloneta[], jugadorScaloneta edad[], int edada);
jugadorScaloneta Menordedad(char Scaloneta[]);
int buscaname(char Scaloneta [], int dato);

int main()
{
    int num;
    int ca;
    char yes;

    int palabra;
    char matriz[fila][100];
    char arre[30];
    char equipos[30];
    int datazo;

    jugadorScaloneta edad[30];

    FILE *archi;
    strcpy(arre, "Scaloneta.bin");//ACA
    //ESTO SIRVE MAS QUE NADA PARA PODER COPIAR EL ARCHIVO EN LA
    //VARIABLE 'ARRE' Y PODER USARLA EN EL MAIN Y NO PONER EL ARCHIVO DIRECTAMENTE
    archi = fopen("Scaloneta.bin", "ab");//Modo de apertura y escritura

    do
    {
        printf("HOLA , ESTA ES LA PRACTICA DEL PARCIAL SELECIONES EL EJERCIO : ");
        fflush(stdin);
        scanf("%i", &num);
        switch(num)
        {
        case 1:
            palabra= cargarMatrizChar(matriz,fila,col);
            printf("Se han cargado %d palabras en la matriz.\n" , palabra);
            break;

        case 2:
            cargarJugadores(arre);
            verarchi(arre);

            break;
        case 3:
            printf("Ingrese el nombre del equipo: ");
            scanf("%s", equipos);
            mostrarEquipos(arre, equipos);

            break;
        case 4:
            verarchi(arre);
            ca = cantid(arre);
            printf("\n\nLa cantidad de regsitros en el archivo es de: %i", ca);
            break;

        case 5:
            verarchi(arre);
            printf("\nseleccione el numero de la pocision del jugador a buscar: ");
            fflush(stdin);
            scanf("%i", &ca);
            buscajugador(arre,ca);
            break;
        case 6:
            verarchi(arre);
            printf("\nseleccione la edad que desea ingresar: ");
            fflush(stdin);
            scanf("%i", &ca);
            ca = pasaje(arre,edad,ca);
            printf("\n\nLa cantidad de personas cargadas ak arreglo es de: %i ", ca);

            break;
        case 7:
         {
            jugadorScaloneta Menor = Menordedad(arre);
            printf("\nJugador de menor edad:");
            printf("\n--------------------------------------------------\n");
            printf("Numero de camiseta: %d\n", Menor.numCamiseta);
            printf("Nombre del jugador: %s\n", Menor.nombre);
            printf("Equipo: %s\n", Menor.equipo);
            printf("Edad: %d\n", Menor.edad);
            printf("--------------------------------------------------\n");
        }
            break;
        case 8:
            verarchi(arre);
            printf("\nIngrese el numero de camiseta que desea buscar: ");
            scanf("%i",&datazo);
            ca=buscaname(arre,datazo);
            if (ca==-1)
            {
                printf("\n El numero de camiseta NO se encontro en el archivo ");
            }
            else
            {
                printf("\nEl numero de camiseta se encontro en el archivo ");
            }
            break;
        }
        printf("Desea ver otro ejercicio? presione s para si ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    while(yes=='s'|| yes=='S');


    return 0;
}
//////////////////////////////////////////////////// 1 ///////////////////////////////////////////////////////////
int cargarMatrizChar (char matriz[][100],int filas,int col)
{
    int contador = 0;
    int i, j;

    for(i=0;i<filas;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("Ingrese la palabra que quiera: ");
            scanf("%s", matriz[i]);
            contador ++;
        }
    }
    return contador;
}
//////////////////////////////////////////////////// 2 ///////////////////////////////////////////////////////////

void cargarJugadores(char Scaloneta[])
{
    FILE *archi;
    archi = fopen(Scaloneta, "ab");
    char yes='s';
    jugadorScaloneta jugador;//Variable jugadorScaloneta es de la estructura
    //ESTO PARA GUARDARLO EN LA ESTRUCTURA ANTES DE PASARLO AL ARCHIVO

    if(archi!=NULL)//VERIFICA SI EXISTE
    {
        while(yes=='s'||yes=='S')//PARA PODER PASAR ENTRE LOS DATOS QUE VAYAS PONIENDO
        {
        printf("Ingrese el numero de camiseta del jugador: ");
        scanf("%d", &jugador.numCamiseta);

        printf("Ingrese el nombre del jugador: ");
        scanf("%s", jugador.nombre);

        printf("Ingrese el equipo del jugador: ");
        scanf("%s", jugador.equipo);

        printf("Ingrese la edad del jugador: ");
        scanf("%d", &jugador.edad);

            fwrite(&jugador, sizeof(jugador),1,archi);//ACA TODO LO DE ARRIBA SE ESCRIBE EN EL ARCHIVO
            //&jugador: Es la dirección de memoria del objeto jugadorScaloneta que se desea escribir en el archivo.
            //Al usar el operador &, obtenemos un puntero al objeto jugadorScaloneta
            //sizeof(jugador): Es el tamaño en bytes de la estructura jugadorScaloneta
            //La función sizeof devuelve el tamaño de un tipo o una estructura en bytes.
            //1: Indica que se va a escribir solo un elemento de la estructura jugadorScaloneta.
            //archi: Es el puntero al archivo en el que se van a escribir los datos.
            printf("Desea continuar?");
            fflush(stdin);
            scanf("%c", &yes);

        }

        fclose(archi);
    }
    else
    {
        printf("NO EXISTE PELOTUDITOOOOO");
    }
}

void verarchi(char Scaloneta[])//MODULARIZACION
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");//Se abre el archivo existente para SOLO lectura
    jugadorScaloneta jugador;


    if(archi!=NULL)//PRIMERA LECTURA
    {
        while(!feof(archi))//feof y el nombre del archivo controlar la finalización de la lectura o escritura de un archivo.
        //Nunca se va a alcanzar el final del archivo por que estamos al principio osea que siempre devulve 0
        {
            fread(&jugador, sizeof(jugador),1,archi);//ACA EL FREAD LEE LOS BYTES CON EL SIZEOF DESDE ARCHI
            //SEGUNDA LECTURA

            if(!feof(archi))//ESTO ES IMPORTANTE POR QUE INTENTA LEERLO POR QUE SE ESTABLE DESPUES DE UNA OPERACION DE LECTURA
            {
                printf("\n--------------------------------------------------\n");
                printf("\nNumero de camiseta : %d", jugador.numCamiseta);
                printf("\nNombre del jugador: %s", jugador.nombre);
                printf("\nEquipo: %s", jugador.equipo);
                printf("\nEdad: %i", jugador.edad);
                printf("\n--------------------------------------------------");
            }
        }
        fclose(archi);
    }

}
//////////////////////////////////////////////////// 3 ///////////////////////////////////////////////////////////

void mostrarEquipos(char Scaloneta[], char nombreEquipos[])
{
     FILE *archi;
    archi = fopen(Scaloneta, "rb");//Se abre el archivo existente para SOLO lectura
    jugadorScaloneta jugador;

    if (archi!=NULL)
    {
        while(fread(&jugador,sizeof(jugador),1, archi)==1)
            //La lectura se realiza en bloques de tamaño 1.OSEA QUE VA A LEER UNO POR UNO
        {
            if(strcmp(jugador.equipo, nombreEquipos)==0)
            //Muestra solo los equipos
            {
               printf("\n--------------------------------------------------\n");
                printf("\nNumero de camiseta : %d", jugador.numCamiseta);
                printf("\nNombre del jugador: %s", jugador.nombre);
                printf("\nEquipo: %s", jugador.equipo);
                printf("\nEdad: %i", jugador.edad);
                printf("\n--------------------------------------------------");
            }
        }
    }
    fclose(archi);
}
//////////////////////////////////////////////////// 4 ///////////////////////////////////////////////////////////
int cantid(char Scaloneta[])
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");
    int total;

    fseek(archi,0, SEEK_END);//CON FSEEK MOVEMOS LA "POCISION", BUSCAMOS EN EL ARCHIVO Y POCISIMONAMOS NUESTRO "INDICADOR" AL FINAL CON EL SEEK_END

    total=ftell(archi)/sizeof(jugadorScaloneta);// Con el ftell Obtenemos la posición actual del archivo
    //Dividimos los bytes del archivo sabiendo que esta al final y con esto sabemos cuantos archivos estan cargados por la cantidad de bytes
    //por que cada uno de los jugadores cargados tienen el mismo peso osea que si tenesmos 2 jugadores de 5 bytes juntos pesan 10,y si lo
    //dividimos nos da la cantidad que son 2 logico
    fclose(archi);

    return total;
}
//////////////////////////////////////////////////// 5  ///////////////////////////////////////////////////////////

void buscajugador(char Scaloneta[], int dato)
{
    FILE *archi;
    archi = fopen(Scaloneta, "rb");
    int num=0;
    int val=0;
    jugadorScaloneta jugador;

    val=cantid(Scaloneta );//ACA YA ESTAMOS LLAMANDO A LA FUNCION ANTERIOR ,Y LE DECIMOS QUE LA FUNCION ANTERIOR SE GUARDE VAL

    if(archi!=NULL)
    {

        if(dato<val)//esta es la verificacion de que no se sobrepase el archivo con los numero ingresados
        {
            fseek(archi,sizeof(jugadorScaloneta)*(dato-1),SEEK_SET);
            //SE MUEVE ENTRE LAS POSICIONES Y     ESTA PARTE CALCULA EL DESPLAZAMIENTO NECESARIO DE BYTRES PARA LLEGAR A LA POSICION CORRECTA
            fread(&jugador,sizeof(jugadorScaloneta),1,archi);
            //ESTO LEE LA POCISION ACTUAL DEL ARVHIVO Y LEE SOLO 1 ELEMNTO

            num=ftell(archi);
            //A LA POCISION ACTUAL ME LA GUARDA EN NUM


            printf("\n\n\n\n\n\n\n");
            printf("\n--------------------------------------------------\n");
            printf("\nNumero de camiseta : %d", jugador.numCamiseta);
            printf("\nNombre del jugador: %s", jugador.nombre);
            printf("\nEquipo: %s", jugador.equipo);
            printf("\nEdad: %i", jugador.edad);
            printf("\n--------------------------------------------------");


        }
        else
        {
            printf("\n\nEL NUMERO SUPERA LA CANTIDAD DE JUGADORES!!!");
        }
        fclose(archi);
    }
}

//////////////////////////////////////////////////// 6 ///////////////////////////////////////////////////////////

int pasaje(char Scaloneta[], jugadorScaloneta edad[], int edada)
{
    FILE *archi;
    archi= fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;
    int i=0;

    if(archi!=NULL)
    {
        while(!feof(archi))//SI EL ARCHIVO NO FINALIZA O SINO SE  ALCANZO EL FINAL DEL ARCHIVO
        {
            fread(&jugador,sizeof(jugadorScaloneta),1,archi);
           // ACA EL FREAD LEE LOS BYTES CON EL SIZEOF DESDE ARCHI
            if(!feof(archi))//VERIFICA NUEVAMENTE SI NO SE A ALCANZO EL FINAL DEL ARCHIVO
            {
                if(edada==jugador.edad)//SI LA EDAD DEL JUGADOR ES EXACTAMENTE IGUAL A LA EDAD QUE BUSCAMOS
                {
                    edad[i]=jugador;//SE AGREGA EL JUGADOR AL ARREGLO EDAD EN LA POCICION I
                    i++;
                }
            }
        }
        fclose(archi);
    }
    return i;
}
//////////////////////////////////////////////////// 7 ///////////////////////////////////////////////////////////

jugadorScaloneta Menordedad(char Scaloneta[])
{
    FILE *archi;
    archi=fopen(Scaloneta,"rb");
    jugadorScaloneta jugador;
    jugadorScaloneta Menor;
    int menorEdad = 18;

    if(archi!= NULL)
    {
        while(fread(&jugador,sizeof(jugador),1,archi)==1)
        {
            if(jugador.edad < menorEdad)
            {
                menorEdad=jugador.edad;
                Menor=jugador;
            }
        }
        fclose(archi);
    }
    return Menor;
}

//////////////////////////////////////////////////// 8 ///////////////////////////////////////////////////////////
int buscaname(char Scaloneta [], int dato)
{
     FILE *archi;
    archi= fopen(Scaloneta, "rb");
    jugadorScaloneta jugador;

    if(archi!=NULL)
    {
        while(fread(&jugador,sizeof(jugadorScaloneta),1,archi)==1)
        {
            if(jugador.numCamiseta== dato)
            {
                fclose(archi);
                return 1;
            }
        }
        fclose(archi);
    }
    else{
   return -1;
    }
}

