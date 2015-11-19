#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"


double parse(char * line){
    char * tok = strtok(line,"\t\r\n");
    while(tok != NULL){
        if(get_type(tok) == NUMBER)
            printf("YAY\n");
        else
            printf("NAY\n");
        tok = strtok(NULL,"\t\r\n");
    }
    return 0;
}

SP_STACK_ELEMENT_TYPE get_type(char * tok){
    if(is_number(tok))
        return NUMBER;
    return PLUS;
}

bool is_number(char * tok){
    int i =0;
    while(tok[i] != '\0'){
        if(tok[i] < '0' || tok[i] > '9')
            return false;
        i++;
    }
    return true;
}
bool is_exit(char * tok){
    char * temp = (char *) malloc(3);
    strncpy(temp,tok,2);
    if(strcmp(temp,"<>")==0 && strlen(tok) == 3)
        return true;
    return false;
}
