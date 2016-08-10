/**
 @file
 @author Brendan Kellam <brendan.kellam@mail.mcgill.ca>
 @version 1.0
 
 **/

/* --- guard --- */
#ifndef ckey_h
#define ckey_h

/* --- include statements --- */
#include "../util.h"


/* --- finals --- */
#define MAXWORD 100

struct key {
	char *word;
	int count;
};

struct key keytab[] = { //NOTE: Alphabetical order
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

#define NKEYS (sizeof(keytab) / sizeof(struct key))



/* --- function prototypes --- */
int getword(char *word, int lim);
int binsearch(char *word, struct key *tab, int n);

// prototypes for pckey.c
struct key * pbinsearch(char *word, struct key *tab, int n);

#endif /* --- ckey_h --- */