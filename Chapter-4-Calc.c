// Notes:
//  It is important to distinguish between a barible declaration and its definition
//  Declaration: Announces the properties of a varible (I.E its type)
//  Definition: Alloticates storage

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100

#define GRAVITY 9.81


int getop(char[]); /* returns the operand/operator */
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar(); //if buffer position is greater than 0, return the next value in the buffer, else, get a char
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    
}

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

/* push f onto value stack */
void push(double f){
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop and return top balue from stack */
double pop(void){
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
    return 0.0;
    }
}

/* reverse Polish calculator */
int main(){
    
    double a = 8.0;
    printf("HERE: %d\n", (int) a);
    
    
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
