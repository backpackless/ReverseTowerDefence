#include "Functions.h"

/*
takes in the name of a level to load, and the 2D map array.
Loads from the level char by char, placing them in the map
array.
Calls Draw() to display the level.
*/
void Load(char level[20], char map[22][80]) {
	FILE *fp;
	char ch = 'a';
	int i, j;

	fp = fopen(level, "r");
	if(fp == NULL) {
		printf("ERROR: Open file failed\n");
		exit(0);
	}

	/*read from file, place chars into the map array.*/
	for(i = 0; i < 22; i++) {
		for(j = 0; j < 80; j++) {
			ch = fgetc(fp);
			if(ch == '\n')
				ch = fgetc(fp);
			map[i][j] = ch;
		}
	}

	Draw(map);

	fclose(fp);
}

/*
lets the user load a level of their choice, purchase the max number of chickens,
and send them through the level.
*/
void LoadStub(void) {
	char level[20];
	char map[22][80];
	int coins = 10000;
	List L;
	char input[BUF];

	Initialize(&L);
	printf("Enter name of level to load: ");
	fgets(level, 19, stdin);
	strtok(level, "\n");
	strcat(level, ".txt");

	printf("Welcome to Level CUSTOM\n");
		while(strcmp(input, "s\n") != 0 && strcmp(input, "4\n") != 0) {
			printf("SHOP:\n1. Chick(c)   ($10)\n2. Hen(H)     ($25)\n3. Rooster(R) ($50)\n4. Start Level\n\n");
			printf("Available Coins: $%d\n", coins);
			printf("Current Number of Chickens (Max 13): %d\n>", L.size);
			fgets(input, BUF, stdin);
			coins = Shop(input, coins, &L);
		}

	Load(level, map);
	Run(&L, map, -1);
	endwin();
	exit(0);
}
