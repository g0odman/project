#ifndef SP_Aux_H_
#define SP_Aux_H_
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
double parse(char * line);

/**
 * Free all allocation associated with the stack.
 * @param
 * SP_STACK* stack - Pointer to a stack which will be deleted.
 * 					 After invoking spStackDestroy, stack will no longer be valid to use.
 * 					 If stack==NULL nothing happens.
 */
#endif /* SP_Aux_H_ */
