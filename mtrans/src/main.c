
/* --- include statements --- */
#include <stdio.h>
#include "./network/client.h"

/* --- definitions --- */
#define ADDRESS "./asdfa"


static void initNetworking(void){
	init();

}



int main(int argc, char * argv[]){
	fprintf(stderr, "running..\n");


	fprintf(stderr, "initializing networking...\n");
	initNetworking();
	fprintf(stderr, "done!\n");

	return 0;
}