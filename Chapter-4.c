//Notes:
// If return type is omitted, int is assumed
// When using a function in another, it is important to DIRECTLY define its type. (Section 4.2)
// Internal: Declarations inside functions, External: Declarations outside functions, world scope
// Notes on macros and #define:
//  A definition is really just a "substitution of text", so cool things can be created
//  Macros with arguments can be used to create type-independent routines
// #undef: Undefines a definition
// A # in the actual replacement text will treat the expresion as a string (look at a example)
// The ## preprocessor operator provides a way to concatenate arguments
// Conditional inclusion

//Imports
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//Init
#define MAXLINE 1000 /* maximum input line length */
#define FALSE 0
#define TRUE 1

#define max(A, B) ((A) > (B) ? (A) : (B))
#define dprint(expr) printf(#expr " = %g\n", expr)
#define print(expr) printf("%d\n", expr)
#define paste(front, back) front ## back

#define swapval(t, x, y) {t tmp; tmp = x; x = y; y = tmp;}

//Definitions
int len(char input[]);
int returnline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);
double atof(char converstion[]);
int atoi(char converstion[]);
void printd(int n);
void qsort(int v[], int left, int right);
void swap(int v[], int i, int j);
void swapstr(char s[], int i, int j);
void itoa(int input, int index, char output[]);
void reverse(char input[], int left, int right);

//Util functions

/* return length of string s */
int len(char s[]){
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
    
}

/* reverse string s recursevly */
void reverse(char s[], int i, int j){
    
    void swapstr(char s[], int i, int j);
    int a = j - i;
   
    if (len(s) % 2 == 0){
        if (i == len(s) - 5) return;
    }else{
        if (i == len(s) - 4) return;
    }
    
    
    swapstr(s, i, j);
    reverse(s, ++i, --j);

}

/* return index of right-most occurence of t in s, -1 if none */
int strrindex(char s[], char t[]){
    int i, j, k;
    int pos = -1;
    
    for (i = 0; s[i] != '\0'; i++){
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            pos = i;
    }
    
    return pos;
}

/* converts integer n to string s recursevly */
void itoa(int n, int i, char s[]){
    if (n < 0){
        s[0] = '-';
        i++;
        n = -n;
    }
    
    s[i] = n % 10 + '0';
    
    if (n/10)
        itoa(n/10, ++i, s);
    else
        s[++i] = '\0';
    
}


//Main functions


/* -- 4.10: recursive functions --  */

void qsort(int v[], int left, int right){
    
    int i, last;
    void swap(int v[], int i, int j); /* declare use of swap function */
    
    if (left >= right) /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right)/2); /* move partition elem */
    last = left; /* to v[0] */
    
    for (i = left+1; i <= right; i++) /* partition */
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
    
}

/* interchange v[i] and v[j] */
void swap(int v[], int i, int j){
    int temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void swapstr(char s[], int i, int j){
    char temp;
    
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}



/* print n in decimal */
void printd(int n){
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    
    if (n/10)
        printd(n/10);
    putchar(n % 10 + '0');
}




/* -- 4.2: converstion string -> double -- */

/* rudimentary calculator */
void tut2(){
    double sum, atof(char[]); //Diretly define atof as a double to keep consistency
    char line[MAXLINE];
    int returnline(char line[], int max); //Again, directly define returnline as a int type
    
    sum = 0;
    while (returnline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += atof(line));
    
}

/* convert string s to double */
double atof(char s[]){
    double val, power, exp;
    int i, sign, expsign;
    
    for (i = 0; isspace(s[i]); i++); /* Skip whitespace */
    
    sign = (s[i] == '-') ? -1 : 1; /* Get sign */
    if (s[i] == '+' || s[i] == '-') /* Skip sign character */
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++) /* Handle all left of decimal */
        val = 10.0 * val + (s[i] - '0');
    
    if (s[i] == '.') /* Skip decimal */
        i++;
    
    for (power = 1.0; isdigit(s[i]); i++) { /* Handle all right of decimal */
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    
    expsign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (exp = 0.0; isdigit(s[i]); i++)
        exp = 10.0 * exp + (s[i] - '0');
    
    
    return sign * val / power * pow(10, expsign*exp);
}

/* convert string s to integer using atof */
int atoi(char s[]){
    double atof(char s[]); //Declare atof as a double type. It accepts one parameter
    
    return (int) atof(s); //Case atof to int
}

/* -- 4.1: pattern finder -- */

/* Find all lines matching pattern */
void tut1(){
    
    char line[MAXLINE];
    int found = 0;
    char pattern[] = "ould";
    
    while (returnline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0){
            printf("%s\n", line);
            found++;
        }
    
    printf("Found: %d\n", found);
    
}

/* return line into s, return length */
int returnline(char s[], int lim){
    
    int c, i;
    
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
    
}

/* return index of t in s, -1 if none */
int strindex(char s[], char t[]){
    
    int i, j, k;
    
    for(i = 0; s[i] != '\0'; i++){
        for (j=i, k=0; t[k]!= '\0' && s[j]==t[k]; j++, k++);
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}



/* -- end -- */


int main(){
    printf("Running...\n");
    
    char s[] = "Brendan";
    reverse(s, 0, len(s)-1);
    printf("result:%s\n\n\n", s);
    
    int a = 4;
    paste(1, 1);
    
    return 0;
}