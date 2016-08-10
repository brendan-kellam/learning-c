//
//  stack.c
//  
//
//  Created by Brendan Kellam on 2016-04-13.
//
//

#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

static int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push f onto value stack */
void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top value from stack */
double pop(void){
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}