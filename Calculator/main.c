//
//  main.c
//  Created by Brendan Kellam on 2016-04-13.
//
//  Static declaration:
//   The external static declaration (applied to functions and external varibles) allows for the varible to be non-visible to other source files
//   A static declaration within a function allows that varible to act like a automatic varible, but it will stay in memory.
//  Register declaration:
//   Allows for a varible to be held within a register for quicker acsess.
//  Note about initialization:
//   Without explicit initialization, external and static = 0, automatic and register = garbage

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXOP 100

int main(){
    printf("Version 1.0 running...\n\n");
    
    int type;
    int res;
    double op2;
    char s[MAXOP];
    
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s)); /* push the operand to the stack */
                break;
            case '+':
                push(pop() + pop()); /* pop the two operands from the stack and add */
                break;
            case '*':
                push(pop() * pop()); /* multiply */
                break;
            case '-':
                op2 = pop();
                push(pop() - op2); /* subtract */
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) /* check for over 0 error */
                    push(pop() / op2); /* divide */
                else
                    printf("error: zero divisor..\n");
                break;
            case '%':
                op2 = pop();
                //printf("%f\n", pop());
                //printf("%f\n", pop());
                
                push( (int) pop() % (int) op2);
                break;
                
            case '\n':
                printf("\t%.8g\n", pop());
                break;
                
            default:
                printf("error: unkown command %s\n", s);
                break;
        }
        
        
    }

    
    
    return 0;
}