/** NOTES:
 Keyword struct introduces a structure declaration
 A optional structure tag may also be provided following the struct statement
 Variables named in a structure: members
 TO DEFINE A NEW STRUCTURE: struct point pt = {10, 10}
 TO DEFINE A NEW STRUCTURE POINTER: 
 	struct point *pp;
	pp = &pt;
	printf("point is (%d,%d)\n", (*pp).x, (*pp).y);
 
 ---- NOTE ----: its usually good form to create a factory function to initialize new structures

 Valid: struct { int x; } x, y, z;
 Legal struct operations:
 	- copying it/assigning to it as a unit 
 	- taking its address with &
 	- accessing its members
 !!!! ----- NOTE ----- !!!! - when structures are passed to functions, they are PASSED BY VALLUE, NOT BY REFERENCE
 		- I.E a new local instance of a structure will be created upon invocation of a function
 		- NO modification to this local instance will AFFECT the original structure

 If very large structures are to be passed to a function, it is generally more efficient to accept
 	a pointer to the original structure

 members of a structure can be assessed from a pointer in two ways:
 	1. (*pp).x
 	2. p->x

 Note of hierarchal ordering for struct pointers:
 	++p->len - increments len by one
 	(++p)->len - increments p before accessing len
 	*p->str - fetches whatever str points to
 	*p->str++ - increments str after accessing whatever it points to (just like *s++)
 	*p++->str - increments p after accessing whater str points too

 Typedef:
 	Typedef allows for the creation of new data type names
 	Ex:
 		typedef int Length; - produces a synonym for int
 		typedef char *String; - String can now be used!

	REDIFINED USING typedef
	
	typedef struct tnode *Treeptr;

	typedef struct tnode {
		char *word;
		int count;
		Treeptr left;
		Treeptr right;
	} Treenode;



**/



typedef char* String;


#include "../util.h"

#define XMAX 100
#define YMAX 100

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};

// makepoint: make a point from x and y components
struct point makepoint(int x, int y){

	struct point temp;

	temp.x = x;
	temp.y = y;
	return temp;
}

// addpoint: add two points
struct point addpoint(struct point p1, struct point p2){
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

// ptinrect: return 1 if p in r, 0 if not
int ptinrect(struct point p, struct rect r){
	return p.x >= r.pt1.x && p.x < r.pt2.x 
		&& p.y >= r.pt1.x && p.y < r.pt2.y;
}

// canonrect: canonicalize coordinates of rectangle
struct rect canonrect(struct rect r){
	struct rect temp;

	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}

void test(struct point * pt){

	pt->x = 100;
	pt->y = 200;
}

struct point test2(struct point pt){
	pt.x = 300;
	pt.y = 400;
	return pt;
}

void tut1(){
	struct rect screen;
	struct point middle;
	struct point makepoint(int, int);

	screen.pt1 = makepoint(0, 0);
	screen.pt2 = makepoint(XMAX, YMAX);
	middle = makepoint((screen.pt1.x + screen.pt2.x)/2, (screen.pt1.y + screen.pt2.y)/2);

	struct point pt1 = makepoint(10, 10);
	struct point pt2 = makepoint(20, 20);

	struct point tst = addpoint(pt1, pt2);

	printf("pt1~ x: %d | y: %d\n", pt1.x, pt1.y);
	printf("pt2~ x: %d | y: %d\n", pt2.x, pt2.y);
	printf("tst~ x: %d | y: %d\n", tst.x, tst.y);

	struct point origin,  *pp;
	origin = makepoint(0, 0);
	pp = &origin;
	printf("origin is (%d,%d)\n", pp->x, pp->y);

}

int main(){
	print(RED "running.." RESET);

	struct point pt = makepoint(10, 10);
	struct point * ppt = &pt;
	printf("%d\n", (int) ppt);
	++ppt->x;
	printf("x: %d  |  y: %d\n", pt.x, pt.y);

	/*
	pt = test2(pt);
	printf("x: %d  |  y: %d\n", pt.x, pt.y);
	*/

	//test();

	return 0;
}