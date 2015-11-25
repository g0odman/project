#ifndef SP_Aux_H_
#define SP_Aux_H_
#include "SP_Stack.h"


/**
 * Recieve a line and parse it
 *
 *
 * @param
 * 		string line - An input line, check if it is valid.
 * 				If so then parse it and print result, else
 * 				print error.
 * @return
 *              The result of the equation.
 */
void parse(char * line);

/**
 * Recieve a string token and check its type
 *
 *
 * @param
 * 		char * token - An input token. Checks if it is valid,
 * 				and if so then find its type.
 * @return
 *              The type of the token (as an enum).
 */
SP_STACK_ELEMENT_TYPE getType(char * tok);

/**
 * Check if the input was the exit code.
 *
 *
 * @param
 * 		string tok - An input token. Checks if it is equal to "<>".
 * @return
 *              True if an exit code was recieved, false otherwise
 */
bool isExit(char * tok);

/**
 * Check if the token recieved is a number
 *
 *
 * @param
 * 		string tok - An input token. Check if it is made up of only
 * 				digits, and between 0 and 9.
 * @return
 *              True if the string represents a number, false otherwise.
 */
bool isNumber(char * tok);

/**
 * Find the precedence of the current operation.
 *
 *
 * @param
 * 		SP_STACK_ELEMENT * op - The operation to check.
 * @return
 *              1 for the lowest, 2 for the middle and 3 if it has the highest precedence
 *              		if it is undefined for some reason, 0.
 */
int getRank(SP_STACK_ELEMENT* op);

/**
 * Perform the given mathematical operation on the two input numbers.
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_STACK_ELEMENT_TYPE op - The operation to perform.
 * @param
 * 		double * ans - A pointer into which to store the result.
 * @return
 *              If the operation was valid, then return true, and store result
 *              		in *ans. Otherwise return false.
 */

bool operate(double x,double y, SP_STACK_ELEMENT_TYPE op,double *ans);

/**
 * Performs a single mathematical operation on the two stacks, as described in
 * the assignement guidelines.
 *
 *
 * @param
 * 		SP_STACK * numbers - A stack containing the numbers
 * @param
 * 		SP_STACK * operations - A stack containing the operations.
 * @return
 *              Perform the top operation in operations, on the top two values in numbers
 *                                  If it was a succes return true, else false.
 */

SP_STACK_ELEMENT perform(SP_STACK* numbers, SP_STACK* operations);

#endif /* SP_Aux_H_ */
