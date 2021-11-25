// Client side implementation of UDP client-server model
#ifndef UDPCLIENTE_H
#define UDPCLIENTE_H
#include "Utilities.h"
#define MAXLINE 1024
// #define IP_SERVER "127.0.0.1"
// Driver code

// void client(int PORT,char* IP_SERVER)
void *client(void *args)
{
	Conexion *conexion = (Conexion *)args;
	int sockfd;
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
	servaddr.sin_port = htons(conexion->PORT);
	servaddr.sin_addr.s_addr = inet_addr(conexion->IP_SERVER);

	// while (1)
	// {
		char buffer[MAXLINE];
		// char test[MAXLINE];
		// char *instruction;
		// cleanBuffer();
		// printf("Ingresa el nombre de el archivo/carpeta que deseas buscar: ");
		// fgets(test, sizeof(test), stdin);
		// instruction = (char *)malloc(sizeof(test) * strlen(test));
		// strcat(instruction, test);

		socklen_t n, len;

		sendto(sockfd, (const char *)conexion->message, strlen(conexion->message),
			   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
			   sizeof(servaddr));
		printf("message sent.\n");

		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					 MSG_WAITALL, (struct sockaddr *)&servaddr,
					 &len);
		buffer[n] = '\0';
		
		printf("Server %s response: \n%s\n",conexion->IP_SERVER,buffer);
		
		// if (strncmp(conexion->message, "exit", 4) == 0)
		// {
			close(sockfd);
	// 		break;
	// 	}
	// }
}

void runClient(int port, char *address)
{
	Conexion conexion;

	pthread_t hilo;
	conexion.PORT = port;
	strcpy(conexion.IP_SERVER, address);
	pthread_create(&hilo, NULL, client, (void *)&conexion);
	pthread_join(hilo,NULL);
}

#endif