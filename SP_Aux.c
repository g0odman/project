#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"

/**
 *  Main function, parses given input and calculates result. Prints
 *  all necsesary things.
 */
void parse(char * line){
	
	//tokenize input:
    char * tok = strtok(line," \t\r\n");
    
    //initialize stack and msg used by stack:
    SP_STACK_MSG * msg = malloc(sizeof(SP_STACK_MSG)); //need to free this, if exit suddenly.
    SP_STACK *numbers, *operations;
    SP_STACK_ELEMENT ans;
    
    //boolean used to determine whether to expect number or operation:
    bool getnum = true, isvalid = true;

    
    //make stacks and validate that they were succesfull:
    numbers = spStackCreate(msg);
    if(numbers == NULL || *msg != SP_STACK_SUCCESS) { return; }
    operations = spStackCreate(msg);
    if(operations == NULL || *msg != SP_STACK_SUCCESS) { return; }

    
    while(tok != NULL){

        SP_STACK_ELEMENT_TYPE  type = getType(tok);

        //If we don't recognize it, it's probably wrong.
        if(type == UNKNOWN){
            printf("Invalid Expression!\n");
            return;
        }

        //make element to push into stack:
        SP_STACK_ELEMENT current;
        current.type = type;

        //Check that the order recieved was correct, and push into correct stack:
        if(type == NUMBER && getnum){
            current.value = atoi(tok);
            numbers = spStackPush(numbers, current, msg);
        }
        else if(!getnum && type != NUMBER){
            while (!(spStackIsEmpty(operations,msg) || 
            		getRank(spStackTop(operations,msg)) < getRank(&current))){
                ans = perform(numbers,operations);
                if(ans.type ==UNKNOWN){
                    printf("Invalid Result!\n");
                    return;
                }
                operations = spStackPop(operations,msg);
                numbers = spStackPop(numbers,msg);
                numbers = spStackPop(numbers,msg);
                numbers = spStackPush(numbers,ans,msg);
            }
            operations = spStackPush(operations,current,msg);
        }
        else{
            printf("Invalid Expression!\n");
            return;
        }
        getnum = !getnum; //For next time, expect opposit of what recieved

        tok = strtok(NULL," \t\r\n"); //Get the next token.
    }
    //IF we finished expecting a number, then there is a problem.
    if(getnum){
        printf("Invalid Expression!\n");
        return;
    }
    
    while (!(spStackIsEmpty(operations,msg))){
        SP_STACK_ELEMENT ans = perform(numbers,operations);
        if(ans.type ==UNKNOWN){
            printf("Invalid Result!\n");
            isvalid = false;
            break;
        }
        operations = spStackPop(operations,msg);
        numbers = spStackPop(numbers,msg);
        numbers = spStackPop(numbers,msg);
        numbers = spStackPush(numbers,ans,msg);
    }
    if(isvalid)
        printf("res = %f\n", spStackTop(numbers,msg)->value); //doing (*x).val is like x->val

    //Free stacks
    free(msg);
    spStackDestroy(operations);
    spStackDestroy(numbers);
}

SP_STACK_ELEMENT perform(SP_STACK* numbers, SP_STACK* operations){
        SP_STACK_MSG * msg= malloc(sizeof(SP_STACK_MSG)); //change this to malloc(sizeof(..)), no?
        double *ans = malloc(sizeof(double));
        double y = spStackTop(numbers,msg)->value;
        numbers = spStackPop(numbers,msg);
        double x = spStackTop(numbers,msg)->value;
        SP_STACK_ELEMENT_TYPE op = spStackTop(operations,msg)->type;
        SP_STACK_ELEMENT new;
        if(!operate(x,y,op,ans))
            new.type = UNKNOWN;
        else {
        	new.value = *ans;
        	new.type = NUMBER;
        	numbers = spStackPush(numbers, new, msg);
        }
        free(msg);
        free(ans);
        return new;
}

bool operate(double x,double y, SP_STACK_ELEMENT_TYPE op,double *ans){
    switch (op){
        case PLUS:
            *ans = x+y;
            break;
        case MINUS:
            *ans =  x - y;
            break;
        case MULTIPLICATION:
            *ans =  x * y;
            break;
        case DIVISION:
            if(y == 0)
                return false;
            *ans =  x/y;
            break;
        case DOLLAR:
            if( x > y){
                return false;
            }
            double sum = 0;
            for(double i = x; i <= y; i++)
                sum += i;
            *ans =  sum;
            break;
        default:
            return false;
    }
    return true;
}

SP_STACK_ELEMENT_TYPE getType(char * tok){
    
	//Check if it is a number
    if(isNumber(tok))
        return NUMBER;
    
    //If not make sure that it is the correct length
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

int getRank(SP_STACK_ELEMENT* op){
    switch (op->type){
        //lowest order
        case PLUS:
        case MINUS:
            return 1;

        //next highest
        case MULTIPLICATION:
        case DIVISION:
            return 2;
            
        //highest
        case DOLLAR:
            return 3;
            
        default:
            return 0;
    }
}

bool isNumber(char * tok){
    //iterate over all of tok and check that the ascii values are digits
    int i =0;
    while(tok[i] != '\0'){
        if(tok[i] < '0' || tok[i] > '9')
            return false;
        i++;
    }
    return true;
}

bool isExit(char * tok){
    return (strncmp(tok,"<>",2) == 0 && strlen(tok) == 3);
}
