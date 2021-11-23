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
    
    char decition = 'x';
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
            client(port);
            break;
        default:
            printf("ERROR OPCION INCORRECTA ENTER PARA CONTINUAR\n");
            while (getchar()!='\n');
            break;
        }
        input = mainmenu();
        
    }

    return EXIT_SUCCESS;
}
