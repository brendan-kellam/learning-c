
#include <stdio.h>
#include <stdlib.h>

/* 
 malloc() takes a single argument (the amount of memory to allocate in bytes)
 calloc() needs two arguments (the number of variables to allocate in memory, and the size in bytes of a single variable).
 
 note: malloc returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type.
 The use of casting is required in C++ due to the strong type system, whereas this is not the case in C.
*/


int main() {
    
    printf("%d\n", NULL);
    int howMany;
    int total = 0;
    float average = 0.0;
    int * pointsArray;
    
    printf("enter count\n");
    scanf("%d", &howMany);
    
    pointsArray = (int *) malloc(howMany * sizeof(int));
    
    printf("Enter them hoss! \n");
    
    for (int i = 0; i < howMany; i++){
        scanf("%d", &pointsArray[i]);
        total += pointsArray[i];
        printf("%d\n", total);
    }
    
    average = (float)total / (float)howMany;
    printf("%f\n", average);
    
    free(pointsArray);
    
    
    //int * points; /* points to first item in heap */
    
    //points = (int *) malloc(5 * sizeof(int)); //malloc (size in bytes)
    
    
    //free(points);
    
   
    /*
    char test[] = "32.01032";
    char * p = test, c;
    printf("%d\n", (int) p);
    
    while ((c = *p++) != '\0') {
        printf("%c\n", c);
        printf("%d\n", (int) p);
    }
    
    p = test;
    printf("\n\n\n%d\n", (int) p);
    
    double testd = atof(test);
    printf("%s\n", test);
    printf("%f\n", testd);
    */
    
    return 0;
}