//standard input output library
#include <stdio.h>

/* General Notes: */
// \n is a example of a escape sequence
//integer division truncates
// %6.1f describes a float that is to be printed with at least
// 	six charters wide, with one digit after the decimal
// #define name replacement-text (similar to final in java)
// note: define quantities are symbolic constants, not variables
// In C, any assignment is a expression and has a value.
// Double defines "double precision" compared to floats that only have "single precision"
// Function definitions must match their corresponding function prototype based on return type and parameter types (not names)
// A array passed into a function WILL NOT have a temporary copy instantiated in the function. This means when int a[]; is passed into to
// 	function:  b(int a[]); any changes made to a[] in b() will directly affect the original instance of a[].
// In C, strings are represented as char[] (character arrays). The final character in a string must be '\0'. This character is required for
//	printf(%s, char[]); statement. 
// Variables instantiated and reconstructed in functions are known as automatic variables
// Variables instantiated outside of functions (or in the outermost scope) are known as external variables
// The "extern" declaration should be used when a external variable is being used in a function
// NOTE: the extern declaration can be omitted if the external variable definition occurs in the source file above the function's declaration 
// void must be a parameter in functions that have no parameters


//NOTE MACRO REDEFINITION
#define EOF 96

//define boolean representations
#define FALSE 0
#define TRUE 1

//define the maxline input
#define MAXLINE 1000

//the maximum amount of lines
#define MAXLINES 10


//gets the length of line[]
int getlength(char line[], int maxline);

//copy from[] -> to[]
void copy(char to[], char from[]);

//trims trailing blanks and tabs
void trim(char line[]);

//gets the length of a line
int getlen(char line[]);

//reverse a string
void reverse(char s[]);

//accepts input from console
void rawinput(char input[]);

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

void detab(char input[]);

void detab(char input[]){

	int i = 0, c = 0, k = 0;
	while((c = input[i]) != '\0'){
		
		if(c == '\t'){

			int j = i+1;
			while((k = input[j]) != '\t' || (k = input[j]) != '\0'){
				printf("%c", k);
				j++;
			}

		}

		//printf("%c", c);
		i++;
	}

	//printf("\n");
}


void tut23(){
	char input[MAXLINE];
	int i = 0, c = 0;
	while ((c = getchar()) != EOF){

		if(c == '\n'){
			input[i++] = '\0';
			i = 0;
			detab(input);
		}

		input[i] = c;
		i++;
	}
}


//---LONGEST LINE REVISED---

int max; /* maximum length seen so far */
char line[MAXLINE];
char longest[MAXLINE];

void copyinput();
int getinputedline();


void copyinput(){
	int i = 0;
	extern char line[], longest[];

	while ((longest[i] = line[i]) != '\0'){
		++i;
	}
}

int getinputedline(){
	int c, i;
	extern char line[];

	for (i = 0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i){
		line[i] = c;
	}

	if(c == '\n'){
		line[i] = c;
		++i;
	}

	line[i] = '\0';
	return i; 
}

void tut22(){
	int len;
	
	//import external variables
	extern int max;
	extern char longest[];

	max = 0;
	while((len = getinputedline()) > 0){
		if (len > max){
			max = len;
			copyinput();
		}
	}
	if(max > 0)
		printf("%s", longest);
}


//reverses a string
void reverse(char s[]){
	int len = getlen(s);
	char rem[len];

	int j = 0;
	for(int i = len-1; i >= 0; i--){
		rem[j] = s[i];
		j++;
	}
	copy(s, rem);
}

void tut21(){

	char line[MAXLINE];
	rawinput(line);
	reverse(line);
	printf("%s\n", line);
}



int getlen(char line[]){
	int c = 0, i = 0;
	while((c = line[i]) != '\0'){
		++i;
	}
	return i;
}

void trim(char line[]){
	int i = 0, c = 0, pos = 0, mark = FALSE;
	char rem[MAXLINE];

	while((c = line[i]) != '\0'){	

		if(c == ' '){
			mark = TRUE;
			pos = i;
		}else{
			mark = FALSE;
		}

		i++;
	}

	if(mark == TRUE){

		for(int j = 0; j < pos; j++){
			rem[j] = line[j];
		}

		rem[pos] = '\0';
		copy(line, rem);

		printf("%d", getlen(line));
	}
}

void tut20(){

	int c = 0, i = 0;
	char line[MAXLINE];

	while ((c = getchar()) != EOF){

		if(c == '\n'){
			line[i++] = '\0';
			i = 0;
			trim(line);
		}

		line[i] = c;
		i++;
	}

}


//print all inputs greater than 80 characters
void tut19(){

	char lines[MAXLINES][MAXLINE];
	char line[MAXLINE];
	int i = 0, len;

	while ((len = getlength(line, MAXLINE)) > 0 && i < MAXLINES){
		if(len > 80){
			copy(lines[i], line);
			++i;
		}
	}

	for(int j = 0; j < i; j++){
		printf("%s", lines[j]);
	}
}

//SECTION 1.9 - CHARACTER ARRAYS


void tut18(){
	int len; /* current line length */
	int max; /* maximum length seen so far */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE]; /* longest line saved here */

	max = 0;
	while ((len = getlength(line, MAXLINE)) > 0){
		if(len > max) {
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0)
		printf("%s", longest);
}

/* getline: read a line into s, return length */
int getlength(char s[], int lim){

	int c, count;

	//loop the inputed line
	for(count = 0; count < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++count)
		s[count] = c;


	//ON-BREAKAGE FROM CHARACTER INPUT//

	//handle new-line 
	if(c == '\n'){
		s[count] = c;
		++count;
	}

	//add null character to character array
	s[count] = '\0';

	//return count
	return count;
}

/* copy: copy 'from" into 'to'; assume to is big enough */
void copy(char to[], char from[]){
	int i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;
}



float fahrToCels(float fahr);

float fahrToCels(float fahr){
	return (5.0/9.0) * (fahr-32.0);
}

void tut17(){
	printf("%f\n", fahrToCels(80));
}


//function prototype representing the power function bellow
int power(int m, int n);


/* power function. raise base to n-th power; n >= 0 */
int power(int base, int n){
	int i, p; 

	p = 1;
	for(i = 1; i <= n; ++i)
		p = p * base;
	return p;
}


//functions intro
void tut16(){
	
	for(int i = 0; i < 10; ++i){
		printf("%d %d %d\n", i, power(2, i), power(-3, i));
	}
}


//prints histogram of frequencies of different characters
void tut15(){

	//create new array of character coutns
	int cArr[1000];

	//set a new character
	int c = 0;

	//set initial values of array
	for (int i = 0; i < 1000; ++i)
        cArr[i] = 0;

    //loop and get characters
	while ((c = getchar()) != EOF){

		if (c >= 0 && c < 1000 && c != '\n' && c != ' ')
			cArr[c] = cArr[c] + 1;
	}

	for(int i = 0; i < 1000; i++){
		int freq = cArr[i];

		if(freq > 0){

			printf("%c ", i);

			for(int j = 0; j < freq; j++){
				printf("|");
			}
			printf("\n");
		}
	}

}

//histogram exercise
void tut14(){

	//set inWord int (boolean represented)
	int inWord = FALSE;
	int c, wc = 0;

	while ((c = getchar()) != EOF){

		//if a blank, tab or newline is detected, the program is not in a word
		if(c == ' ')
			inWord = FALSE;
		else if(c == '\t' || c=='\n'){
			inWord = FALSE;
			
			for(int i = 0; i < wc; i++){
				printf("|");
			}
			printf("\n");

			wc = 0;
		}

		else if(inWord == FALSE){
			wc++;
			inWord = TRUE;
		}


	}
	

}

void tut13(){

	int c, i, nwhite, nother;
    int ndigit[10];
    nwhite = nother = 0;

    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;

    //get the current line
    while ((c = getchar()) != EOF)

    	//checks to see if character int is between 0 and 9
        if (c >= '0' && c <= '9'){

        	//set a refrence index
        	int ref = c - '0';

        	//increment digit array
            ++ndigit[ref];

        }else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;

    printf("digits =");

    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);

    printf(", white space = %d, other = %d\n", nwhite, nother);

}

//prints input one word at a time
void tut12(){

	int c;

	while((c = getchar()) != EOF){

		if(c == ' ') putchar('\n');
		else putchar(c);

	}
}

//counts characters, words and lines
void tut11(){

	int c, nl, nw, nc, inWord;

	//initially, inWord is set to false
	inWord = FALSE;

	//set line count, word count and char count to 0
	nl = nw = nc = 0;
	while((c = getchar()) != EOF){

		//increment character count
		++nc;

		//if a newline is detected, then the number of lines must be incremented
		if(c == '\n') ++nl;

		//if a blank, tab or newline is detected, the program is not in a word
		if(c == ' ' || c == '\t' || c=='\n') inWord = FALSE;

		//else if the program is not in a word, increment word count and set inWord to TRUE
		else if(inWord == FALSE){
			inWord = TRUE;
			++nw;
		}

	}
	printf("%d %d %d\n", nl, nw, nc);
}

//replace all backspaces and tabs
void tut10(){

	int c;

	while((c = getchar()) != EOF){

		if(c == '\t') putchar('\\');
		else if(c == '\b') putchar('\\');
		else putchar(c);
	}

}


//blank replacer
void tut9(){

	int c, inspace = FALSE;

	while((c = getchar()) != EOF){

		if(c == ' '){
			if(inspace == FALSE){
				inspace = TRUE;
				putchar(c);
			}
		}else{
			inspace = FALSE;
			putchar(c);
		}
	}

}

//count all blanks, tabs and newlines
void tut8(){
	int c, count = 0;

	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\t' || c == '\n')
			++count;
	}
	printf("count:%d", count);

}

//count number of lines
void tut7(){
	int c, nl;

	nl = 0;
	while((c = getchar()) != EOF){

		//this integer character comparison is legal due to the nature of a character.
		//a character represents a ascii int ('\n' represents 10)
		if(c =='\n')
			++nl;
	}
	printf("%d\n", nl);
}


//count characters in input
void tut6(){

	//hold the count (double used to provide more memory)
	double nc;

	nc = 0;

	//while (getchar() != EOF) ++nc;
	for(nc = 0; getchar() != EOF; ++nc);

	printf("%.0f\n", nc);
}


//simple copy program
void tut5(){

	//int is defined here as it must be large enough to hold any value getchar returns aswell as EOF.
	//EOF is a character that represents "end of file", and represents -1
	int c;

	printf("%d\n\n", getchar());
	printf("%d\n", getchar() != EOF);
	printf("%d\n", EOF);

	while ((c = getchar()) != EOF){
		putchar(c);
	}
}


#define LOWER 0
#define UPPER 300
#define STEP 20

//print fahrenheit-celsius table
void tut4(){

	int fahr;

	for(fahr = LOWER; fahr <= UPPER; fahr+=STEP){
		printf("%3d %6.1f \n", fahr, (5.0/9.0)*(fahr-32));
	}
}

//convert celsius to fahrenheit
void tut3(){
	float fahr, celsius;

	int lower = -20;
	int upper = 100;
	int step = 1;

	celsius = lower;

	while(celsius <= upper){
		fahr = (9.0*celsius)/5.0 + 32.0;
		printf("%3.0f\t%6.1f\n", celsius, fahr);
		celsius += step;
	}

}

//convert fahrenheit to celsius
void tut2(){
	float fahr, celsius;

	int lower = 0;
	int upper = 300;
	int step = 20;

	fahr = lower;

	printf("Fahrenheit vs Celsius\n");
	while(fahr <= upper){

		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f\t%6.2f\t\n", fahr, celsius);
		fahr = fahr + step;
	}
}

void tut1(){
	//example of a character string printout
	printf("hello, world!\n");
}

int main(){
	printf("running\n\n");
	tut23();
	return 0;
}



