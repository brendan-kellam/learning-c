/* --- imports  --- */
#include <stdio.h>
#include <string.h>
#include "util.c"

/* --- definitions --- */
#define MAXLINES 5000
#define MAXLEN 1000 /* max length of any input line */

/* --- varibles  --- */
char *lineptr[MAXLINES]; /* pointers to text lines */


/*  --- function prototypes --- */
int readlines(char *lineptr[], int nlines); /* read input lines, return number of lines. */
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);
char *alloc(int);


/* sorting operations: */
    /* read all lines of input */
    /* sort them */
    /* print them in order */


/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines){
    
    int len, nlines = 0;
    char *p, line[MAXLEN];
    
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || ())
           
           
    return -1;
}


int main() {
    printf("running..\n");
    
    readlines(char *lineptr[], int maxlines);
    
    int nlines; /* number of lines to read from input */
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }else{ /* number of lines invalid */
        printf("error: input invalid!\n");
        return 1;
    }
    
    
}