#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>
#include <conio.h>
#define FOREGROUND_WHITE 0x0007
#define FOREGROUND_CYAN 0x0003
#define ROWS 8   // rows in board
#define COLS 8   // columns in board
#define sequenceLength 8
#define pad(s) string(padding, s) 
#define clear system("cls")
using namespace std;

// the global variables for the players names, the grid size, level,

extern int padding;
extern char board[ROWS][COLS];
extern char player;
extern string mode;
extern string Name;
extern string Name2;
extern string level;

// prototypes for the functions for the different game levels
int levelChecker(char board[ROWS][COLS]);
int getComputerMoveEasy(char board[ROWS][COLS]);
int getComputerMoveModerate(char board[ROWS][COLS]);
bool checkConsecutive(char board[ROWS][COLS], int row, int col, char player, int consecutiveCount);


// prototypes for the functions used in displaying to the user
void setColor(int color);
void printBoard(char board[ROWS][COLS]);
void anim();

// prototypes for the functions used during gameplay
void makeMove(char board[ROWS][COLS], int col, char player);
void play();
bool istie();
void ai();
bool gameover(int x);

// game start for player Vs player
void Game1v1();

// function that checks the winner based on a specific character
int check();

// game start for the computer vs human 
void Start();

// menu function prototype
void Menu();


#endif