#ifndef _HEADER_
#define _HEADER_
#define BDAM 1
#define YDAM 2
#define SDAM 3
#define BUF 100

#define CHP 25
#define HHP 35
#define RHP 50

#include "ListInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

int isValid(char input[]);
void PlayGame(void);
void Create(void);

int Shop(char input[], int coins, List *L);
void Load(char level[20], char map[22][80]);
void LoadStub(void);

void Pop(char map[22][80]);
void Draw(char map[22][80]);
void WriteToFile(char map[22][80]);
void BuildMap(char map[22][80]);

int Run(List * L, char map[22][80], int levelCount);

int MoveUnit(int i, List * L, int * cnt, int *direction, int * win, int levelCount);

#endif
