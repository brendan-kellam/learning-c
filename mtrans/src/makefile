mtrans : main.o ./network/client.o
	cc -o mtrans main.o ./network/client.o

main.o : main.c ./network/client.h
	cc -c main.c
client.o : client.c client.h
	cc -c client.o

clean :
	rm edit main.o client.o