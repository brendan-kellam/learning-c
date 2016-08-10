#include "util.h"

int bufp = 0;

void print(const char *input){
    printf("%s\n", input);
}

void panic(const char *error){
    fprintf(stderr, RED "%s\n" RESET, error);
    exit(EXIT_FAILURE);
}

void strtolower(char *s){
    for(int i = 0; s[i]; i++)
        s[i] = tolower(s[i]);
}

int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
    if (bufp >= BUFSIZE)
        print(RED "ungetch: too many characters" RESET);
    else 
        buf[bufp++] = c;
}

int _getline(char *s, int lim){
    int c, i = 0;
    
    // loop through user input
    while ( i < lim-1 && (c = getchar()) != EOF && c != '\n'){
        *s++ = c;
        i++;
    }
    
    // add null character
    s[i] = '\0';

    // return input size
    return i;
    
}


int getword(char *word, int lim){
    
    int c, getch(void); 
    void ungetch(int); 
    char *w = word;

    while (isspace(c = getch()))
        ;
    
    if (c != EOF) 
        *w++ = c;
    
    if (!isalpha(c)) { 
        *w = '\0';
        return c; 
    }

    for ( ; --lim > 0; w++) {
        if(!isalnum(*w = getch())) {
            ungetch (*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}


int getlineauto(char **input){
    
    // Initial memory allocation
    * input = (char *) malloc(MAXINPUT);
    if (*input == NULL){
        fprintf(stderr, RED "memory allocation failed\n" RESET);
        return -1;
    }
    
    // get input from user
    int size = _getline(*input, MAXINPUT);
    
    // reallocating memory
    *input = (char *) realloc(*input, size);
    
    // return reallocated size of char array
    return size;
}

int readlines(char *input[], int max){

    // Initialize new line string
    char *line;
    int i = 0;

    // Get line from user
    while ((i < max) && (getlineauto(&line) > 0)){

        // add line to input
        input[i++] = line;
    }

    // return length of input array
    return i;
}

void writelines(char *lineptr[], int nlines){

    // decrement number of lines
    while (nlines-- > 0)

        // print line
        printf("%s\n", *lineptr++);
}

int numcmp(const char *numa, const char *numb){
    double v1, v2;

    v1 = atof(numa);
    v2 = atof(numb);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int insstrcmp(const char *str1, const char *str2){
    char *s1 = (char *) str1;
    char *s2 = (char *) str2;
    strtolower(s1);
    strtolower(s2);

    return strcmp(s1, s2);
}

void swap(void *v[], int i, int j){
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

// contains: tests if val exists within v
int contains(void *v[], void * val, int len, int (*comp)(void *, void *)){

    for (int i = 0; i < len; i++)        
        if ((*comp)(val, v[i]) == 0)
            return i;

    return -1;
}

/* qsort: sort v[left]...v[right] into increasing order */
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse){
    int i, last, compare;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++){
        compare = (*comp)(v[i], v[left]);
        compare *= (reverse ? -1 : 1);
        if (compare < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    _qsort(v, left, last-1, comp, reverse);
    _qsort(v, last+1, right, comp, reverse);
}

