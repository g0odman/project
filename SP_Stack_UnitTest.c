#include "SP_Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FAIL(msg) do {\
		fprintf(stderr,"%s Line %d: %s", __FILE__, __LINE__, msg);\
		return false;\
	} while(0)

#define ASSERT_TRUE(expression) do { \
                if(!((expression))) { \
                        FAIL("expression is false :: "); \
                } \
        } while (0)

#define ASSERT_FALSE(expression) do { \
                if((expression)) { \
                        FAIL("expression is true  ::"); \
                } \
		} while (0)

#define RUN_TEST(f) do { \
			if(f()==true){ \
				fprintf(stderr, "%s  PASSS\n",#f);\
			}else{ fprintf(stderr, "%s  FAIL\n",#f);\
			} }while (0)

bool TEST1(){
	SP_STACK_MSG msg;
	SP_STACK_ELEMENT* elementPtr = NULL;
	SP_STACK * stack = spStackCreate(&msg);
	ASSERT_TRUE(msg == SP_STACK_SUCCESS && stack!=NULL);
	elementPtr = spStackTop(stack,&msg);
	ASSERT_TRUE(msg == SP_STACK_ERROR_IS_EMPTY && elementPtr == NULL);
	SP_STACK_ELEMENT newElement = {.type = NUMBER , .value = 100};
	stack = spStackPush(stack,newElement,&msg);
	ASSERT_TRUE(msg == SP_STACK_SUCCESS);
	elementPtr = spStackTop(stack,&msg);
	ASSERT_TRUE(elementPtr->type == newElement.type && elementPtr->value == newElement.value && msg==SP_STACK_SUCCESS);
	spStackDestroy(stack);
	return 1;
}

bool TEST2(){
	
	/**
	 * basic test, inserting and removing 100 elements
	 */
	
	SP_STACK_MSG msg;
	SP_STACK_ELEMENT* top = NULL;

	
	//make empty stack
	SP_STACK* stack = spStackCreate(&msg);
	ASSERT_TRUE(spStackIsEmpty(stack, &msg));
	
	//insert numbers 0 to 99:
	for(int i=0; i<100; i++){
		SP_STACK_ELEMENT new = {.type = NUMBER, .value = i};
		stack = spStackPush(stack,new,&msg);
		ASSERT_TRUE(msg == SP_STACK_SUCCESS);
		top = spStackTop(stack, &msg);
		ASSERT_TRUE(top->type == new.type && top->value == new.value && msg==SP_STACK_SUCCESS);
	}
	
	ASSERT_TRUE(spStackIsEmpty(stack, &msg) == false);
	
	//remove items:
	for(int i = 99; i>=0; i--){
		top = spStackTop(stack, &msg);
		ASSERT_TRUE(top->type == NUMBER && top->value == i && msg==SP_STACK_SUCCESS);
		stack = spStackPop(stack, &msg);
		ASSERT_TRUE(msg == SP_STACK_SUCCESS);
	}
	
	ASSERT_TRUE(spStackIsEmpty(stack, &msg) == true);
	
	spStackDestroy(stack);
	
	return 1;
}

bool TEST3(){
	/**
	 * corner case testing
	 */
	
	SP_STACK_MSG msg;
	SP_STACK_ELEMENT* top = NULL;
	SP_STACK_ELEMENT e = {.type = NUMBER, .value = 3};

	
	//make empty stack
	SP_STACK* stack = spStackCreate(&msg);
	ASSERT_TRUE(spStackIsEmpty(stack, &msg));
	
	//make sure destroying NULL doesn't cause problem:
	spStackDestroy(NULL);
	
	//try getting top when stack is empty or NULL:
	top = spStackTop(stack, &msg);
	ASSERT_TRUE(top == NULL && msg == SP_STACK_ERROR_IS_EMPTY);
	top = spStackTop(NULL, &msg);
	ASSERT_TRUE(top == NULL && msg == SP_STACK_ERROR_NULL_ARGUMENT);
	
	//try removing top element when stack is empty or NULL:
	stack = spStackPop(stack, &msg);
	ASSERT_TRUE(msg == SP_STACK_ERROR_IS_EMPTY);
	spStackPop(NULL, &msg);
	ASSERT_TRUE(msg == SP_STACK_ERROR_NULL_ARGUMENT);
	
	//try inserting to NULL:
	spStackPush(NULL, e, &msg);
	ASSERT_TRUE(msg == SP_STACK_ERROR_NULL_ARGUMENT);
	
	//try checking size of NULL:
	spStackIsEmpty(NULL, &msg);
	ASSERT_TRUE(msg == SP_STACK_ERROR_NULL_ARGUMENT);
	
	
	spStackDestroy(stack);
	
	return 1;
}

int main(){
	RUN_TEST(TEST1);
	RUN_TEST(TEST2);
	RUN_TEST(TEST3);
	return 0;
}
