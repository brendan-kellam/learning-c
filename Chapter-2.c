#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h> //Allows for character tests
#include <math.h> 

/* General Notes */
// Basic data types:
//	char (single byte representing a single ascii character)
// 	int (a integer, reflecting natural size of machine [I.E 32 bits])
// 	float (single-precision floating point)
//	double (Double-percision floating point)
// 
// short: causes integer to be 16bits
// long: causes integer to be 64bits
// 
// Constants:
//  Long constant: add terminal L suffix. Ex: 123456789L
// 	Unsigned constant: add U suffix. Ex: 123U
//  Float: For decimal values, doubles are assumed. Add F suffix to specify. Ex: 124.3f. 
//  Octal: use leading 0. Ex: 31 = 037
//  Hexadecimal: add 0x. Ex: 0xff = 255
//
// Character constants are just single characters. In character constants, arbitrary byte-sized bit patterns can be used to set certain values
// 	(either in hexadecimal or octal)
// EX: Define ASCII vertical tab:
//		#define VTAB '\013';
//		#define VTAB '\xb';
//
// strlen(n) returns the length of a char string, minus the \0 character (found in <string.h>)
//
// Enumeration:
//	a enumeration is a list of constant integer values. Ex: enum boolean { FALSE, TRUE }
//		In this case, FALSE = 0 and TRUE = 1
// If no value is specified for a enum, it will increment from its previous partner.
// Ex: enum months = { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC } 
//
// Constants can be defined using const. Ex: const int pi = 3.141592653589793;
// Constants can be used with array arguments to indicate a function does NOT change said array. Ex: int strlen(const arr[]); [does not change arr]
//
// <ctype.h> header includes a family of functions for character conversions
// important to specify "signed" or "unsigned" non-character data if said data is to be converted into a character
// False = 0, True = (any integer not 0)
// <math.h> package is the math package
//
// On creation of a function prototype, the type of each argument will cause all passes to said function to be coerced
//
// Bitwise Operators:
// NOTE: The following operations may only be applied to integral operands - (char, short, int, long)
// Operations:
//  &  - bitwise AND
//  |  - bitwise inclusive OR
//  ^  - bitwise exclusive OR
//  << - left shift
//  >> - right shift
//  ~  - one's complement (unary) [NOT OPERATION]
//
// Condenced statements:
//  z = (a > b) ? a : b; /* z = max(a, b); */
//
//
//

//DEFINITIONS;
#define EOF 96
#define MAXLINE 1000
#define TRUE 1
#define FALSE 0

//FUNCTION PROTOTYPES:
void rawinput(char input[]);
void copy(char to[], char from[]);
int getlen(char input[]);
int htoi(char s[]);
void squeeze(char s1[], char s2[]);
int any(char s1[], char s2[]);
int lower(int c);


int bitcountv2(unsigned x){
    int b = 0;
    while(x != 0){
        x &= (x-1);
        b++;
    }
    return b;
}

// bitcount: count 1 bits in x
int bitcount(unsigned x){
    int b;
    
    for (b = 0; x != 0; x >>= 1){
        if(x & 01)
            b++;
    }
    return b;
}


int lower(int c){
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

void tut5(){
  printf("%c\n", lower('a'));
}

//MAIN BLOCK:
void rawinput(char input[]){
  int i = 0, c = 0;

  while ((c = getchar()) != EOF){

    if(c == '\n'){
      input[i++] = '\0';
      return;
    }

    input[i] = c;
    i++;
  }

}

/* copy: copy 'from" into 'to'; assume to is big enough */
void copy(char to[], char from[]){
  int i = 0;

  while ((to[i] = from[i]) != '\0')
    ++i;
}


int getlen(char input[]){
  int c = 0, i = 0;
  while((c = input[i]) != '\0') i++;
  return i;
}


//converts hexidecimal string to integer
int htoi(char s[]){

  printf("%s\n", s);

  int count = 0, c = 0, i = getlen(s), r = 0;


  while (i >= 0){
    c = tolower(s[i]);
    
    if(c == '\0'){
      i--;
      continue;
    }


    if(isdigit(c)){
      int d = (c - '0');
      if(d != 0) r += pow(16, count) * d; 

    }else if(isalpha(c) && (c >= 'a' && c <= 'f')){
      int d = (c - 'a');
      r += pow(16, count) * (10 + d);

    }else{
      break;
    }
    
    i--;
    count++;
  }

  return r;
}

void squeeze(char s1[], char s2[]){

  int i, j, k, z, found = FALSE; 

  for(i = j = 0; s1[i] != '\0'; i++){

    found = FALSE;

    for(k = 0; s2[k] != '\0'; k++){
      if(s1[i] == s2[k]){
        found = TRUE; 
        break;
      }
    }

    if(!found){
      s1[j++] = s1[i];
    }

  }

  s1[j] = '\0';

  printf("%s\n", s1);
}

int any(char s1[], char s2[]){

  int i, j;

  for(i = 0; s1[i] != '\0'; i++){

    for(j = 0; s2[j] != '\0'; j++){
      if(s1[i] == s2[j]) return i;
    }

  }

  return -1;
}


void tut4(){
  char s1[MAXLINE];
  char s2[MAXLINE];
  rawinput(s1);
  rawinput(s2);

  int res = any(s1, s2);
  printf("Result: %d\n", res);
}

void tut3(){

  char s1[MAXLINE];
  char s2[MAXLINE];

  rawinput(s1);
  rawinput(s2);

  squeeze(s1, s2);

}

void tut2(){

  char input[MAXLINE];
  rawinput(input);
  
  int res = htoi(input);
  printf("Result: %d\n", res);

}


void tut1(){
	printf("Unsigned char max: %d\n", UCHAR_MAX);
  	printf("Signed char max: %d\n", SCHAR_MAX);
  	printf("Signed char min: %d\n", SCHAR_MIN);

  	unsigned int i = ~0;
  	printf("Unsigned int max: %u\n", i);
  	printf("Signed int max: %d\n", i / 2);
  	printf("Signed int min: %d\n",  - (i / 2) - 1);
}


int main(){
    printf("%cC\n", lower('A'));
    
    return 0;
}