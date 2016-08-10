
#include "expr.h"

void push(double value){
	if (stack_height == STACK_SIZE)
		panic("stack is too high!");
	stack[stack_height++] = value;
}

double pop(void){
	if (stack_height == 0)
		panic("stack is empty!");
	return stack[--stack_height];
}


int main(int argc, char **argv){
	printf(BLU "running..\n" RESET);

	int i;
	double value; 

	for (int i = 1; i < argc; ++i){
		printf("%c\n", argv[i][0]);
	}

	for (i = 1; i < argc; ++i){
		switch (argv[i][0]){
			case '\0':
				panic("empty command line argument");
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				push(atof(argv[i]));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '-':
				value = pop();
				push(pop() - value);
				break;
			case '*':
				push(pop() * pop());
				break;
			case '/':
				value = pop();
				push(pop() / value);
				break;
			default:
				panic("unknown operator");
				break;
		}	
	}

	printf("%g\n", pop());
	return 0;
}