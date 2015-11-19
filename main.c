#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"
#define MAX_LINE_LENGTH 200

int main(){
    char * line = (char *)malloc(MAX_LINE_LENGTH +1);
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        if(is_exit(line))
            break;
        parse(line);
    }
    printf("Exiting...\n");
    free(line);
    return 0;
}
