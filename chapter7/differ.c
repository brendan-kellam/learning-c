
/*	NOTES;
*/

#include "../util.h"

#define MAXLINE 10000

int main(int argc, char *argv[]){
	print("running..");
	char *prog = argv[0]; 

	if (argc != 3) {
		fprintf(stderr, "%s: incorrect usage!", prog);
		exit(1);
	} 

	char *f1 = argv[1], *f2 = argv[2];
	char line1[MAXLINE], line2[MAXLINE];
	FILE *fp1, *fp2;
	int line = 1;

	if ( (fp1 = fopen(argv[1], "r")) != NULL && (fp2 = fopen(argv[2], "r")) != NULL ) {
			
		
		do {

			line1 = fgets(line1, MAXLINE, fp1);
			line2 = fgets(line2, MAXLINE, fp2);

			if (strcmp(line1, line2) != 0) {
				fprintf(stderr, "lines inequivalent at line: %d \n%s:%d:%s \n%s:%d:%s", line, f1, line, line1, f2, line, line2);
				fclose(fp1);
				fclose(fp2);
				exit(2);
			}

			line++;
		} while ((line1 != NULL) && (line2 != NULL));



		/*
		while ( strcmp(fgets(line1, MAXLINE, fp1), fgets(line2, MAXLINE, fp2)) == 0 ) {
			printf("here\n");
		}*/

		printf("%s\n", line1);
	} else {
		fprintf(stderr, "%s: File does not exist!", prog);
		exit(2);
	}

	fclose(fp1);
	fclose(fp2);

	exit(0);
}