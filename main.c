#include "Functions.h"

/*
displays main menu, let's the user choose an operation, and
calls the appropriate function.
*/
int main() {
	char input[BUF];

	/*title screen*/
	printf("THIS\n");
	sleep(1);
	printf(" IS\n");
	sleep(1);
	printf("CHICKEN RUN\n\n");

	/*menu screen*/
	printf("OPTIONS\n1. START GAME\n2. INSTRUCTIONS\n3. CREATE\n4. LOAD CUSTOM\n5. EXIT\n>");
	fgets(input, BUF, stdin);


	/*user input, while the input is invalid*/
	while(isValid(input) == 0) {
		printf("ERROR: Invalid Input\n>");
		fgets(input, BUF, stdin);
	}

	while(isValid(input) == 1) {
		if(strcmp(input, "s\n") == 0 || strcmp(input, "S\n") == 0 || strcmp(input, "1\n") == 0 ) {
			printf("STARTING GAME...\n");
			sleep(1);
			PlayGame();
		} else if(strcmp(input, "i\n") == 0 || strcmp(input, "I\n") == 0 || strcmp(input, "2\n") == 0 ) {
			printf("INSTRUCTIONS:\n");
			printf("Your goal is to lead a squad of chickens to the\n");
			printf("end of every level. Angry farmers will attack your\n");
			printf("chickens as they pass. You will purchase chickens in\n");
			printf("the shop, then begin each level. Once the level has\n");
			printf("started, you can no longer take action; make sure\n");
			printf("you're satisfied with your selections! You only\n");
			printf("need one chicken to reach the end of a level to\n");
			printf("succeed. There are three levels to complete.\n");
			printf("You will be rewarded money after each level to\n");
			printf("purchase more chickens. Good luck!\n\n");
		} else if(strcmp(input, "c\n") == 0 || strcmp(input, "C\n") == 0 || strcmp(input, "3\n") == 0 ) {
			printf("Now Entering CREATE LEVEL...\n");
			printf("wasd to move, e to pick up character, r to\n");
			printf("place character, q to quit, then enter level name:\n");
			sleep(3);
			Create();
		}else if(strcmp(input, "l\n") == 0 || strcmp(input, "L\n") == 0 || strcmp(input, "4\n") == 0 ) {
			printf("LOADING CUSTOM LEVEL...\n");
			sleep(1);
			LoadStub();
		}else if(strcmp(input, "q\n") == 0 || strcmp(input, "Q\n") == 0 || strcmp(input, "5\n") == 0 ) {
			printf("EXITING GAME...\n");
			exit(0);
		}

		printf("OPTIONS\n1. START GAME\n2. INSTRUCTIONS\n3. CREATE\n4. LOAD CUSTOM\n5. EXIT\n>");
		fgets(input, BUF, stdin);

	}

	return EXIT_SUCCESS;
}

/*check if the entered value is valid or not.
Return 0 if the input is invalid, 1 if valid.*/
int isValid(char input[]) {
	if(strcmp(input, "s\n") != 0 && strcmp(input, "S\n") != 0 && strcmp(input, "q\n") != 0 && strcmp(input, "Q\n") != 0 && strcmp(input, "1\n") != 0 && strcmp(input, "2\n") != 0 && strcmp(input, "3\n") != 0 && strcmp(input, "i\n") != 0 && strcmp(input, "I\n") != 0 && strcmp(input, "c\n") != 0 && strcmp(input, "C\n") != 0 && strcmp(input, "4\n") != 0 && strcmp(input, "5\n") != 0 && strcmp(input, "l\n") != 0 && strcmp(input, "L\n") != 0 )
		return 0;
	return 1;
}

