//
//  getop.c
//  
//
//  Created by Brendan Kellam on 2016-04-13.
//
//

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include "calc.h"

int getop(char s[]){
    
    int i, c, sign = 1;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t'); /* filter thru all leading spaces and tabs */
    
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;                /* not a number */
    i = 0;
    
    if (isdigit(c))              /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.')
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
    
}

