#include "ListType.h"

extern void Initialize (List *L);
extern void InitializeChicken (char ava, int hp, char name[MAXNAMESIZE], Chicken *C);
extern void Insert (Chicken X, int position, List *L);
extern void Remove (int position, List *L);
extern int Full (List *L);
