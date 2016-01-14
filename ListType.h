#define MAXLISTSIZE 13
#define MAXNAMESIZE 20

/*typedef for type Chicken*/
typedef struct {
	char avatar;
	int hp;
	char name[MAXNAMESIZE];
	int x;
	int y;
	int direction;
} Chicken;

/*typedef for the List*/
typedef struct {
	Chicken items[MAXLISTSIZE];
	int size;
} List;
