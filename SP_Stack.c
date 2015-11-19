#include <stdbool.h>
#include "SP_Stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//max num of elements is 1024
#define MAX_STACK_SIZE 1024

//used by checkStack:
typedef enum {PEAK, PUSH, EMPTY, MAKE} Operation;

//declaring auxillary functions:
bool checkStack(const SP_STACK* stack, SP_STACK_MSG* msg, Operation op);
SP_STACK* makeNode(SP_STACK_ELEMENT* value, SP_STACK* next);


/**
 * This struct represents a stack.
 * 
 * 		int size - represents the amount of elements currently in stack
 * 		SP_STACK_ELEMENT value - the value of this node
 * 		SP_STACK_ELEMENT *next - pointer to next element in linked list
 * 		int pointerCounter - number of pointers to this node, for delete.
 *
 */
struct sp_stack_struct {
    int size;
    SP_STACK_ELEMENT *element;
    SP_STACK *next;
    int pointerCounter;
};

/**
 * Create a new empty stack.
 *
 * Messages:
 * 		SP_STACK_ERROR_ALLOCATION_FAILED - In case allocation failed.
 * 		SP_STACK_SUCCESS - In case creation of the stack succeeded.
 *
 * @param
 * 		SP_STACK_MSG* msg - Pointer which has the memory location where the message
 * 					   		will be stored. if msg==NULL then the function doesn't
 * 							set the value of *msg.
 * @return
 *		A pointer to a new empty stack, if any error occurred NULL is returned.
 */
SP_STACK* spStackCreate(SP_STACK_MSG* msg) {
	
	//allocate pointer:
	SP_STACK *s;
	s = makeNode(NULL, NULL);
	
	//check if allocation worked
	if(!checkStack(s, msg, MAKE)) { return NULL; }
	
	//return the new stack and update message if necsessary:
	if(msg != NULL){
		*msg = SP_STACK_SUCCESS;
	}
	return s;
    
}

/**
 * Free all allocation associated with the stack.
 * @param
 * SP_STACK* stack - Pointer to a stack which will be deleted.
 * 					 After invoking spStackDestroy, stack will no longer be valid to use.
 * 					 If stack==NULL nothing happens.
 */
void spStackDestroy(SP_STACK* stack) {
	
	//check node isn't null:
	if(stack == NULL) { return; }

	stack->pointerCounter--;
	
	//recursivly delete if no more pointers to this
	if(stack->pointerCounter <= 0){
		spStackDestroy(stack->next);
		free(stack->element);
		free(stack);
	}
}

/**
 * Looks at the top of the stack without removing it.
 * Note - The element returned is the SAME element in the stack. Changing the element
 * will cause in changing the top element value as well.
 * Messages:
 *		SP_STACK_ERROR_NULL_ARGUMENT - stack is NULL.
 *		SP_STACK_ERROR_IS_EMPTY - stack is empty
 *		SP_STACK_SUCCESS - in case of success.
 * @param
 * SP_STACK* stack   - The stack which holds the top element.
 * SP_STACK_MSG* msg - Pointer which has the memory location where the message
 * 					   will be stored. if msg==NULL then the function doesn't
 * 					   set the value of *msg.
 * @return
 * The top element of the stack if the stack is not empty, otherwise NULL is returned.
 */
SP_STACK_ELEMENT* spStackTop (SP_STACK* stack, SP_STACK_MSG* msg) {
	
	//printf("%f\n", stack->element->value); //causes seg fault ! (?!)
	
	//check whether stack is null or empty, and update
	//msg accordingly
	if(!checkStack(stack, msg, PEAK)){ return NULL; }
	
	printf("%f\n", stack->element->value); //no seg fault!? why??
	
	return stack->element;
}

/**
 * Removes the top of the stack.
 * Messages:
 *		SP_STACK_ERROR_NULL_ARGUMENT - stack is NULL.
 *		SP_STACK_ERROR_IS_EMPTY - stack is empty
 *		SP_STACK_SUCCESS - in case of success.
 * @param
 * SP_STACK* stack   - The stack which holds the top element.
 * SP_STACK_MSG* msg - Pointer which has the memory location where the message
 * 					   will be stored. if msg==NULL then the function doesn't
 * 						set the value of *msg.
 * @return
 * A stack after the pop operation. If the stack is empty the new stack will be
 * the same as the old one. In case stack is NULL, return NULL
 */
SP_STACK* spStackPop(SP_STACK* stack, SP_STACK_MSG* msg) {
	
	if(!checkStack(stack, msg, PEAK)) { return stack; }
	
	SP_STACK *newTop = stack->next;
	newTop->pointerCounter++; //make it also a top
	
	spStackDestroy(stack); //not sure whether supposed to or not
	
	return newTop;
}

/**
 * Pushes a new element to the top of the stack. The element pushed to the stack
 * is a COPY of the argument newElement.
 * Messages:
 *		SP_STACK_ERROR_NULL_ARGUMENT - stack is NULL.
 *		P_STACK_ERROR_ALLOCATION_FAILED - In case allocation failed.
 *		SP_STACK_SUCCESS - in case of success.
 * @param
 * SP_STACK* stack   - The stack which the new element will be added to.
 * SP_STACK_ELEMENT newElement - The new element to be pushed.
 * 								 A copy of this argument will be allocated and
 * 								 pushed to the top of the stack.
 * SP_STACK_MSG* msg - Pointer which has the memory location where the message
 * 					   will be stored. if msg==NULL then the function doesn't
 * 						set the value of *msg.
 * @return
 * If the parameter 'stack is NULL then NULL is returned.
 * If memory allocation fails then 'stack' is returned.('stack' will not be affected)
 * In case of success, the stack after the push operation.
 *
 */
SP_STACK* spStackPush(SP_STACK* stack, SP_STACK_ELEMENT newElement,SP_STACK_MSG* msg) {
	
	//make sure stack isn't null:
	if(!checkStack(stack, msg, PUSH)) { return stack; }
	
	//copy element:
	SP_STACK_ELEMENT* e = (SP_STACK_ELEMENT*)malloc(sizeof(SP_STACK_ELEMENT));
	e->value = newElement.value;
	e->type = newElement.type;
	
	//make new stack with additional element:
	SP_STACK *toRet =  makeNode(e, stack);
	
	//TODO remove these:
	spStackDestroy(stack);
	printf("%f	%f\n", newElement.value, toRet->element->value);
	
	//make sure malloc didn't fail:
	if(!checkStack(toRet, msg, MAKE)) { return stack; }
	
	return toRet;
}

/**
 * Checks if the stack is Empty.
 * Messages:
 *		SP_STACK_ERROR_NULL_ARGUMENT - stack is NULL.
 *		SP_STACK_SUCCESS - in case of success.
 * @param
 * SP_STACK* stack   - The stack which holds the top element.
 * SP_STACK_MSG* msg - Pointer which has the memory location where the message
 * 					   will be stored. if msg==NULL then the function doesn't
 * 						set the value of *msg.
 * @return
 * true in case stack is empty, otherwise the returned value is false.
 */
bool spStackIsEmpty(SP_STACK* stack, SP_STACK_MSG* msg) {
	
	//check whether stack is null:
	if(!checkStack(stack, msg, EMPTY)) { return false; };
	
	return (stack->size == 0);
}




/* Auxillary functions: */


/**
 * Auxillary function used by other functions.
 * Checks whether stack is null, empty or full,
 * and updates msg accordingly.
 * 
 * returns true if not empty and not null
 * 
 */
bool checkStack(const SP_STACK* stack, SP_STACK_MSG* msg, Operation op) {
	
	//check whether stack is null:
	if(stack == NULL){
		if(msg != NULL){
			if(op == MAKE){ //check whether failed to make or incorrect input
				*msg = SP_STACK_ERROR_ALLOCATION_FAILED;
			} else {
				*msg = SP_STACK_ERROR_NULL_ARGUMENT;
			}
		}
		return false;
	}
	
	//check whether stack is empty when trying to read:
	if(stack->size == 0 && op == PEAK){
		if(msg != NULL){
			*msg = SP_STACK_ERROR_IS_EMPTY;
		}
		return false;
	}
	
	//check whether stack is full and trying to write:
	if(stack->size >= MAX_STACK_SIZE && op == PUSH){
		if(msg != NULL){
			*msg = SP_STACK_ERROR_ALLOCATION_FAILED;
		}
		return false;
	}
	
	//all OK:
	if(msg != NULL){
		*msg = SP_STACK_SUCCESS;
	}
	return true;
}

/**
 * Makes a new node:
 */
SP_STACK* makeNode(SP_STACK_ELEMENT* element, SP_STACK* next) {
	
	//make node:
	SP_STACK *s;
	s = (SP_STACK*)malloc(sizeof(SP_STACK));
	if(s == NULL) {	return NULL; }
	
	//initialize:
	s->element = element;
	s->next = next;
	s->pointerCounter = 1;
	if(next == NULL){
		s->size = 0;
	} else {
		s->size = next->size + 1;
		next->pointerCounter++;
	}
	
	return s;
}
