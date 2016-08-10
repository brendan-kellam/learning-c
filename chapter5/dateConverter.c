
#include "dateConverter.h"


int isleap(const int year){

	//check validity of year
	if (year < 0) return ERROR;

	//return if leap year
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int day_of_year(int year, int month, int day){
	
	int i, leap;

	//define if year is leap or not
	leap = isleap(year);

	//check validity of inputs
	if (leap == -1 || month < 1 || month > 12 || day < 1 || day > 31) 
		return ERROR;

	//calculate given day
	for (i = 1; i < month; i++)
		day += daytab[leap][i];

	return day;
}


void month_day(int year, int yearday, int *pmonth, int *pday){
	int i, leap;

	//define if year is leap or not
	leap = isleap(year);

	if (leap == -1 || yearday < 1 || yearday > 366) return;

	
	
	//calculate month and day
	for (i = 1; yearday > daytab[leap][i]; i++){
		print("here");
		yearday -= daytab[leap][i];
	}

	//set pointer month and day
	*pmonth = i;
	*pday = yearday;
}

char *month_name(int n){
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June", 
		"July", "August", "September",
		"October", "November", "December"
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}

void getAverage(int *arr, int size, double *pres){
	int i, sum = 0;
	double avg;

	for (i = 0; i < size; ++i){
		sum += arr[i];
	}

	avg = (double)sum / size;
	*pres = avg;
}


int main(){

	int month; 
	int day;

	//printf("%d\n", day_of_year(1996, 1, 20));

	month_day(1996, 20, &month, &day);
	printf("month: %d  |  day: %d\n", month, day);

	char *name = month_name(-1);
	print(name);


	int arr[4] = {100, 30, 20, 31};
	double result;
	getAverage(arr, 4, &result);
	printf("%f\n", result);

	return 0;
}