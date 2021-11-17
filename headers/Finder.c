#include"Finder.h"



int main()
{

    char input[255], *query,route[255];

    printf("Ingresa el archivo o carpeta que deseas buscar: ");
    scanf("%s", input);
    query = gfind(input);
    printf("%s",query);
    
    
    return 0;
}
