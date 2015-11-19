#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"

/**
 *  Main parsing function.
 *  
 *  Input is a line read from user
 */
double parse(char * line){
	
    char * tok = strtok(line,"\t\r\n");
    
    //TODO finish:
    while(tok != NULL){
        if(get_type(tok) == NUMBER)
            printf("YAY\n");
        else
            printf("NAY\n");
        tok = strtok(NULL,"\t\r\n");
    }
    return 0;
}

/**
 *  Returns type of given token read from user
 *  
 */
SP_STACK_ELEMENT_TYPE get_type(char * tok){
	
	//why not already convert it to an SP_STACK_ELEMENT, and return that?
    if(is_number(tok))
        return NUMBER;
    return PLUS;
}


//isn't there a buit in function that does this?
bool is_number(char * tok){
    int i =0;
    while(tok[i] != '\0'){
        if(tok[i] < '0' || tok[i] > '9')
            return false;
        i++;
    }
    return true;
}

/**
 *  Returns true if the given input is the exit command, false otherwise
 *  
 */
bool is_exit(char * tok){
    char * temp = (char *) malloc(3);
    strncpy(temp,tok,2);
    
    if(strcmp(tok,"<>") == 0 && strlen(tok) == 3){
    	free(temp); //you need to free it!
        return true;
    }
    
    free(temp); //you need to free it!
    return false;
}
