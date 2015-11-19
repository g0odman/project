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
SP_STACK_ELEMENT_TYPE get_type(char * tok);
/**
 * Check if the token recieved is a number
 *
 *
 * @param
 * 		string tok - An input token, check if it is all acii between 0 and 9
 * @return
 *              The result of the equation.
 */
bool is_exit(char * tok);
/**
 * Check if the input was an exit code.
 *
 *
 * @param
 * 		string tok - An input token, check if it is equal to <>.
 * @return
 *              True if an exit code was recieved, false otherwise
 */
bool is_number(char * tok);

#endif /* SP_Aux_H_ */
