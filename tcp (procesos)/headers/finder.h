/*************************************************************************************/
/* @file    finder.h                                                                 */
/* @brief   busqueda de archivos en el servidor                                      */
/*************************************************************************************/

#ifndef _finder_h
#define _finder_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funcion para copiar y contqar los caracteres de la busqueda
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

//funcion retorna el resultado de la busqueda realizada en el servidior
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
