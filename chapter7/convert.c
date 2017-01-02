
#include <stdio.h>
#include <ctype.h>
#include <string.h> 

/* convert.c:
	Must be compiled in two different executable forms:
		1. tolower
		2. toupper

	./tolower: converts input to all lowercase
	./toupper: converts input to all uppercase

*/

int main(int argc, char *argv[]){

	// skip to the first alphabetic character
	while(!isalpha(*++argv[0]));

	// exec to the executed "name"
	char *exec = argv[0];

	// create a function pointer for either toupper or tolower
	int (*func)(int c); 

	// test the executed name to see if it properly aligns with either
	//	"toupper" or "tolower". Assign function pointer accordingly
	if (strcmp(exec, "tolower") == 0)
		func = tolower;
	else if (strcmp(exec, "toupper") == 0)
		func = toupper;
	else 
		return -1;

	// 
	char c;
	while ((c = getchar()) != EOF)
		putchar(func(c));


	return 0;
}