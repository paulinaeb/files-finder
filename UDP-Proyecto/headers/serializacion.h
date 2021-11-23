#ifndef SERIALIZACION_H
#define SERIALIZACION_H
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
#define MAX_CHAR 255
#define MAX_ADDRESS 100
typedef struct peticion
{
    char address[MAX_ADDRESS][MAX_CHAR]; //Aqui se almacenan las n computadoras donde se hara la query
    int n_address;
    char message[MAX_CHAR];              // Aqui se almacena la query que se va a realizar

} Peticion;

int cleanBuffer()
{
  int fdflags;
  fdflags = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, fdflags | O_NONBLOCK);
  while (getchar()!=EOF);
  fcntl(STDIN_FILENO, F_SETFL, fdflags);
}


char *serializationMessage(Peticion peticion)
{

    char *serialization = (char *)malloc(sizeof(char) * peticion.n_address * MAX_CHAR * MAX_CHAR );
    
    strcat(serialization,"message:[");
    strcat(serialization, peticion.message);
    strcat(serialization, "];");
    strcat(serialization,"address:[");
    for(int i = 0 ; i < peticion.n_address ; i++){
        strcat(serialization,peticion.address[i]);
        strcat(serialization,",");
    }
    strcat(serialization,"]");
    return serialization;
}

Peticion desSerializacionMessage(){
    
}

void print(Peticion peticion){
    printf("Mensaje: %s\n",peticion.message);
    for(int i = 0 ; i < peticion.n_address ; i++){
        printf("address: %s\n",peticion.address[i]);
    }
}   

#endif
