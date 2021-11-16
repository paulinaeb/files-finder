#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int opcion;
    do{
        printf("***Bienvenido a su buscador de archivos y directorios***\n\n");
        printf("1. Menu de busqueda\n\n");
        printf("2. Puertos disponibles\n\n");
        printf("3. Ayuda\n\n");
        printf("4. Salir\n\n");
        scanf( "%d", &opcion);
        switch ( opcion ){
            case 1:{
                // //declaracion de variables
                char* buscador = "find /home -iname "; //busca en todos los directorios de la pc, no distingue mayus-minus
                char* busqueda; //almacena nombre ingresado por el usuario
                char* query;
                printf("Ingresa el archivo o carpeta que deseas buscar: ");
                scanf("%s",busqueda);
                query = (char*)malloc(sizeof(buscador)*sizeof(busqueda)+1); 
                strcat(query,buscador);
                strcat(query,busqueda); 

                FILE *fp = popen(query, "r");
                if (fp != NULL) {
                    char number[200]; //resultado del comando, seria bueno cambiarlo a puntero y hacer el malloc y el free despues
                    if (fgets(number, sizeof(number), fp))
                        printf("%s\n", number);
                    else 
                        printf("No se encontro el archivo/carpeta que ha indicado\n\n");
                    pclose(fp);
                }
                free(query);
            }
                break;
            case 2:
                printf("En construccion\n\n");
                break;
            case 3:
                printf("En construccion\n\n");
                break;
        }
    }while (opcion!=4);
    
    return 0;
}
