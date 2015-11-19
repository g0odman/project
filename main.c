#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "SP_Aux.h"

#define MAX_LINE_LENGTH 200

int main(){
	
	//allocate buffer to read to:
    char *line = (char*)malloc(MAX_LINE_LENGTH +1);
    
    //main loop:
    while (fgets(line,MAX_LINE_LENGTH,stdin)!=NULL){
    	
    	//check whether need to exit:
        if(isExit(line)) { break; }
        
        //run parser: (see SP_Aux)
        parse(line);
    }
    
    printf("Exiting...\n");
    free(line);
    return 0;
}
