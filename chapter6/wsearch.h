/* --- guard --- */
#ifndef ckey_h
#define ckey_h

/* --- include statements --- */
#include "../util.h"


/* --- definitions --- */
#define MAXWORD 100


/*
	REDIFINED USING typedef
	
	typedef struct tnode *Treeptr;

	typedef struct tnode {
		char *word;
		int count;
		Treeptr left;
		Treeptr right;
	} Treenode;

*/



struct tnode { // the tree node (used for binary trees)
	char *word; // points to the text
	int count;	// number of occurrences
	struct tnode *left; // left child
	struct tnode *right; // right child
};


/* --- function prototypes	--- */
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct tnode *talloc(void);
char * _strdup(char *s);

/* --- finals --- */
#endif /* --- ckey_h --- */