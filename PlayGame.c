#include "Functions.h"

/*
Loops through the three included levels. Displays the shop menu,
lets the user buy chickens and start the game. Checks if the
user has won or lost, displays the appropriate message and exits.
*/
void PlayGame(void) {
	int winCheck = 1;
	int levelCount = 1;
	int coins = 100;
	char input[BUF];
	char map[22][80];
	List L;

	Initialize(&L);

	while(winCheck == 1 && levelCount <= 3) {

		strcpy(input, "asd");
		printf("Welcome to Level %d!\n", levelCount); fflush(stdout);
		while(strcmp(input, "s\n") != 0 && strcmp(input, "4\n") != 0) {
			printf("SHOP:\n1. Chick(c)   ($10)\n2. Hen(H)     ($25)\n3. Rooster(R) ($50)\n4. Start Level\n\n"); fflush(stdout);
			printf("Available Coins: $%d\n", coins); fflush(stdout);
			printf("Current Number of Chickens (Max 13): %d\n>", L.size); fflush(stdout);
			fgets(input, BUF, stdin);
			coins = Shop(input, coins, &L);
		}

		/*load the level*/
		if(levelCount == 1)
			Load("level1.txt", map);
		else if(levelCount == 2)
			Load("level2.txt", map);
		else if(levelCount == 3)
			Load("level3.txt", map);
	
		/*return 1 if user completed level, 0 if they failed*/
		winCheck = Run(&L, map, levelCount);
		endwin();

		/*award resources based on which level was completed*/
		if(levelCount == 1 && winCheck == 1) {
			coins = coins + 150;
		}else if(levelCount == 2 && winCheck == 1) {
			coins = coins + 200;
		}else if(levelCount == 3 && winCheck == 1) {
			coins = coins + 300;
		}

		levelCount++;
		fflush(stdout);
	}


	if(winCheck == 1 && levelCount == 4) {
		printf("Congratulations! You escaped from the farm with %d chickens remaining!\n", L.size);
		exit(0);
	}
    else {
		printf("You lose, but the farmers eat well.\n");
		exit(0);
	}
}

/*
takes in the input char, coins the user has, and the list of chickens.
Checks if the user is able to buy the selected chicken, adds it to
the list, returns remaining coins.
*/
int Shop(char input[], int coins, List *L) {
	Chicken C;

	if(Full(L) == 1) {
		printf("You have the maximum number of chickens!\nPlease start the level.\n");
		return coins;
	}

	if(strcmp(input, "1\n") == 0) {
		if(coins >= 10) {
			coins = coins - 10;
			InitializeChicken('c', CHP, "Chick", &C);
			Insert(C, L->size, L);
			printf("Purchased: Chick\n\n");
		} else
			printf("Insufficient Funds to Purchase: Chick\n\n");
	} else if(strcmp(input, "2\n") == 0) {
		if(coins >= 25) {
			coins = coins - 25;
			InitializeChicken('H', HHP, "Hen", &C);
			Insert(C, L->size, L);
			printf("Purchased: Hen\n\n");
		} else
			printf("Insufficient Funds to Purchase: Hen\n\n");
	} else if(strcmp(input, "3\n") == 0) {
		if(coins >= 50) {
			coins = coins - 50;
			InitializeChicken('R', RHP, "Rooster", &C);
			Insert(C, L->size, L);
			printf("Purchased: Rooster\n\n");
		} else
			printf("Insufficient Funds to Purchase: Rooster\n\n");
	} else {
		if(strcmp(input, "4\n") != 0 && strcmp(input, "s\n") != 0)
			printf("ERROR: Invalid Input\n\n");
	}

	return coins;
}
