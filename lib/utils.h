#ifndef SERIALIZACION_H
#define SERIALIZACION_H
//librerias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio_ext.h>
#include <fcntl.h>
#include <pthread.h>
#define MAX_CHAR 255

//definicion de las estructuras
typedef struct direccion{
  char address[MAX_CHAR];
  struct direccion *next;
} Direccion;

typedef struct conexion{
  int PORT;
  char IP_SERVER[255];
  char message[255];
} Conexion;

Direccion *newDireccion(char *address){
  Direccion *ptr = (Direccion *)malloc(sizeof(Direccion));
  if (ptr != NULL)
  {
    strcpy(ptr->address, address);
    ptr->next = NULL;
  }
}

Direccion *addDireccion(Direccion *listp, Direccion *newp){
  Direccion *p;
  if (listp == NULL)
    return newp;
  for (p = listp; p->next != NULL; p = p->next)
    ;
  p->next = newp;
  return listp;
}

int cleanBuffer(){
  int fdflags;
  fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
  while (getchar() != EOF)
    ;
  fcntl(STDIN_FILENO, F_SETFL, fdflags);
}

void pausa(){
  while (getchar() != '\n')
    ;
}

#endif
