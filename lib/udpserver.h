/************************************************
* Crea un servidor UDP. Recibe como argumento
* en linea de comandos el numero de puerto. El servidor
* nunca termina su ejecucion
***************************************/
#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "finder.h" 

// #define PORT 2002
#define TAMANO 1024
void error_fatal(char *msg){
    perror(msg);
    exit(1);
}

void server(int PORT){
    int sock;
    struct sockaddr_in server;
    struct sockaddr_in from;
    socklen_t length, fromlen, n;
    char buffer[TAMANO];

    /* (1) creacion del socket del servidor*/

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        error_fatal("Creando el socket");
    length = sizeof(server);
    memset(&server, 0, length); /*limpio la direccion del socket del servidor*/

    /* (2) vinculo la direccion IP y puerto local al socket creado anteriormente */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr *)&server, length) < 0)
        error_fatal("binding");
    fromlen = sizeof(from);

    /* (3) bucle principal. Pongo a recibir y responder mensajes a traves del socket*/ 
    printf("\n[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(server.sin_port)); 
    while (1){ 
        n = recvfrom(sock, buffer, TAMANO, 0, (struct sockaddr *)&from, &fromlen);
        if (n < 0){
            error_fatal("recvfrom");
        }
        /*datagrama recibido*/
        buffer[n] = '\0'; /* para poder imprimirlo con prinft*/
        printf("Recibido en el servidor: %s", buffer);
        /*enviar respuesta*/
        char *query = gfind(buffer);
        n = sendto(sock, query, strlen(query), 0, (struct sockaddr *)&from, fromlen);
        // n = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&from, fromlen);
        if (strncmp(buffer, "exit", 4) == 0){
            close(sock);
            break;
        }
        if (n < 0){
            error_fatal("sendto");
        }   
    }
}

#endif