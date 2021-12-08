// Client side implementation of UDP client-server model
#ifndef UDPCLIENTE_H
#define UDPCLIENTE_H
#include "utils.h"
#define MAXLINE 1024
// Driver code

void *client(void *args){
	Conexion *conexion = (Conexion *)args;
	int sockfd;
	struct sockaddr_in servaddr;
	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(conexion->PORT);
	servaddr.sin_addr.s_addr = inet_addr(conexion->IP_SERVER);
	char buffer[MAXLINE];
	socklen_t n, len;
	sendto(sockfd, (const char *)conexion->message, strlen(conexion->message),
	MSG_CONFIRM, (const struct sockaddr *)&servaddr,
   sizeof(servaddr)); 
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				 MSG_WAITALL, (struct sockaddr *)&servaddr,
				 &len);
	buffer[n] = '\0';
	if (n==0){
		printf("\nNo se hallaron resultados en el servidor de IP: %s\n",conexion->IP_SERVER);
	}
	else{
		printf("\nServer %s response: \n%s\n", conexion->IP_SERVER, buffer); 
		
	}
	close(sockfd);
}

void runClient(int port, char *address,char*message){
	Conexion conexion;
	pthread_t hilo;
	conexion.PORT = port;
	strcpy(conexion.IP_SERVER, address);
	strcpy(conexion.message, message);
	pthread_create(&hilo, NULL, client, (void *)&conexion);
	pthread_join(hilo, NULL);
}

#endif
