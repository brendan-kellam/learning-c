/**
 @file
 @author Brendan Kellam <brendan.kellam@mail.mcgill.ca>
 @version 1.0
 
**/

/* --- notes --- 
a non-leap year is defined as 0 (I.E FALSE)
a leap year is defined as 1 (I.E TRUE)
	ex: daytab[0][2] -> returns days in February during a NON LEAP YEAR
		daytab[1][3] -> returns days in March during LEAP YEAR

[i][j] -> i: columns -- j: rows
when passing a two-dimensional array to function, parameter declaration
	must include number of column
	ex: f(int daytab[][13]) { ... } //valid
	ex: f(int daytab[2][13]) { ... } //also valid
	ex: f(int (*daytab)[13]) { ... } //also valid

*/

/* --- guard --- */
#ifndef dateConverter_h
#define dateConverter_h


/* --- include statements --- */
#include "../util.h"


/* --- finals --- */

/*
	daytab: two-dimensional char array to store # of days in a given month
		for leap and non-leap years.
	NOTE: daytab of length = 13 with index 0 = 0 to allow for natural
		use of months (I.E January = 1, February = 2 etc.);

*/
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, //non leap year
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} //leap year
};



/* --- function prototypes --- */


/*
	isleap: returns if a given AC year (I.E year >= 0) is leap
	parameters
		const int year: given year (ex: 1998)
	returns
		FALSE (0) -> not a leap year
		TRUE (1) -> leap year
	return flags
		1. If year does not exist (ex: -141), return: -1	
*/
int isleap(const int year);


/*
	day_of_year: converts year, month and day of month to a day of the year
	parameters
		int year: year of date (ex: 1998)
		int month: month of date (ex: 8 {August})
		int day: day of date (ex: 28)
	returns
		the day of a given year
	return flags
		1. If any error occurs (I.E improper year, month or day), return: -1
*/
int day_of_year(int year, int month, int day);



/*
	month_day: converts the integer day of the year into the month and day
	parameters
		int year: year of day (ex: 1998)
		int yearday: day of year (ex: 28)
		int *pmonth: return month pointer
		int *pday: return day pointer
	error handling
		1. If Error occurs, pmonth and pday will not be re-assigned,
			function will break out before  their assignment
*/
void month_day(int year, int yearday, int *pmonth, int *pday);

/*
	*month_name: return name of n-th month
	parameters
		int n: n-th month
	error handling
		1. if n is less than 1 or greater than 12, return
			string pointer to: "Illegal month"
*/
char *month_name(int n);



#endif /*--- dateConverter_h --- */



