//
//  getch.c
//  
//
//  Created by Brendan Kellam on 2016-04-13.
//
//

#include <stdio.h>
#include "calc.h"
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */


int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar(); //if buffer position is greater than 0, return the next value in the buffer, else, get a char
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    
}
