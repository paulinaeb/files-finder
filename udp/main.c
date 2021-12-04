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

int getPort()
{
    char decition = 'x';
    int port = 2002;
    printf("Puerto por defecto(2002)\nDeseas cambiar el puerto? s/n ");
    scanf(" %c", &decition);

    if (decition == 's' || decition == 'S')
    {
        printf("Ingresa el puerto que quiere utilizar: ");
        scanf("%d", &port);
    }
    return port;
}

int main()
{
    int port;
    int input = mainmenu();
    char addr[255];
    char decition = 'x';
    Direccion *address = NULL;
    char instruction[MAXLINE];

    while (input != 3)
    {
        switch (input)
        {
        case 1:
            port=getPort();
            server(port);
            break;
        case 2:
            port=getPort();
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
            while (address != NULL)
            {
                runClient(port, address->address, instruction);
                address = address->next;
            }
            printf("Presiona enter para continuar...\n");
            pausa();
            break;
        default:
            printf("Opcion incorrecta Presiona enter para continuar...\n");
            pausa();pausa();
            break;
        }
        input = mainmenu();
    }

    return EXIT_SUCCESS;
}
