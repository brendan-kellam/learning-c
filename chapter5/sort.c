
#include "sort.h"


int main(int argc, char *argv[]){

	int nlines; // number of input lines read
	int numeric = FALSE; // TRUE if numeric source
	int reverse = FALSE; // TRUE if reverse sorting enabled
	int fold = FALSE;

	while (--argc > 0) {
		char *line = *++argv;

		if (strcmp(line, "-n") == 0)
			numeric = TRUE;
		else if (strcmp(line, "-r") == 0)
			reverse = TRUE;
		else if (strcmp(line, "-f") == 0)
			fold = TRUE;
		else
			printf(RED "sort: %s is a invalid flag\n" RESET, line);
	}



	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {

		_qsort((void **) lineptr, 0, nlines-1,
			(int (*)(void*, void*))(numeric ? numcmp : (fold ? insstrcmp : strcmp)) , reverse);
		writelines(lineptr, nlines);
		return 0;

	}else{
		printf("input too big to sort\n");
		return 1;
	}	




}