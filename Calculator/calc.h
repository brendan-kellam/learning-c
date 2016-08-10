//
//  calc.h
//  Created by Brendan Kellam on 2016-04-13.

#define NUMBER '0'
void push(double);
double pop(void);
int getop(char[]); /* returns the operand/operator */
int getch(void);
void ungetch(int);