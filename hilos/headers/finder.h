/*************************************************************************************/
/* @file    finder.h                                                                 */
/* @brief   busqueda de archivos en la maquina                                       */
/*************************************************************************************/

#ifndef _finder_h
#define _finder_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *out;

//esta funcion para contar los caracteres de un archivo 
int fsize(char *filename){

    FILE *fp = popen(filename, "r");
    char caracter;
    int i = 0;
    
    if (fp == NULL){
        printf("\nError de apertura del archivo. \n\n");
        return 0;
    }
    else{
        while ((caracter = fgetc(fp)) != EOF) { i++; }
    }

    pclose(fp);

    return i;
}

//funcion retorna el archivo completo de las rutas de los archivos en la pc
char *gfind(char *input){
    char *out;
    
    char FIND[] = "find /home -iname ";
    char query[500];
    
    strcat(query, FIND);
    strcat(query, input);
    
    out = malloc(sizeof(char) * fsize(query));
        
    return out;
}

#endif
