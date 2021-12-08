/*************************************************************************************/
/* @file    tcp_thead_server.h                                                       */
/* @brief   cliente tcp utilizando sockets e hilos                                   */
/*************************************************************************************/

#ifndef _tcp_thead_client_h
#define _tcp_thead_client_h
#include <unistd.h>  
#include <stdlib.h> 
//sockets
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
//strings / errores
#include <stdio.h> 
#include <string.h> 
//finder / utilities
#include "finder.h"
#include "utils.h"
//hilos
#include <pthread.h>
#define BUF_SIZE    500

void *client_tcp_t(void *args){
    char buf_rx[BUF_SIZE]=" ";                       // buffer de recepcion
    Conexion *conexion = (Conexion *)args;
    int sockfd;
    struct sockaddr_in servaddr;
    // creacion del socket del cliente - socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1){ 
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        pausa();
        return NULL;
    } 
    else{
        printf("[CLIENT]: Socket successfully created\n"); 
    }

    // conexion con el socket del servidor - connect()
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(conexion->IP_SERVER);
    servaddr.sin_port        = htons(conexion->PORT); 
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0){ 
        printf("[SERVER-error] connection with the server failed\n");  
        pausa();
        return NULL;
    } 
    else{
    	printf("[CLIENT]: connected to SERVER %s\n",conexion->IP_SERVER); 
    }
   
    // Envio de consulta y lectura de respuesta - write() / read()
    write(sockfd, conexion->message, sizeof(conexion->message));  
    int n = read(sockfd, buf_rx, BUF_SIZE);
    buf_rx[n]='\0'; 
    if (n==0){
        printf("\nNo se hallaron resultados en el servidor de IP: %s",conexion->IP_SERVER);
    }
    else {
        printf("\n[SERVER %s] response: \n%s",conexion->IP_SERVER,buf_rx);
    }
    // cerramos el socket con el servidor - close()
    printf("\n[CLIENT]: socket closed \n\n");
    close(sockfd); 
}

void runClient_tcp_t(int port, char *address, char *message){
	Conexion conexion;
	pthread_t hilo;
	conexion.PORT = port;
	strcpy(conexion.IP_SERVER, address);
	strcpy(conexion.message, message);
	pthread_create(&hilo, NULL, client_tcp_t, (void *)&conexion);
	pthread_join(hilo, NULL);
}
#endif
