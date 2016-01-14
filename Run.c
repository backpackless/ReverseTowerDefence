#include "Functions.h"

/*
takes in a list, the map array, and the level counter (current level).
Moves the units through the level.
*/
int Run(List * L, char map[22][80], int levelCount) {
	int i, cnt;
	/*X is set to 79 because the x coordinate of the starting location
	never changes.*/
	int X = 79;
	int Y;
	int check = 1;
	/*direction checks whether the unit should move up or down.*/
	int direction = -1;
	int win = 0;

	cnt = L->size;

	/*find the y coordinate of the starting position.*/
	for(i = 0; i < 22; i++) {
		if(map[i][79] == 'o')
			Y = i;
	}

	/*set the initial x and y of each unit to the
	starting locations.*/
	for(i = 0; i < L->size; i++) {
		L->items[i].y = Y;
		L->items[i].x = X;
	}

	/*check is 1 if there are units remaining, and 0 if all units are killed.*/
	while(check == 1) {
		for(i = 0; i < L->size; i++) {
			check = MoveUnit(i, L, &cnt, &direction, &win, levelCount);
		}
		usleep(100000);
	}

	return win;
}

/*
takes in an int i (current position in list), a list, the count of how many items are in the list(cnt),
an integer to check if the user has won the level (win), and the level counter.
Moves the unit, applies any damage dealt, removes dead units from the list and checks if the
user wins the level.
*/
int MoveUnit(int i, List * L, int * cnt, int * direction, int * win, int levelCount) {
	/*ch holds the farmer avatar value*/
	char ch;
	/*check is set if the unit is travelling vertically
	(code to check for damage is the same travelling up or down, eliminates
	redundant code)*/
	int check = 0;
	mvwprintw(stdscr, 0, 0, "Level %d", levelCount);

	/*Checks which direction to head when travelling vertically, so the unit
	doesn't jump between the path behind it and in front of it. 1 = up,
	0 = down*/
	if(mvinch(L->items[i].y, (L->items[i].x + 1)) != '.' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'B' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'Y' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'S' && mvinch((L->items[i].y - 1), L->items[i].x) == '+')
		L->items[i].direction = 1;
	else if(mvinch(L->items[i].y, (L->items[i].x + 1)) != '.' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'B' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'Y' && mvinch(L->items[i].y, (L->items[i].x + 1)) != 'S' && mvinch((L->items[i].y + 1), L->items[i].x) == '+')
		L->items[i].direction = 0;

	/*check if the unit should move to the left*/
	if(mvinch(L->items[i].y, (L->items[i].x - 1)) == '+') {
		/*move avatar to the left, replace its old spot with a '+',
		alter the unit's coordinates.*/
		mvaddch(L->items[i].y, (L->items[i].x - 1), L->items[i].avatar);
		mvaddch(L->items[i].y, L->items[i].x, '+');
		L->items[i].x = L->items[i].x - 1;

		/*damage calculations*/
		ch = (char)mvinch((L->items[i].y - 1), (L->items[i].x - 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			/*if damage is taken, replace the character, but in red*/
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y - 1), (L->items[i].x));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y - 1), (L->items[i].x + 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y + 1), (L->items[i].x - 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y + 1), (L->items[i].x));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y + 1), (L->items[i].x + 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}
	/*check if unit moves up.*/
	}else if(mvinch((L->items[i].y - 1), L->items[i].x) == '+' && L->items[i].direction == 1) {
		mvaddch((L->items[i].y - 1), L->items[i].x, L->items[i].avatar);
		mvaddch(L->items[i].y, L->items[i].x, '+');
		L->items[i].y = L->items[i].y - 1;
		check = 1;
	
	/*check if unit moves down.*/
	} else if(mvinch((L->items[i].y + 1), L->items[i].x) == '+' && L->items[i].direction == 0) {
		mvaddch((L->items[i].y + 1), L->items[i].x, L->items[i].avatar);
		mvaddch(L->items[i].y, L->items[i].x, '+');
		L->items[i].y = L->items[i].y + 1;
		check = 1;
	/*following code blocks check if the unit has reached the end of the map.
	If so, removes unit from the map (not the list!), sets win condition to 1,
	and subtracts 1 from the count of units on the board.*/
	}else if(mvinch(L->items[i].y, (L->items[i].x - 1)) == 'O') {
		mvaddch(L->items[i].y, L->items[i].x, '+');
		if(*cnt != 0)
			*cnt = *cnt - 1;
		*win = 1;
	
	} else if(mvinch((L->items[i].y - 1), L->items[i].x) == 'O') {
		mvaddch(L->items[i].y, L->items[i].x, '+');
		if(*cnt != 0)
			*cnt = *cnt - 1;
		*win = 1;
	
	} else if(mvinch((L->items[i].y + 1), L->items[i].x) == 'O') {
		mvaddch(L->items[i].y, L->items[i].x, '+');
		if(*cnt != 0)
			*cnt = *cnt - 1;
		*win = 1;
	}

	/*if the unit is travellint vertically, check for damage*/
	if(check == 1) {
		/*damage calculations*/
		ch = (char)mvinch((L->items[i].y - 1), (L->items[i].x - 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y), (L->items[i].x - 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y + 1), (L->items[i].x - 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y - 1), (L->items[i].x + 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y), (L->items[i].x + 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}

		ch = (char)mvinch((L->items[i].y + 1), (L->items[i].x + 1));
		if(ch == 'B') {
			L->items[i].hp = L->items[i].hp - BDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'Y') {
			L->items[i].hp = L->items[i].hp - YDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}else if(ch == 'S') {
			L->items[i].hp = L->items[i].hp - SDAM;
			attron(COLOR_PAIR(1));
			mvaddch(L->items[i].y, L->items[i].x, L->items[i].avatar);
			attroff(COLOR_PAIR(1));
		}
	}

	/*remove the unit from the map and the list if it has no hp left*/
	if(L->items[i].hp <= 0) {
		mvaddch(L->items[i].y, L->items[i].x, '+');
		Remove(i, L);
		*cnt = *cnt - 1;
	}

	refresh();

	if(*cnt == 0)
		return 0;
	return 1;
}
