/*************************************************************************************/
/* @file    main.c                                                                   */
/* @brief   Menu principal de file finder TCP, utilizando hilos y procesos           */       
/*************************************************************************************/

//headers
#include "headers/tcp_thread_server.h"
#include "headers/tcp_thread_client.h"
#include "headers/utilities.h"

//hilos
#include <pthread.h>

//Seleccion de Cliente o Servidor
int port=2002;

int mainMenu(){
    int input = 0;
    system("clear");
    printf("Files Finder\n\n");
    printf("(1) SERVIDOR TCP (Hilos)\n(2) CLIENTE TCP (Hilos)\n(3) CAMBIAR PUERTO ACTUAL (%d)\n(4) SALIR\n",port);
    scanf("%d", &input);          
    return input;
}

//Seleccion de puerto
void getPort()
{
    char decition = ' ';
    int resp = 0;
    printf("Puerto actual: %d\nDeseas cambiar el puerto? s/n ", port);
    scanf(" %c", &decition);
    if (decition == 's' || decition == 'S'){
        printf("Ingresa el puerto que quiere utilizar: ");
        scanf("%d", &resp);
        port=resp; 
    }  
}

int main(){ 

    char serv_addr[15];         //direccion IP de un servidor
    Direccion *address = NULL;  //Lista de direcciones IP de los servidores a buscar
    char instruction[100];  	//Consulta a preguntar a los servidores CHQUEAR TAMAÑP
    int  input = mainMenu();    //Respuesta a consulta del menu principal
    char d2 = ' ';
    
    while (input != 4){ 
    
        switch (input){
        //Servidor    
        case 1: 
            runServer_tcp_t(port);
            break;
        //Cliente
        case 2: 
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
        case 3: 
            getPort(); 
            break;

        //Input incorrecto
        default:
            printf("Opcion incorrecta\n");
            pausa();
            break;
        }
        input = mainMenu();
    }

    //Salir
    return EXIT_SUCCESS;
}
