#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX_LINE_LENGTH 200
int main(){
    char * line = malloc(MAX_LINE_LENGTH +1);
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
        char * tok = strtok(line,"\t\r\n");
        while(tok != NULL){
            puts(tok);
            tok = strtok(NULL,"\t\r\n");
        }
    }
    free(line);
    return 0;
}
