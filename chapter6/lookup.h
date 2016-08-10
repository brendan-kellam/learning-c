
/* --- guard --- */
#ifndef ckey_h
#define ckey_h

/* --- include statements --- */
#include "../util.h"


/* --- definitions --- */
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

struct nlist {
	struct nlist *next; // next entry in the linked list
	char *name;			// defined name
	char *defn;			// replacement text
};

/* --- function prototypes --- */



#endif