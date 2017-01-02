
/* Notes:

 --- Simple INPUT/OUTPUT functions ---
								
 The simplest way of dealing with input is:
 	int getchar(void)

 	NOTE: To allow for a program (say prog) to redirect its standard input from command line to a input file (say txt), 
 	use the following command: ./prog <txt 

 To output to the standard output (usually the screen):
 	int putchar(int)

 	NOTE: Again, to output to a file (prog) instead of printing to the screen, use: ./prog >txt

 Varible-length argument lists:
	
 To define a varible-length argument function:
 	void minprintf(char *fmt, ...);

 	NOTE: The ellipses (...) must ALWAYS be present as the final argument

 <stdarg.h> can be used to traverse the variable arguments

 --- Reading/Writing to a file ---

 The standard input is by default assigned to the keyboard, while standard output is assigned to the display



*/

// includes
#include "../util.h"


// function prototypes
void minprintf(char *fmt, ...);


// simplified version of printf
void minprintf(char *fmt, ...){
	va_list ap; // points to each unnamed arg in turn
	char *p, *sval;
	int ival;
	double dval;

	va_start(ap, fmt); // make ap point to 1st unnamed arg
	for (p = fmt; *p; p++) {
		
		if (*p != '%') { // check if the current character is a conversion operator (%)
			putchar(*p);
			continue;
		}

		switch (*++p) { // increment to the argument type (as followed by %), and check what
						// type it corresponds to 
			case 'd':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break; 
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap); // clean up when done
}

void tut1(){
	char *line;
	char monthname[20];
	int day, month, year;

	while (getlineauto(&line) > 0) {
		if (sscanf(line, "%d %s %d"), &day, monthname, &year) == 3)
			printf("valid: %s\n", line);
		else if (sscanf(line, "%d/%d/%d", &day, &month, &year) == 3)
			printf("valid: %s\n", line);
		else
			printf("invalid: %s\n", line);
	}
}

int main(int argc, char *argv[]){


	print("running..");

	//minprintf("hello, this is a %s test. \nCurrently running at %d efficiency. \ntest: %f", "stupid", 23, 30.23);

	int day, month, year;

	scanf("%d/%d/%d", &day, &month, &year);

	minprintf("day: %d, month: %d, year: %d", day, month, year);

	return 0;
}