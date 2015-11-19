#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"


void parse(char * line){
    char * tok = strtok(line,"\t\r\n");
    SP_STACK_MSG * msg= malloc(2);
    struct sp_stack_struct* numbers, *operations;

    numbers = spStackCreate(msg);

    //Valdate that the stack was created correctly
    if(*msg == SP_STACK_ERROR_ALLOCATION_FAILED)
        return;

    operations = spStackCreate(msg);

    //Valdate that the stack was created correctly
    if(*msg == SP_STACK_ERROR_ALLOCATION_FAILED)
        return;

    while(tok != NULL){

        SP_STACK_ELEMENT_TYPE  type = get_type(tok);

        //If we don't recognize it, it's probably wrong.
        if(type == UNKNOWN){
            printf("Invalid Expression!\n");
            return;
        }

        //Push into stacks
        SP_STACK_ELEMENT current;
        current.type = type;
        if(type == NUMBER){
            current.value = atoi(tok);
            spStackPush(numbers, current,msg);
        }
        else
            spStackPush(operations,current,msg);
        printf("%f\n",current.value);
        tok = strtok(NULL,"\t\r\n");
    }

    //Free stacks
    spStackDestroy(operations);
    spStackDestroy(numbers);
}

SP_STACK_ELEMENT_TYPE get_type(char * tok){
    //Check if it is a number
    if(is_number(tok))
        return NUMBER;
    //If not make sure that it is teh correct length
    else if(strlen(tok) !=1)
        return UNKNOWN;
    //return the correct value
    switch(tok[0]) {
        case '+'  :
             return PLUS;
        case '-'  :
             return MINUS;
        case '$'  :
             return DOLLAR;
        case '*'  :
             return MULTIPLICATION;
        case '/'  :
             return DIVISION;
        default : /* Optional */
             return UNKNOWN;
    }
}

bool is_number(char * tok){
    //iterate over all of tok and check the ascii values
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

    //Check if the first two chars are correct.
    strncpy(temp,tok,2);

    //And make sure that it is the correct length
    if(strcmp(temp,"<>")==0 && strlen(tok) == 3)
        return true;
    return false;
}
