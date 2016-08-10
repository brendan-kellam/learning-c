
#include "not.h"

int main(int argc, char *argv[]){

	char *line, *result;
	int c, i, count;



	for (i = 1, line = argv[i]; i < argc; i++)
		if (strcmp(line, "not") != 0) 
			panic("not usage: not not not...not (n times)");
		else
			count++;
	
	result = (count % 2 != 0) ? " not" : "";
	printf("I am ");
	for (i = 0; i < count; i++) printf("not ");
	printf("doing something\n");

	printf("Therefore, I am%s doing something! ;)\n", result);

	return 0;
}