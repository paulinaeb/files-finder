/*************************************************************************************/
/* @file    main.c                                                                   */
/* @brief   Menu principal de file finder TCP, utilizando hilos y procesos           */       
/*************************************************************************************/
//librerias
#include "lib/tcp_thread_server.h"
#include "lib/tcp_thread_client.h"
#include "lib/utils.h"
#include "lib/tcp_process_server.h"
#include "lib/udpserver.h"
#include "lib/udpcliente.h"

//variable global
int port=2002;

int mainMenu(){
    int input = 0;
    system("clear");
    printf("\n*******************************************\n");
    printf("************** Files Finder ***************\n");
    printf("*******************************************\n");
    printf("\nSelecciona una opcion\n\n");
    printf("\n-->Conexion TCP\n\n");
    printf("(1) SERVIDOR (Hilos) \n(2) SERVIDOR (Procesos)\n(3) CLIENTE \n");
    printf("\n-->Conexion UDP\n\n");
    printf("(4) SERVIDOR \n(5) CLIENTE \n(6) CAMBIAR PUERTO ACTUAL (%d)\n\n\n(7) AYUDA\n(8) SALIR\n\n",port);
    printf("Opcion: ");
    scanf("%d", &input);          
    return input;
}

//Seleccion de puerto
void getPort(){
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

    char serv_addr[20];         //direccion IP de un servidor
    Direccion *address = NULL;  //Lista de direcciones IP de los servidores a buscar
    char instruction[1024];  	//Consulta a preguntar a los servidores 
    int  input = mainMenu();    //Respuesta a consulta del menu principal
    char decition = ' ';
    
    while (input != 8){ 
        switch (input){
        //Servidor    TCP hilos
        case 1: 
            runServer_tcp_t(port);
            break; 
        // servidor TCP procesos
        case 2:
            runServer_tcp_p(port);
            break;
        // cliente TCP 
        case 3: 
        do{
            printf("Ingresa el servidor para la conexion: ");
            scanf("%s", serv_addr);
            address = addDireccion(address, newDireccion(serv_addr));
            printf("Desea agregar otra direccion? s/n ");
            scanf(" %c", &decition);
        } 
        while (decition == 's' || decition == 'S');  //VALIDAR
        cleanBuffer();
        printf("\nIngresa el nombre del archivo/carpeta que deseas buscar: ");
        fgets(instruction, sizeof(instruction), stdin);
        while (address != NULL){
            runClient_tcp_t(port, address->address, instruction);
            address = address->next;
        }
        pausa();
        break;
        //servidor udp
        case 4:
            server(port);
            break;
        //cliente udp
        case 5:
        do{
            printf("Ingresa el servidor para la conexion: ");
            scanf("%s", serv_addr);
            address = addDireccion(address, newDireccion(serv_addr));
            printf("Desea agregar otra direccion? s/n ");
           scanf(" %c", &decition);
        } while (decition == 's' || decition == 'S');
        cleanBuffer();
        printf("Ingresa el nombre de el archivo/carpeta que deseas buscar: ");
        fgets(instruction, sizeof(instruction), stdin);
        while (address != NULL){
            runClient(port, address->address, instruction);
            address = address->next;
        }
        printf("Presiona enter para continuar...\n");
        pausa();
        break;
        //cambiar puerto
        case 6: 
            getPort(); 
            break;
        //mostrar ayuda
        case 7:
            printf("***************AYUDA*************");
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
