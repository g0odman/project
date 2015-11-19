#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Stack.h"

double parse(char * line){
    char * tok = strtok(line,"\t\r\n");
    while(tok != NULL){
        printf("%s\n",tok);
        fflush(stdout);
        tok = strtok(NULL,"\t\r\n");
    }
    return 0;
}

