#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h> //Allows for character tests
#include <math.h>

//NOTE MACRO REDEFINITION
#define EOF 96

//define boolean representations
#define FALSE 0
#define TRUE 1

//define the maxline input
#define MAXLINE 1000

int binsearch(int x, int v[], int n);
void escape(char t[], char s[]);
int len(char s[]);
void rawinput(char input[]);
void append(char s[], char add[], int n);
void expand(char s1[], char s2[]);
void itoa(int n, char s[], int min);
void reverse(char s[]);




// --- UTIL FUNCTIONS ---//
int len(char s[]){
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
    
}

void reverse(char s[]){
    int c, i, j;
    
    for (i = 0, j = len(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
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


// assumes perfect length
void append(char s[], char add[], int n){
    int i;
    for (i = 0; i < len(add); i++){
        s[(n + i)] = add[i];
    }
}


// --- MAIN ---//

void itoa(int n, char s[], int min){
    int i, sign;
    
    if ((sign = n) < 0)
        n = -n; //make n positive
    i = 0;
    do {
        s[i++] = n % 10 + '0'; //get next digit
    }while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';

    printf("%d\n", i);
    printf("%d\n", min);
    
    if (i < min) {
        
        for (4; i < (min - i) + i; i++){
            s[i] = ' ';
        }
    
    }
    
    printf("%s\n", s);
    
    s[i] = '\0';
    reverse(s);
}


//sample input: a-z ouput: abc..xyz
//sample input: a-z0-9 output: abc..xyz012..789
void expand(char s1[], char s2[]){
    int i = 0, count = 0;
    char c;
    int alpha = FALSE;
    int inoper = FALSE;
    
    char a, b;
    
    //main char loop (c = current char of s1)
    while ((c = s1[i++]) != '\0'){
        printf("%c\n", c);
        
        if (c == '-'){
            if (a != 0) inoper = TRUE;
            continue;
        }
        
        if(inoper == TRUE){
            b = c;
            if (isdigit(c) || isalpha(c)){
                for (int i = a; i <= b; i++, count++){
                    s2[count] = i;
                }
            }
            inoper = FALSE;
        }
        else a = c;
        
        
        
    }
}


//copies t -> s
void escape(char t[], char s[]){
    int c = 0, i = 0, end = 0;
    char temp[1];
    
    while ((c = t[i++]) != '\0'){
        switch (c){
            end = len(s);
            temp[0] = c;
            case '\n':
                append(s, "\n", end);
                break;
                
            case '\t':
                append(s, "\t", end);
                break;
                
            default:
                append(s, temp, end);
                break;
                
        }
    }
    
    
}

void tut2(){
    char t[MAXLINE];
    char s[MAXLINE];
    
    rawinput(t);
    rawinput(s);
    escape(t , s);
    printf("%s\n", s);
    
    printf("%d\n", len(t));
}

int binsearch(int x, int v[], int n){
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    
    while (low <= high){
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    
    return -1; //no match
}


void tut1(){
    int a[] = {0, 3, 9, 22, 68, 102, 106, 120, 140, 190};
    int res = binsearch(102, a, 10);
    printf("%d\n", res);
    printf("%d\n", a[res]);
}


int main(){
    printf("running..\n");
    
    char s[MAXLINE];
    int n = -1789;
    int min = 10;
    
    itoa(n, s, min);
    printf("%s\n", s);
    
    return 0;
}