#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---Macros---
#define MAX 50



//Definimos un arreglo de estructuras para los clientes.
struct cliente {
        char ID[8];
        char nombre [30];
        char telefono [10];
        unsigned int dia;
        unsigned int mes;
        unsigned int anio;
} cliente[MAX];

//---Prototipos---
void cargar(void), guardar(void), buscar(void), muestra(int i);
void leercad(char *indic, char *s, int cont);
void borrar(void), intro(void), mostrar(void);
int busca(char *nombre), menu(void);
void iniciar_lista(void);
int busca_libre(void);

//---Main---
int main() {
        int opcion;

        iniciar_lista();

        for(;;) {
                opcion = menu();
                switch(opcion) {
                        case 1: intro();
                        break;

                        case 2: borrar();
                        break;

                        case 3: mostrar();
                        break;

                        case 4: buscar();
                        break;

                        case 5: guardar();
                        break;

                        case 6: cargar();
                        break;

                        case 7: printf("No pude ordenar la lista :( \n");
                        return 0;

                        case 8: return 0;

                        case 9: printf("\nLicencia: BSD-Clause-3");
                        printf("\nCreado por: Omar Jair Purata");
                        printf("\nUsando C (ANSI, C11), Vim 8.0 & \
                        StackOverflow (no pregunten)");
                        break;

                        default: printf("Opción no válida");
                        return 0;
                }
        }
}

void iniciar_lista(void)
{
        /* No vimos esto en clase pero el usar la palabra clave "register"
        * va a guardar una variable (En este caso de tipo entero) en el
        * registro del procesador, los registros son menos tardados en acceder
        * que la memoria, como el entero i que estoy declarando abajo es una
        * variable que voy a usar frecuentemente es mejor guardarla dentro
        * del registro aunque al final del día en compilador será quien
        * decida poner la variable dentro del registro.
        */
        register int i;

        for (i = 0; i < MAX; i++) *cliente[i].nombre = '\0';
}


int menu(void)
{
        char s[80]; //No mas de 80 caracteres, nadie quiere tipear nombres de opciones tan largos.
        int c;
        printf("1- Introducir un cliente\n");
        printf("2- Borrar un cliente\n");
        printf("3- Listar los clientes\n");
        printf("4- Buscar en el archivo\n");
        printf("5- Guardar el archivo\n");
        printf("6- Cargar el archivo \n");
        printf("7- Ordenar el archivo por nombre\n");
        printf("8- Salir\n");
        printf("9- Acerca De: ");

        do {
                printf("\nIntroduzca su opción: ");
                fgets(s, sizeof(s), stdin);
                c = atoi(s);
        } while (c < 0 || c > 9);

        return c;
}


/* Aquí declararé la función intro que primero va a llamar a la funcion definida "buscar_libre"
 * esa función lo que hará es revisar si hay un espacio libre donde meter los datos en el arreglo
 * de estructuras que definimos mas arriba en el código, luego llamará a la funcion "leercadena"
 * que le pedirá al usuario campos que se manejen como cadenas de texto como el número de teléfono o el ID
 * principalmente porque quiero intentar validarlos esa función la documentaré mas abajo esta función llamada
 * intro de tipo void lo que hará es que tendrá un ciclo infinito en el cual seguirá preguntando los datos
 * para un nuevo usuario si es que queda espacio en el arreglo de estructuras que se encuentre en memoria.*/

void intro(void)
{
        int i;

        for(;;) {
                i = busca_libre();

                if (i < 0) {
                        printf("\nLa lista se encuentra llena :( \n");
                        return;
                }

                leercad("\nIntroduzca un ID: ", cliente[i].ID, 8);
                //Con esta función leeremos las cadenas de caracteres que se necesiten.
                leercad("\nIntroduzca un nombre: ", cliente[i].nombre, 30);
                //Condicional de espacio
                if (! *cliente[i].nombre) break; //Podemos poner la sentencia en la misma línea que la condición.
                leercad("\nIntroduzca un teléfono: ", cliente[i].telefono, 10); //Una funcion personalizada paraleer cadenas

                printf("\nIntroduzca un día: ");
                scanf("%x", &cliente[i].dia);
                printf("\nIntroduzca un mes: ");
                scanf("%x", &cliente[i].mes);
                printf("\nIntroduzca un año: ");
                scanf("%x", &cliente[i].anio);

        }
}



/*
 * Esta función va a retornar el índice (o el espacio) de una estructura (si es que hay una libre)
 * En caso de no existir, devolverá un -1 (No hay excepciones aquí) aunque podríamos usar
 *la librería errno.h pero solo sería para enviar un mensaje de error y no para ciclar el programa */

int busca_libre(void)
{
        register int i; //De nuevo guardamos el entero "i" en un registro del procesador.

        for(i = 0; i<MAX; i++) //Un for sin llaves hará que la siguiente instrucción pertenezca al cuerpo del ciclo.
                if(!*cliente[i].nombre) return i;
        return -1;
}



//Esta función leerá una cadena de caracteres, lo genial es que gracias a StackOverflow y a alguien de Freenode
//previene que la cadena tenga caracteres de mas y la valida

void leercad(char *indic, char *s, int cont)
{
        char cadena[255];

        do {
                printf("%s", indic);
                fgets(cadena, sizeof(cadena), stdin);
                if(strlen(cadena)>=cont) printf("\nLa cadena de texto que ingresó es demasiado larga.");
        } while (strlen(cadena)>=cont);

        strcpy(s, cadena);
}

/* Esta función eliminará una dirección de la lista */

void borrar(void)
{
        int i;
        char cadena[255];

        leercad("Introduzca el nombre del usuario que desea eliminar: ", cadena, 30);
        i = busca(cadena);
        if ( i >= 0 ) *cliente[i].nombre = '\0';
        else printf("No se encontró a esa persona\n");
}

/* Ésta función buscará un nombre y devolverá su lugar en el índice
 * o retornará un error de -1 si no encuentra nada*/

int busca(char *nombre)
{
        int i;

        for(i=0; i < MAX; i++)
        if (!strcmp(nombre, cliente[i].nombre)) break;
        if (i == MAX) return -1; //Solo si ya se recorrió todo el arreglo y no se encontró el nombre.
        else return i;
}

// Con la siguiente función mostraremos la lista de correos

void mostrar(void)
{
        int i;

        for(i=0; i<MAX; i++) {
                if(*cliente[i].nombre) {
                        muestra(i);
                        printf("\n\n");
                }
        }
        printf("\n\n");
}
// Lo siguiente imprimirá los nombres y los teléfonos

void muestra(int i)
{
        printf("%s\n", cliente[i].ID);
        printf("%s\n", cliente[i].nombre);
        printf("%s %x %x %x \n", cliente[i].telefono, cliente[i].dia, cliente[i].mes, cliente[i].anio);
}

/* Buscar dentro de la lista */
void buscar(void)
{
        int i;
        char nombre[30];

        leercad("Introduzca sus parámetros de búsqueda: ", nombre, 30);
        if((i=busca(nombre))< 0) printf("No se encontró a nadie con ese nombre\n");
        else muestra(i);
}

/* Guardado y cargado de la lista */

void guardar(void)
{
        FILE *fp;

        if((fp = fopen("clientes.gdnz", "wb")) == NULL) {
                printf("No se pudo abrir el archivo :(\n");
                return;
        }

        printf("\n**********|Guardando el archivo|***********\n");
        fwrite(cliente, sizeof cliente, 1, fp);
        if(ferror(fp))
                printf("Ocurrió un error al escribir en el archivo :(\n");
        fclose(fp);
}

/* Cargar el archivo */

void cargar(void)
{
        FILE *fp;

        if((fp = fopen("clientes.gdnz", "rb")) == NULL) {
                printf("No se pudo cargar el archivo :( \n");
                return;
        }

        printf("\n**********|Cargando el archivo|**********\n");
        fread(cliente, sizeof cliente, 1, fp);

        if(ferror(fp))
                printf("Ocurrió un error al cargar el archivo :(\n");
}
