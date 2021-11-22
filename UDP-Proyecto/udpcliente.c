// Client side implementation of UDP client-server model
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
#include "headers/ClienteUDP.h"
#define PORT 2002
#define MAXLINE 1024
#define IP_SERVER "127.0.0.1"
// Driver code
int main()
{
	while (1)
	{

		int sockfd;
		// char *buffer;
		char buffer[MAXLINE];
		// char *hello = "Hello from client";
		struct sockaddr_in servaddr;

		// Creating socket file descriptor
		if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			perror("socket creation failed");
			exit(EXIT_FAILURE);
		}

		memset(&servaddr, 0, sizeof(servaddr));

		// Filling server information
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(PORT);
		servaddr.sin_addr.s_addr = inet_addr(IP_SERVER);

		// Peticion peticion;
		int n_address = 0;
		int decision = 0;
		char test[255];
		// while (decision != 2)
		// {

		// 	printf("Ingresa la direccion: ");
		// 	fgets(peticion.address[n_address], sizeof(peticion.address), stdin);
		// 	cleanBuffer();
		// 	printf("Desea agregar otra direccion?  [1. si , 2.no] :");
		// 	scanf("%d", &decision);
		// 	cleanBuffer();
		// 	n_address++;
		// }
		// peticion.n_address = n_address;

		printf("Ingresa el nombre de el archivo/carpeta que deseas buscar: ");
		// fgets(peticion.message, sizeof(peticion.message), stdin);
		fgets(test, 255, stdin);

		socklen_t n, len;

		//SERIALIZACION PENDIENTE PARA VARIAS COMPUTADORAS

		// sendto(sockfd, (const char *)serializationMessage(peticion), strlen(serializationMessage(peticion)),
		// 	   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
		// 	   sizeof(servaddr));

		sendto(sockfd, (const char *)test, strlen(test),
			   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
			   sizeof(servaddr));
		printf("message sent.\n");

		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *)&servaddr,
					 &len);
		buffer[n] = '\0';
		printf("Server response: \n%s\n", buffer);

		if (strncmp(test, "exit", 4) == 0)
		{
			close(sockfd);
			break;
		}
	}
}
