#include "Functions.h"

/*
copies values from one chicken to another.
*/
static void copyItem (Chicken *Y, Chicken X) {
	Y->avatar = X.avatar;
	Y->hp = X.hp;
	strncpy(Y->name, X.name, MAXNAMESIZE - 1);
	Y->x = X.x;
	Y->y = X.y;
}

/*
sets passed in values equal to those of an item of type chicken (C).
*/
void InitializeChicken (char ava, int hp, char name[MAXNAMESIZE], Chicken *C) {
	C->avatar = ava;
	C->hp = hp;
	strncpy(C->name, name, MAXNAMESIZE - 1);
	C->name[MAXNAMESIZE - 1] = '\0';
	C->x = 0;
	C->y = 0;
}

/*
initializes a list by setting its size equal to 0.
*/
void Initialize (List *L) {
	L->size=0;
}

/*
inserts a chicken item into a specific position of the list.
*/
void Insert (Chicken X, int position, List *L) {
  	int i;
	for (i=L->size; i>position; i--) { 
		copyItem(&L->items[i],L->items[i-1]);
	}
	copyItem(&L->items[position],X);
	L->size++;
}

/*
removes a chicken from the list.
*/
void Remove (int position, List *L) {
	int i;
	L->size--;
	for (i=position; i<L->size; i++) {
		copyItem(&L->items[i],L->items[i+1]);
	}
}

/*
returns 1 if the list is full, 0 otherwise.
*/
int Full (List *L) {
	return L->size==MAXLISTSIZE;
}


