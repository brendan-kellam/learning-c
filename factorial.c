//
//  factorial.c
//  
//
//  Created by Brendan Kellam on 2016-04-14.
//
//

//imports
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXVAL 10000

//definitions
#define TRUE 1
#define FALSE 0


int getlen(char input[]); /* returns the length of a string (ommits '\0' character) */
int factorial(int number); /* returns factorial of number */
void factorialstr(char input[], char result[]); /* returns a factorail of a string */
int isnum(char input[]); /* returns TRUE or FALSE */

int isnum(char input[]){
    int i, c;
    while ((c = input[i++]) != '\0')
        if(!isdigit(c)) return FALSE;
    return TRUE;
}

int getlen(char input[]){
    int c = 0, i = 0;
    while((c = input[i]) != '\0') i++;
    return i;
}

void rawinput(char input[]){
    int i = 0, c = 0;
    
    while ((c = getchar()) != EOF){
        
        if(c == '\n'){
            input[i++] = '\0';
            return;
        }
        
        input[i] = c;
        i++;
    }
    
}

void factorialstr(char str[], char res[]){
    int i, j, c, t;
    for (j = 0, i = 0, t = 0; j < getlen(str); j++, i = 0)
        while ((c = str[j + i++]) != '\0')
            res[t++] = c;
}

int factorial(int num){
    if (num <= 1)
        return 1;
    return num * factorial(num-1);
}

int main(){
    printf("running...\n");
    
    char str[MAXVAL];
    rawinput(str);
    
    
    if (isnum(str))
        printf("result:%d\n", factorial(atoi(str)));
    else {
        char res[MAXVAL];
        factorialstr(str, res);
        printf("result:%s\n", res);
    }
        
    return 0;
}









