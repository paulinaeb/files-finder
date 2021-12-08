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
        int tamanio = strlen(aux) - 3;
        int inicio = 3;
        strncpy(file, aux + inicio, tamanio);
     //   printf("File:%s\n",file);
}

char *gfind(char *input){   
    char *aux =input;
    char *out;
    char cad_type_search [3]=""; //" ./"
    char cad_search [6]=" ";  //buscar
    int j=0;
    int i=0; 
    int flag=0;
    char *FIND;
    char aux_file[100]=" ";
    
    while(*input != '\0'){ 
        if(i<6){ 
            cad_search[i]=*input;
            i++;  
            input++;
        }
        if(i>=6){
        	break;
        } 
    }   
    int tamanio = 3;
    int inicio = 0;
    char cadena[100] = "";
    strncpy(cadena, input + inicio, tamanio); 
 
    for (int i = 0; i < strlen(cad_search); i++){
        cad_search[i] = tolower(cad_search[i]);
    }

    if(strcmp(cad_search, "buscar") != 0){
        printf("Comando invalido\n"); 
    return "\nComando invalido\n";
    }else{
        if(strcmp(cadena, " ./") == 0){
            flag=1;
            filesSearch(input);
            printf("\n****Busqueda por extension****\n");
            int j=0;
            strcat(file, "\""); 
            for (int i=0;i<strlen(file);i++){
            	if (file[i]!='\n'){ 
            	    aux_file[j]=file[i];
            	    j++;
            	}
            }
            aux_file[j]='\0'; 
            FIND = "find /home -name \"*.";
        }
        else if(strcmp(cadena, " $/") == 0){
            filesSearch(input);
            printf("\n****Busqueda por nombre+extension o carpetas****\n"); //nombre y extension
            FIND = "find /home -iname ";
        }
        else if(strcmp(cadena, " -/") == 0){
            filesSearch(input);
            printf("\n****Busqueda de archivos vacio****s\n"); 
            FIND = "find /home -type f -";
        }
        else if(strcmp(cadena, " #/") == 0){
            filesSearch(input);
            printf("\n****Busqueda de directorios vacios****\n"); 
            FIND = "find /home -type d -";
        }
        else{
            printf("Comando invalido\n"); 
            return "\nComando invalido\n";
        }
    }
     
    char *query;
    if (flag==1)
    	query = (char *)malloc(sizeof(aux_file) * sizeof(aux_file) + 1);
    else 
    	query = (char *)malloc(sizeof(file) * sizeof(file) + 1);
    	
    strcat(query, FIND);
    if (flag==1)
    	strcat(query, aux_file);
    else 
    	strcat(query, file);
    out = malloc(sizeof(char) * fsize(query)); 
    return out;
}

#endif
