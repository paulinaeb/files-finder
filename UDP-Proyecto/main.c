#include "headers/udpserver.h"
#include "headers/udpcliente .h"



int mainmenu()
{
    int input = 0;
    system("clear");
    printf("BIENVENIDO AL MENU DEL FILES FINDER\n");
    printf("1. SER SERVIDOR\n2. SER CLIENTE\n3. SALIR\n?");
    scanf("%d", &input);
    return input;
}

int main()
{
    int port = 2002;
    int input = mainmenu();
    char addr[255];
    char decition = 'x';
    Direccion *address = NULL;
    char instruction[MAXLINE];

    while (input != 3)
    {
        printf("Puerto por defecto(2002)\nDeseas cambiar el puerto? s/n ");
        scanf(" %c", &decition);

        if (decition == 's' || decition == 'S')
        {
            printf("Ingresa el puerto que quiere utilizar: ");
            scanf("%d", &port);
        }
        switch (input)
        {
        case 1:
            server(port);
            break;
        case 2:
            do
            {
                printf("Ingresa el servidor para la conexion: ");
                scanf("%s", addr);
                address = addDireccion(address, newDireccion(addr));
                printf("Desea agregar otra direccion? s/n ");
                scanf(" %c", &decition);
            } while (decition == 's' || decition == 'S');
            cleanBuffer();
            printf("Ingresa el nombre de el archivo/carpeta que deseas buscar: ");
            fgets(instruction, sizeof(instruction), stdin);
            // client(port, addr);
            Conexion conexion;
            conexion.PORT = port;
            strcpy(conexion.message, instruction);
            while (address != NULL)
            {
                pthread_t hilo;
                strcpy(conexion.IP_SERVER, address->address);
                pthread_create(&hilo, NULL, client, (void *)&conexion);
                pthread_join(hilo, NULL);
                address = address->next;
            }
            pausa();
            break;
        default:
            printf("ERROR OPCION INCORRECTA ENTER PARA CONTINUAR\n");
            pausa();
            break;
        }
        input = mainmenu();
    }

    return EXIT_SUCCESS;
}
