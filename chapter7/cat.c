
/*	NOTES;
 Before a file can be read or written, it must first be opened.
 A library function is supplied for this purpose:
 	FILE *fopen(char *name, char *mode);

 returns:
 	A pointer to a FILE struct (the file pointer)
 	NULL - on error

 NOTES:
 	the mode parameter (string) indicates how one intends to use the file that is being read.
 	Allowable modes:
 		- read: "r"
 		- write: "w"
 		- append: "a"
 		- binary text: "b"

 	If a file is not found, it is created if possible

 the FILE structure:

 FILE *fp;
 fp = fopen(char *name, char *mode);

 	This says fp is a pointer to a FILE and fopen returns a pointer to a FILE.

 The standard library file pointers are:
 	- stdin
 	- stdout
 	- stderr

 As such, the macros getchar() and putchar(s) can be defined as:
 	#define getchar() getc(stdin)
 	#define putchar(c) putc((c), stdout)

 useful functions:
 	int getc(FILE *fp);
 	int putc(int c, FILE *fp);
 	int fscanf(FILE *fp, char *format, ...);
 	int fprintf(FILE *fp, char *format, ...);
 	char *fgets(char *line, int maxline, FILE *fp);
 	int fputs(char *line, FILE *fp);


*/

#include "../util.h"

int getlinee(char *line, int max){
	if (fgets(line, max, stdin) == NULL)
		return 0;
	else
		return strlen(line);
}

void filecopy(FILE *ifp, FILE *ofp){
	int c;

	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);
}

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]){

	FILE *fp;
	void filecopy(FILE *, FILE *);
	char *prog = argv[0]; // program name for errors

	if (argc == 1) // no arguments; copy standard input
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) != NULL){
				filecopy(fp, stdout);
				fclose(fp);
			} else {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}

	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}

	exit(0);
}