/**
 @file
 @author Brendan Kellam <brendan.kellam@mail.mcgill.ca>
 @version 1.0
 
**/

/* --- notes --- 
*/


/* --- guard --- */
#ifndef expr_h
#define expr_h



/* --- include statements --- */
#include "../util.h"


/* --- finals --- */
#define STACK_SIZE 1024


double stack[STACK_SIZE];
int stack_height = 0;


/* --- function prototypes --- */

double pop(void);

#endif /*--- dateConverter_h --- */

