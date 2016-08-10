#include "ckey.h"

struct key * pbinsearch(char *word, struct key *tab, int n){

	int cond;

	// get the address of the first and last index
	struct key *low = &tab[0]; 
	struct key *high = &tab[n];
	struct key *mid;

	while (low < high) {
		mid = low + (high-low) / 2; // get the mid address
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}

int comp(struct key *key1, struct key *key2) {
	if (key1->count > key2->count)
		return 1;
	else if(key1->count < key2->count)
		return -1;
	else
		return 0;
}

int equals(struct key *key1, struct key *key2){
	return strcmp(key1->word, key2->word);
}

int main(){

	char word[MAXWORD];
	struct key *p;

	struct key *temp[NKEYS];
	int count = 0;

	while (getword(word, MAXWORD) != EOF) {
		if (isalpha(word[0])) {
			if ((p = pbinsearch(word, keytab, NKEYS)) != NULL) {

				int index = contains((void**) temp, p, count, (int (*)(void*, void*)) equals);
				
				// if p is found within the temp array
				if (index >= 0)
					temp[index]->count++;
				
				// if NOT found in temporary index
				else {
					temp[count++] = p;
					p->count++;
				}
			}
		}
	}

	// preform a quick sort on the temp array
	_qsort((void **) temp, 0, count-1, (int (*)(void*, void*)) comp, TRUE);


	print(RED "UNSORTED:" RESET);
	for (p = keytab; p < keytab + NKEYS; p++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
		
	print("----");

	print(BLU "SORTED:" RESET);
	for (int i = 0; i < count; i++)
		printf("%4d %s\n", temp[i]->count, temp[i]->word);

	return 0;
}

