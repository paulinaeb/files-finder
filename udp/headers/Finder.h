#ifndef FINDER_H
#define FINDER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char*out;
/**
 * @brief 
 * @description: esta funcion permite contar los caracteres de un archivo 
 * @param filename 
 * @return int 
 */

int fsize(char *filename)
{

    FILE *fp = popen(filename, "r");
    char caracter;
    int i = 0;
    if (fp == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
        return 0;
    }
    else
    {

        while ((caracter = fgetc(fp)) != EOF)
        {
            i++;
        }
    }

    pclose(fp);

    return i;
}

/**
 * @brief 
 * @description: esta funcion retorna el archivo completo de las rutas de los archivos en la pc
 * @param input 
 * @return char* 
 */

char *gfind(char *input)
{
    char *FIND = "find /home -iname ";
    char *query = (char *)malloc(sizeof(input) * sizeof(input) + 1);
    strcat(query, FIND);
    strcat(query, input);
    out = malloc(sizeof(char) * fsize(query));
    // fshow(query, out);
    return out;
}



#endif