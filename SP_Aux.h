#ifndef SP_Aux_H_
#define SP_Aux_H_
#include "SP_Stack.h"
/**
 * Recieve a line and parse it
 *
 *
 * @param
 * 		string line - An input line, check if it is valid.
 * 		                        If so then parse it, else baad.
 * @return
 *              The result of the equation.
 */
void parse(char * line);
/**
 * Recieve a token and check for its type
 *
 *
 * @param
 * 		char * token - An input token, check if it is valid.
 * 		                        If so then find its type.
 * @return
 *              The type of the enum.
 */
SP_STACK_ELEMENT_TYPE getType(char * tok);
/**
 * Check if the token recieved is a number
 *
 *
 * @param
 * 		string tok - An input token, check if it is all acii between 0 and 9
 * @return
 *              The result of the equation.
 */
bool isExit(char * tok);
/**
 * Check if the input was an exit code.
 *
 *
 * @param
 * 		string tok - An input token, check if it is equal to <>.
 * @return
 *              True if an exit code was recieved, false otherwise
 */
bool isNumber(char * tok);
/**
 * Find the precedence of the current operation.
 *
 *
 * @param
 * 		SP_STACK_ELEMENT * op - The operation to check
 * @return
 *              1 for the lowest, 2 for the middle and 3 if it has the highest precedence
 *                                  if it is undefined for some reason, 0.
 */
int getRank(SP_STACK_ELEMENT* op);
/**
 * Perform a mathematicla operation on two doubles
 *
 *
 * @param
 * 		double x - The first number
 * @param
 * 		double y - the second number;
 * @param
 * 		SP_STACK_ELEMENT_TYPE op - The operation to perform.
 * @param
 * 		bool * valid - A pointer which will indicate whether the operation was valid.
 * @return
 *              If the operation was valid, then the result, if not 0 and set valid accordingly.
 *                                  if it is undefined for some reason, 0.
 */

bool operate(double x,double y, SP_STACK_ELEMENT_TYPE op,double *new);

/**
 * Performs a single mathematicla operation using the values from the two stacks
 *
 *
 * @param
 * 		SP_STACK * numbers - A stack containing only numbers
 * @param
 * 		SP_STACK * operations - A stack containing only operations.
 * @return
 *              Perform the top operation in operations on the top two values in numbers
 *                                  If it was a succes return true, else false.
 */

SP_STACK_ELEMENT perform(SP_STACK* numbers, SP_STACK* operations);
#endif /* SP_Aux_H_ */
