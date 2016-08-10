/**
NOTES:

the statement:
struct key {
	char *word;
	int count;
} keytab[NKEYS];


is equivalent to:
struct key {
	char *word;
	int count;
};

struct key keytab[NKEYS];

**/


#include "ckey.h"

int binsearch(char *word, struct key tab[], int n){
	int cond;
	int low, high, mid; 

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else 
			return mid;
	}
	return -1;
}

int main(){

	print(BLU "Hello World!" RESET);

	char *test;

	printf("%d\n", getword(test, 100));
	//printf("%d\n", 't');



	int n;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF) // get each word

		if (isalpha(word[0])) // check if the first character is a letter

			if ((n = binsearch(word, keytab, NKEYS)) >= 0) // search for the word in the hashmap
				keytab[n].count++; // increment the value entry

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);


	return 0;
}