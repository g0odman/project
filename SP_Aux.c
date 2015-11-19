#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "SP_Aux.h"

/**
 *  Main function, parses given input and calculates result.
 */
void parse(char * line){
	
	//tokenize input:
    char * tok = strtok(line,"\t\r\n");
    
    //initialize stack and msg used by stack:
    SP_STACK_MSG * msg= malloc(2); //change this to malloc(sizeof(..)), no?
    SP_STACK *numbers, *operations;
    
    //boolean used to determine whether to expect number or operation:
    bool getnum = true;

    
    //make stacks and validate that they were succesfull:
    numbers = spStackCreate(msg);
    if(*msg == SP_STACK_ERROR_ALLOCATION_FAILED) { return; }
    
    operations = spStackCreate(msg);
    if(*msg == SP_STACK_ERROR_ALLOCATION_FAILED) { return; }

    
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
                if(!perform(numbers,operations) { return; }
            }
            operations = spStackPush(operations,current,msg);
        }
        else{
            printf("Invalid Expression!\n");
            return;
        }
        getnum = !getnum; //For next time, expect opposit of what recieved
        printf("Stack Sizes:\n\tNumbers:\t%d\n\tOperations:\t%d\n",numbers->size,operations->pointerCounter);

        tok = strtok(NULL,"\t\r\n"); //Get the next token.
    }
    //IF we finished expecting a number, then there is a problem.
    if(getnum){
        printf("Invalid Expression!\n");
        return;
    }
    
    while (!(spStackIsEmpty(operations,msg))){
        if(!(perform(numbers,operations))){
            printf("Invalid Expression!\n");
            return;
        }
    
    }
    
    printf("Res = %f",(*spStackTop(numbers,msg)).value); //doing (*x).val is like x->val

    //Free stacks
    free(msg);
    spStackDestroy(operations);
    spStackDestroy(numbers);
}

bool perform(SP_STACK* numbers, SP_STACK* operations){
        bool * valid = true;
        SP_STACK_MSG * msg= malloc(2);
        int x = (*spStackTop(numbers,msg)).value;
        numbers = spStackPop(numbers,msg);
        int y = (* spStackTop(numbers,msg)).value;
        numbers = spStackPop(numbers,msg);
        SP_STACK_ELEMENT* op = spStackTop(numbers,msg);
        operations = spStackPop(numbers,msg);
        SP_STACK_ELEMENT new;
        new.value = operate(x,y,(* op).type,valid);
        printf("The new value is %f\n",new.value);
        if(!(*valid)){
            printf("Invalid Result!\n");
            return false;
        }
        new.type = NUMBER;
        numbers = spStackPush(numbers,new,msg);
        free(msg);
        return true;
}

double operate(double x,double y, SP_STACK_ELEMENT_TYPE op,bool* valid){
    switch (op){
        case PLUS:
            return x +y;
        case MINUS:
            return x-y;
        case MULTIPLICATION:
            return x*y;
        case DIVISION:
            if(y ==0){
                valid = false;
                return 0;
            }
            return x/y;
        case DOLLAR:
            if( x >y){
                (* valid) = false;
                return 0;
            }
            double sum = 0;
            for(double i =x; i <=y;i++)
                sum +=i;
            return sum;
        default:
            (*valid) = false;
            return 0;
    }
}

SP_STACK_ELEMENT_TYPE getType(char * tok){
    //Check if it is a number
    if(isNumber(tok))
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

int getRank(SP_STACK_ELEMENT* op){
    switch ((*op).type){
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
    //iterate over all of tok and check the ascii values
    int i =0;
    while(tok[i] != '\0'){
        if(tok[i] < '0' || tok[i] > '9')
            return false;
        i++;
    }
    return true;
}

bool isExit(char * tok){
    char * temp = (char *) malloc(3); //need to free as well!!!

    //Check if the first two chars are correct.
    strncpy(temp,tok,2);

    //And make sure that it is the correct length
    if(strcmp(temp,"<>")==0 && strlen(tok) == 3) {
    	free(temp);
        return true;
    }
    
    free(temp);
    return false;
}
