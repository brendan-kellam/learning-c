
#include "tail.h"

int main(int argc, char *argv[]) {
	if (argc > 2) {
		printf(RED "tail: too many arguments!\n" RESET);
		return -1;
	}

	int n = 10, c, valid = TRUE;

	if (argc == 2){
		if ((*++argv)[0] == '-'){
			
			int length = sizeof(*argv) - 1, i = 0;
			char line[length];

			while ((c = *++argv[0])){

				if ((c >= '0') && (c <= '9')){
					line[i++] = c;

				}else{
					printf("tail: %c is not a valid number\n", c);
					valid = FALSE;
					break;
				}
			}

			if(i != 0) n = atoi(line);
		}else valid = FALSE;
	}
	
	if (valid != TRUE)
		printf("Usage: tail -n\n");
	else{
		printf("NUMBER: %d\n", n);




	}


	return 0;
}