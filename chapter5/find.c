#include "find.h"

/* NOTES: 
(*++argv)[0] points to the first character of each argument string
*++argv[0] increments the pointer argv[0]

*/


int main(int argc, char *argv[]){

	char *line;
	long lineno = 0;
	int c, except = FALSE, number = FALSE, found = FALSE;

	while (--argc > 0 && (*++argv)[0] == '-'){
		while ((c = *++argv[0])){
			printf("character: %c\n", c);
			switch (c){
				case 'x':
					except = TRUE;
					break;
				case 'n':
					number = TRUE;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = ERROR;
					break;
			}
		}
	}

	if (argc != 1)
		printf("Usage: find -x -n pattern\n");
	else
		while (getlineauto(&line) > 0 ) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s\n", line);
				found++;
			}
		}

	return found;
}