/*************************************************************************************/
/* @file    utilities.h                                                              */
/* @brief   funciones y estructuras de interes                                       */
/*************************************************************************************/

#ifndef _utilities_h
#define _utilities_h

//unix
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <stdio_ext.h>
#include <fcntl.h>

#define MAX_CHAR 15

//Estructura para direcciones IP de servidores
typedef struct direccion{
  char    address[MAX_CHAR];
  struct  direccion *next;
} Direccion;

//Estructura para una conexion
typedef struct conexion{
  int   PORT;
  char  IP_SERVER[MAX_CHAR];
  char  message[MAX_CHAR];
} Conexion;

// Creacion de nuevo nodo para la lista de direcciones IP de servidores
Direccion *newDireccion(char *address){
  Direccion *ptr = (Direccion *)malloc(sizeof(Direccion));

  if (ptr != NULL)  {
    strcpy(ptr->address, address);
    ptr->next = NULL;
  }
}

//Agregacion de una nueva direccion IP a la lista de direcciones de servidores
Direccion *addDireccion(Direccion *listp, Direccion *newp){
  Direccion *p;

  if (listp == NULL)
    return newp;

  for (p = listp; p->next != NULL; p = p->next);
  
  p->next = newp;

  return listp;
}

// ?
int cleanBuffer(){
  int fdflags;
  fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
  while (getchar() != EOF)
    ;
  fcntl(STDIN_FILENO, F_SETFL, fdflags);
}

// Presiona enter para continuar
void pausa(){
	printf("Press [ENTER] to continue\n");
	char enter = 0;
	while(getchar()!='\n'); // option TWO to clean stdin
        getchar(); // wait for ENTER
  
}

#endif
