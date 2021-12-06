#ifndef FINDER_H
#define FINDER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 
 * @description: esta funcion permite contar los caracteres de un archivo 
 * @param filename 
 * @return int 
 */

int fsize(char *filename){
    FILE *fp = popen(filename, "r");
    char caracter;
    int i = 0;
    if (fp == NULL){
        printf("\nError de apertura del archivo. \n\n");
        return 0;
    }
    else{

        while ((caracter = fgetc(fp)) != EOF){ 
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

char *gfind(char *input){
    int type_search;
    char cad_type_search [3];
    char cad_search [6];
    for (int i = 0; i < sizeof(input); i++){
        if(i <6){
            strcat(cad_search,tolower((unsigned char)input[i]));
        }
        else if(i >= 6 && i < 9){
            strcat(cad_type_search,input[i]);
        }
    }

    if(strcmp(cad_search, "buscar") != 0){
        printf("Comando invalido");
    }else{
        if(strcmp(cad_type_search, " ./")){
            printf("Es por extension");
        }else if(strcmp(cad_type_search, " $/")){
            printf("Es normal");
        }else if(strcmp(cad_type_search, " -/")){
            printf("Es por nombre");
        }else{
            printf("Comando invalido");
        }
    }
    
    char*out;
    char *FIND = "find /home -iname ";
    char *query = (char *)malloc(sizeof(input) * sizeof(input) + 1);
    strcat(query, FIND);
    strcat(query, input);
    out = malloc(sizeof(char) * fsize(query)); 
    return out;
}

#endif