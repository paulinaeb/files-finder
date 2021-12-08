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
#include "lib/finder.h"

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
    printf("(1) SERVIDOR (Hilos) \n(2) CLIENTE (Hilos)\n(3) SERVIDOR (Procesos)\n(4) CLIENTE (Procesos)\n");
    printf("\n-->Conexion UDP\n\n");
    printf("(5) SERVIDOR \n(6) CLIENTE \n\n\n(7) AYUDA\n(8) SALIR\n\n");
    printf("Opcion: ");
    scanf("%d", &input);          
    return input;
}

//Seleccion de puerto
void getPort(int static_port){
    char decition = ' ';
    int resp = 0;
    port = static_port;
    printf("Puerto actual: %d\nDeseas cambiar el puerto? s/n ", static_port);
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
    char* inst=instruction;
    char* rlocal;
    int  input = mainMenu();    //Respuesta a consulta del menu principal
    char decition = ' ';
    char resp=' ';
    char buscarlocal=' ';
    while (input != 8){ 
        switch (input){
        //Servidor    TCP hilos
        case 1: 
            getPort(2020);
            runServer_tcp_t(port);
            break; 
        // servidor TCP procesos
        case 3:
            getPort(2002);
            runServer_tcp_p(port);
            break;
        // cliente TCP procesos o hilos
        case 2: //cliente hilos
        case 4: //cliente procesos
        if (input==2)
                port=2020;
        else 
            port=2002;
        getPort(port);
        do{
            printf("Ingresa la direccion IP del servidor para la conexion: ");
            scanf("%s", serv_addr);
            address = addDireccion(address, newDireccion(serv_addr));
            printf("Desea agregar otra direccion? s/n ");
            scanf(" %c", &decition);
        } 
        while (decition == 's' || decition == 'S');  //VALIDAR
        printf("Desea buscar tambien en la PC local? s/n ");
        scanf(" %c",&buscarlocal);
        cleanBuffer();
        system("clear"); 
        printf("\nIngresa el comando de busqueda : ");
        fgets(instruction, sizeof(instruction), stdin);
        if (buscarlocal=='s' || buscarlocal=='S'){
        	rlocal=gfind(inst);
        	printf("\nBusqueda local:\n%s\n",rlocal);
        }
        while (address != NULL){
            runClient_tcp_t(port, address->address, instruction);
            address = address->next;
        }
        printf("\n\nPresiona enter para volver al menu...\n");
        pausa();
        break;
        //servidor udp
        case 5:
            getPort(2002);
            server(port);
            break;
        //cliente udp
        case 6:
        getPort(2002);
        do{
            printf("Ingresa la direccion IP del servidor para la conexion: ");
            scanf("%s", serv_addr);
            address = addDireccion(address, newDireccion(serv_addr));
            printf("Desea agregar otra direccion? s/n ");
           scanf(" %c", &decition);
        } while (decition == 's' || decition == 'S');
        printf("Desea buscar tambien en la PC local? s/n ");
        scanf(" %c",&buscarlocal);
        cleanBuffer();
        system("clear");
        printf("Ingresa el comando de busqueda: ");
        fgets(instruction, sizeof(instruction), stdin);
        if (buscarlocal=='s' || buscarlocal=='S'){
        	rlocal=gfind(inst);
        	printf("\nBusqueda local:\n%s\n",rlocal);
        }
        while (address != NULL){
            runClient(port, address->address, instruction);
            address = address->next;
        }
        printf("\n\nPresiona enter para volver al menu...\n");
        pausa();
        break; 
        //mostrar ayuda
        case 7:  
            system("clear"); 
            printf("\n*******************************************\n");
            printf("************ Ayuda Files Finder ************\n");
            printf("*******************************************\n");
            printf("\n Files finder es un buscador de archivos personalizado inspirado en\n");
            printf("la funcionalidad del comando FIND en Linux. Ademas, permite crear conexiones\n");
            printf("con distintos servidores desde un cliente a fin de realizar una misma busqueda\n");
            printf("en cada servidor y devolver un resultado. \n\nLos protocolos de conexion permitidos\n");
            printf("son TCP (implementado con hilos), TCP (implementado con procesos) y UDP. Cada una de\n");
            printf("ellas tendra un puerto asignado por defecto. En caso de querer cambiarlo, el usuario\n");
            printf("podra hacerlo justo despues de haber seleccionado su opcion preferida mostrada por el\n");
            printf("menu principal. Desde el cliente seleccionado se pediran las direcciones IP de los\n");
            printf("servidores donde se desea realizar la busqueda. Ademas, el buscador tambien es capaz\n");
            printf("de buscar en la PC del cliente, en caso de que el usuario asi lo desee. \n\n");
            printf("Una vez establecida la conexion, el usuario podra realizar las busquedas, segun el\n");
            printf("comando indicado. Las reglas estan establecidas de la siguiente manera:\n\n");
            printf("1. Busqueda de todos los archivos de una extension determinada\n");
            printf("Comando a utilizar: buscar ./[extension]\n");
            printf("Ejemplo: buscar ./h\n");
            printf("El comando anterior traera la ubicacion de tdos los archivos de extension .h\n\n");
            printf("2. Busqueda de archivos con extension o directorios\n");
            printf("Comando a utilizar: buscar $/[nombre de archivo+su extension o nombre del directorio]\n");
            printf("Ejemplo 1: buscar $/files-finder\n");
            printf("El comando anterior traera la ubicacion de todos los directorios files-finder\n");
            printf("Ejemplo 2: buscar $/main.c\n");
            printf("El comando anterior traera la ubicacion de todos los archivos llamados main.c\n\n");
            printf("3. Busqueda de archivos vacios\n");
            printf("Comando a utilizar: buscar -/empty\n");
            printf("4. Busqueda de directorios vacios\n");
            printf("Comando a utilizar: buscar #/empty\n");
            printf("\nPresione s+Enter para volver al menu\n");
            scanf("\nRespuesta: %c",&resp);
            if (resp=='s')    
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
