/***************************************************************************************/
/* @file    server_secuencial.c                                                        */
/* @brief   Secuencial server. TCP sockets                                             */
/***************************************************************************************/

/*standard symbols */
#include <unistd.h>  

/* sockets */
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>

/* strings / errors*/
#include <errno.h>
#include <stdio.h> 
#include <string.h> 

/* server parameters */
#define SERV_PORT       8080              /* port */
#define BUF_SIZE        100               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */
int connfd [10];
int aux = 0;

int main(int argc, char* argv[])          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client; 
    
    int  len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    char buff_mj[BUF_SIZE] = "Hello ya se hizo la conexion";
     
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[SERVER]: Socket successfully created..\n"); 
    }
    
    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port        = htons(SERV_PORT); 
    
    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[SERVER]: Socket successfully binded \n");
    }
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    len = sizeof(client); 
  
      /* Accept the data from incoming sockets in a iterative way */
    while(aux < 2){
      connfd[aux] = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd[aux] < 0) 
        { 
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        } 
        else
        {              
            len_rx = read(connfd[aux], buff_rx, sizeof(buff_rx));  
                
            if(len_rx == -1){
                fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
            }
            else if(len_rx == 0){  /* if length is 0 client socket closed, then exit */
                printf("[SERVER]: client socket closed \n\n");
                close(connfd[aux]);
                break; 
            }
            else{  
                write(connfd[aux], buff_tx, strlen(buff_tx));
                printf("Cliente %i \n",connfd[aux]);
                aux = aux + 1;
                printf("%i \n",aux);
                printf("[SERVER]: %s \n",buff_rx);
            }  
        }                  
    }
    for (int i=0; i < aux; i++){
        write(connfd[i], buff_mj, strlen(buff_mj));
    }  
} 