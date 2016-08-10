calc : main.o getop.o stack.o getch.o
	cc -o calc main.o getop.o stack.o getch.o

main.o : main.c calc.h
	cc -c main.c
getop.o : getop.c calc.h
	cc -c getop.c
stack.o : stack.c calc.h
	cc -c stack.c
getch.o : getch.c calc.h
	cc -c getch.c

clean :
	rm edit main.o getop.o stack.o getch.o