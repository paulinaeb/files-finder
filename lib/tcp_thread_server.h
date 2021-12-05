/*************************************************************************************/
/* @file    tcp_thead_server.h                                                       */        
/* @brief   servidor tcp utilizando sockets e hilos                                  */
/*************************************************************************************/
#ifndef _tcp_thead_server_h
#define _tcp_thead_server_h
#include <unistd.h>  
//sockets
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
//hilos
#include <pthread.h>
//finder / utilities
#include "finder.h"
#include "utils.h"
//strings / errores
#include <errno.h>
#include <stdio.h> 
#include <string.h> 
//Parametros para el servidor
#define BUF_SIZE    500    // tamaño del buffer de recepcion y transmision de datos  
#define BACKLOG     5      // cola de espera de clientes

void *connection_handler(void *p_connfd){
    int connfd = *((int*)p_connfd);
    free(p_connfd);
    int  len_rx, len_tx = 0;                    // Tamaño de lo recibido y enviado, en bytes
    char buff_tx[BUF_SIZE], buff_rx[BUF_SIZE];  // Buffer de trasnmision (tx) y recepcion (rx)
    // recibe la consulta en el buffer de recepcion	- read()	          
    len_rx = read(connfd, buff_rx, sizeof(buff_rx));  
    if(len_rx == -1){
        fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
        pausa();
        return NULL;
    }
    else{  
    // realiza busqueda y guarda los resultados de la consulta en el buffer de trasnmision              
    char *buff_tx = gfind(buff_rx);	              
	buff_rx[strlen(buff_rx)-1] = '\0';
    printf("[CLIENT]: Search for \"%s\"\n",buff_rx);
    // envia respuesta - write()
    write(connfd, buff_tx, strlen(buff_tx));     
    // imprime respuesta
    printf("[SERVER]: Results from \"%s\"\n",buff_rx);
    printf("%s",buff_tx);
    // cerramos el socket con el cliente - close()
    printf("[SERVER]: socket closed \n\n");
    close(connfd);
    }  
}

void runServer_tcp_t(int PORT){ 
    int sockfd, connfd;                         // listening and connection socket file descriptor
    unsigned int len;                           // Tamaño de la direccion del cliente
    struct sockaddr_in servaddr, client;        // Socket address format for server and client
                            
    // creacion del socket del servidor - socket()
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1){ 
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        pausa();
        return; 
    } 
    else{
        printf("\n[SERVER]: Socket successfully created\n"); 
    }
    // vinculo la direccion IP y puerto local al socket creado anteriormente - bind()
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port        = htons(PORT); 
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0){ 
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
    	pausa();
        return;
    } 
    else{
        printf("[SERVER]: Socket successfully binded \n");
    }
    // escuchar clientes para ser atendidos - listen()
    if ((listen(sockfd, BACKLOG)) != 0){ 
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        pausa();
        return; 
    } 
    else{
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    // ciclo de espera de clientes
    while(1){
        // aceptar coneccion de un cliente - accept()
        len = sizeof(client); 
        connfd = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd < 0){ 
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            pausa();
            return; 
        } 
        else{
            // manejador de conexiones    
            pthread_t hilo;
            int *p_connfd = malloc(sizeof(int));
            *p_connfd = connfd;
            pthread_create(&hilo, NULL, connection_handler, p_connfd);                                         
        }                  
    }  
}

#endif
