/**
 @file
 @author Brendan Kellam <brendan.kellam@mail.mcgill.ca>
 @version 1.0
 
 **/

/* --- guard --- */
#ifndef util_h
#define util_h

/* --- include statements --- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>


/* --- finals --- */
#define ERROR -1
#define FALSE 0 /* boolean FALSE */
#define TRUE 1  /* boolean TRUE */
#define MAXINPUT 100000
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */


#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


/* --- function prototypes --- */


/* print: accept string and print to screen with added '\n'
 parameters
    input: pointer char array reference
*/
void print(const char *input);

/* panic: accept error string, print to screen w/ '\n'
		and exit the program
 NOTE: this function will TERMINATE the PROGRAM!!!
 parameters
 	input: pointer char array reference
*/
void panic(const char *error);


/* strtolower: convert string s to all lowercase
 parameters
 	s: char pointer to input string
*/
void strtolower(char *s);

/* getch: get a (possibly pushed back) character
 NOTE: this function utilizes char buf[] array
*/
int getch(void);

/* ungetch: push character back on input
 NOTE: this function utilizes char buf[] array
*/
void ungetch(int c);

/* _getline: accept input of length = size from user
 parameters
    input: vacant pre-allocated pointer char array
    size: length of input array
 returns
    size: length of used memory in char array
 
*/
int _getline(char *input, int size);


/* getword: get next word or character from input
*/
int getword(char *word, int lim);


/* getlineauto: get input of length <= MAXINPUT (100000) from user
 parameters
    input: pointer-pointer char array reference
 returns
    length of char array
 return flags
    1. If input is negative, malloc was unable to allocate memory
 error handling
    1. If input exceeds MAXINPUT, remaining input will be cut off.
 */

int getlineauto(char **input);


/* readlines: read a number (less than max) of lines from user  
 parameters
 	input: array of char pointers (strings)
 	max: maximum number of lines read from user
 returns
 	number of lines read
*/
int readlines(char *input[], int max);


/* writelines: write nlines lines to screen
 parameters
 	output: array of char pointers (strings)
 	nlines: number of lines to print
*/
void writelines(char *output[], int nlines);


/* numcmp: compare two numbers represented as characters
 parameters
	numa/numb: two numbers to compare
 returns
 	-1: numa < numb
 	1: numa > numb
 	0: numa = numb
*/
int numcmp(const char *numa, const char *numb);

/* ins: "insensitive string comparison" compares two strings without case-sensitivity 
 parameters
 	str1/str2: two strings to compare
 returns
 	-1: str1 < str2
 	1: str1 > str2
 	0: str1 = str2
*/
int insstrcmp(const char *str1, const char *str2);


/* swap: swap v[i] with v[j]
 parameters
 	v[]: array of void pointers (I.E pointer of any type)
 	i/j: int indexes to swap
*/
void swap(void *v[], int i, int j);


/* contains: given a v[] pointer array, check if val exists within it. If val DOES exist within v, return the index
    where v exists
 parameters
    v[]: array of void pointers (so any pointer type)
    val: pointer to value being searched for
    len: length of array
    (*comp): comparison function (much like the one used in the _qsort function)
 returns
    the index where val exists
 return flags 
    1. If val DOES NOT exist within v, -1 will be returned
*/
int contains(void *v[], void * val, int len, int (*comp)(void *, void *));


/* _qsort: quick-sort v[] pointer array using *comp comparison function
 parameters
 	v[]: array of void pointers (so any pointer type)
 	left/right: bounds of sorting
 	(*comp): comparison function (function MUST accept two pointers to compare and return a int flag)
 	reverse: change sorting direction (reverse = TRUE indicates reverse)
 NOTES: this function is recursively called
*/
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse);


#endif /* --- util_h --- */
