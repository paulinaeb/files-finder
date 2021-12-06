#ifndef FINDER_H
#define FINDER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char file[100];

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

void filesSearch(char *aux){
        int tamanio = strlen(aux) - 10;
        int inicio = 9;
        strncpy(file, aux + inicio, tamanio);
        printf("File: %s\n",file);
}

char *gfind(char *input){  
    char *aux =input;
    char cad_type_search [3]; //" ./"
    char cad_search [6];  //buscar
    int i=0;
    int j=0;
    while(*input != '\0'){
        if(i<6){
            cad_search[i]=*input;
            i++;  
            input++;
        }
        if(i>=6){
            cad_type_search[j]=*input;
            j++;
            input++;
        }
        if (j==3){
            break;
        }
    } 
    printf("\nsearch: %s", cad_search); 
    printf("\nsearch 2: %s\n", cad_type_search); 

    for (int i = 0; i < strlen(cad_search); i++){
        cad_search[i] = tolower(cad_search[i]);
    }

    for (int i = 0; i < strlen(cad_type_search); i++){
        cad_type_search[i] = tolower(cad_type_search[i]);
    }

    if(strcmp(cad_search, "buscar") != 0){
        printf("Comando invalido");
    }else{
        if(strcmp(cad_type_search, " ./buscar") == 0){
            filesSearch(aux);
            printf("Es por extension");
        }else if(strcmp(cad_type_search, " $/buscar") == 0){
            filesSearch(aux);
            printf("Es normal");
        }else if(strcmp(cad_type_search, " -/buscar") == 0){
            filesSearch(aux);
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