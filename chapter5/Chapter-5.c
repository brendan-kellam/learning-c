/* --- NOTES --- */
// &n - returns the memory address of varible n (treated like a pointer)
// *p - returns the value of the varible p points to (treated like a varible)
// *(pa+i) = a[i]
// pointers can NEVER be 0, and therefore treat it special
// For a pointer: 0 = NULL (NULL located in <stdio.h>)
// Refering to a array's given name refrences position 0 of the array
// char *p = c   equivilent to   char *p = &c[0]
// pointer arithmetic: can only be operated if two given pointers point to members of the same array
// pointers can be used to point at arrays, in essences they are pointing to other pointers
// functions are held in contiguous blocks in memory (I.E machine instructions for a function are adjacent in memory) 


/* --- include statements --- */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* --- definitions / function prototypes--- */
#define BUFSIZE 100 // maxiumum input buffer size
#define ALLOCSIZE 1000 //size of available space
#define FALSE 0
#define TRUE 1

int getch(void);
int strlength(char *input);
void ungetch(int value);
void afree(char *position);
char *alloc(int size);
void stringcat(char *s, const char *t);
int strend(char *s, char *t);


/* --- global varible definitions --- */
char buf[BUFSIZE];
int bufp = 0;

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position in alloc */


/* --- util functions --- */


int strend(char *s, char *t){ /* check if t exists at the end of s */
    s += strlength(s);
    t += strlength(t);

    while (*--s == *--t)
        printf("here!\n");
    
    if(*t == '\0') return 0;
    return 1;
}


void stringcat(char *s, const char *t){
    
    while (*s) /* loop too the end of s */
        ++s;
    
    while (*t)
        *s++ = *t++;
    
    *s = '\0';
    
}


char *alloc(int n){ /* returns pointer to n characters */
    if (allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n; /* return the old alloc position */
    } else
        return  NULL;
}

void afree(char *p){ /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE) /* check if the position pointer is in bounds */
        allocp = p;
    
}


/* compute the length of a given char array */
int strlength(char *s){
    int i = 0;
    
    for (i = 0; *s != '\0'; s++, i++);
    return i;
}


/* get from input stream (if bufp = 0) else pull from input stream */
int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/* push to input buffer */
void ungetch(int c){
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters!\n");
    else
        buf[bufp++] = c;
}


/* get next integer from input into *pn */
int getint(int *pn){
    int c, sign;
    
    while ((isspace(c = getch())))
           ; /* skip white space */
     
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){ /* check if c is valid */
        ungetch(c);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
            if(!isdigit(c = getch()))
                ungetch(c);
    
    
           
    for (*pn = 0; isdigit(c); c = getch())
           *pn = 10 * *pn + (c - '0'); /* convert to integer */
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
    
}



int main(){
    
    printf("running...\n");
    
    char s[] = "helloabcd";
    char t[] = "abcd";
    printf("here: %d\n", strend(s, t));

    
    return 0;
    
}
