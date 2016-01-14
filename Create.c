#include "Functions.h"

/*
declares a 2D char array 'map' to hold the level.
Calls functions to let the user build a map and write it to a file.
*/
void Create(void) {
	char map[22][80];

	initscr();
	noecho();

	Pop(map);
	Draw(map);
	BuildMap(map);

	endwin();
	WriteToFile(map);

}

/*
takes in a 2D array of char, populates it with '.'
(i.e. the ground texture of the map.)
*/
void Pop(char map[22][80]) {
	int i;
	int j;

	/*nested for-loops to iterate through every element of
	the array*/
	for(i = 0; i < 22; i++) {
		for(j = 0; j < 80; j++) {
			map[i][j] = '.';
		}
	}
}

/*
takes in a 2D array of char, prints the contents to the screen.
In other words, displays the map.
*/
void Draw(char map[22][80]) {
	int i;
	int j;

	initscr();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);

	for(i = 0; i < 22; i++) {
		for(j = 0; j < 80; j++) {
			mvaddch(i, j, map[i][j]);
		}
	}

	/*printing the legend*/
	mvwprintw(stdscr, 22, 0, "   +         B            Y                 S            o        O ");
	mvwprintw(stdscr, 23, 0, "  Path     Farmer    Rifle Farmer    Shotgun Farmer    Start     End");
	refresh();
}

/*
takes in a 2D array of char, prints it to a .txt file.
*/
void WriteToFile(char map[22][80]) {
	char inp[20];
	char level[25];
	FILE *fp;
	int i;
	int j;

	/*read in desired name for level, concatenate .txt on the end.*/
	fgets(inp, 19, stdin);
	strtok(inp, "\n");
	strncpy(level, inp, 19);
	strcat(level, ".txt");

	fp = fopen(level, "w");

	/*iterate through every element, print it to file.*/
	for(i = 0; i < 22; i++) {
		for(j = 0; j < 80; j++) {
			fputc(map[i][j], fp);
			/*put a newline in the file if j has reached the end of a line.*/
			if(j == 79)
				fputc('\n', fp);
		}
	}

	fclose(fp);
	printf("New Level Created: %s\n", level);
	exit(0);
}

/*
takes in a 2D array of char, allows the user to navigate it with wasd.
*/
void BuildMap (char map[22][80]) {
	char in = 'a';
	char put = 'a';
	int y;
	int x;

	while(in != 'q' && in != 'Q') {
		getyx(stdscr, y, x);
		in = getch();
		/*move cursor according to user input*/
		switch(in) {
			case 'w':
				move(y - 1, x);
				break;
			case 'a':
				move(y, x - 1);
				break;
			case 's':
				move(y + 1, x);
				break;
			case 'd':
				move(y, x + 1);
				break;
			case 'e':
				/*if the user selected 'e', archive the character their cursor is on.*/
				if((char)mvinch(y, x) == '+' || (char)mvinch(y, x) == 'B' || (char)mvinch(y, x) == 'Y' || (char)mvinch(y, x) == 'S' || (char)mvinch(y, x) == 'o' || (char)mvinch(y, x) == 'O')
					put = (char)mvinch(y, x);
				break;
			case 'r':
				/*if the user selected 'r', place the archived character where their cursor is.*/
				if((char)mvinch(y, x) == '.') {
					mvaddch(y, x, put);
					map[y][x] = put;
				}
				move(y, x);
				break;
		}
		refresh();
	}
}
