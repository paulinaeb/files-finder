/*************************************************************************************/
/* @file    main.c                                                                   */
/* @brief   Menu principal de file finder TCP, utilizando hilos                      */       
/*************************************************************************************/

//headers
#include "headers/tcp_thread_server.h"
#include "headers/tcp_thread_client.h"
#include "headers/utilities.h"

//hilos
#include <pthread.h>

//Seleccion de Cliente o Servidor
int mainMenu(){
    int input = 0;

    system("clear");
    printf("Files Finder\n\n");
    printf("(1) SERVIDOR TCP (Hilos)\n(2) CLIENTE TCP (Hilos)\n(3) SALIR\n?");
    scanf("%d", &input);          

    return input;
}

//Seleccion de puerto
int getPort()
{
    char decition = 'x';
    int port = 2002;

    printf("Puerto por defecto(2002)\nDeseas cambiar el puerto? s/n ");
    scanf(" %c", &decition);

    if (decition == 's' || decition == 'S'){
        printf("Ingresa el puerto que quiere utilizar: ");
        scanf("%d", &port);
    }

    return port;
}

// programa principal
int main(){
    int  port;                  // puerto

    char serv_addr[15];         // direccion IP de un servidor
    Direccion *address = NULL;  // lista de direcciones IP de los servidores a buscar
    char instruction[100];  	// consulta a preguntar a los servidores
     
    int  input = mainMenu();    // seleccion de maquina cliente o servidor
	
    char d2 = 'x';
    
    while (input != 3){ 
    
        switch (input){

        // servidor    
        case 1:
            port=getPort();
            runServer_tcp_t(port);
            break;
        
        // cliente
        case 2:
            port=getPort();

            do{
                printf("Ingresa el servidor para la conexion: ");
                scanf("%s", serv_addr);
                
                address = addDireccion(address, newDireccion(serv_addr));

                printf("Desea agregar otra direccion? s/n ");
                scanf(" %c", &d2);
            } while (d2 == 's' || d2 == 'S');  //VALIDAR

            cleanBuffer();

            printf("\nIngresa el nombre del archivo/carpeta que deseas buscar: ");
            fgets(instruction, sizeof(instruction), stdin);

            while (address != NULL){
                runClient_tcp_t(port, address->address, instruction);
                address = address->next;
            }
            pausa();            
            break;

        // input incorrecto
        default:
            printf("Opcion incorrecta\n");
            pausa();
            break;
        }
        input = mainMenu();
    }

    // salir
    return EXIT_SUCCESS;
}
