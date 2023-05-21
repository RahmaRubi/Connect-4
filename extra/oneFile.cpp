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


#include "main.h"



// Function to set text color
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// return the ai input based on the level the player choose
int levelChecker(char board[ROWS][COLS])
{
    return (level == "1" ? getComputerMoveEasy(board) : getComputerMoveModerate(board));
}

// draws animations before displaying text
void anim()
{
    clear;
    for (int line = 0; line < 2; line++) {
        // Print three dots in a line
        for (int i = 0; i < 3; i++) {
            cout << pad(' ') << ".";
            cout.flush(); // Flush the output stream to ensure dots are immediately visible
            this_thread::sleep_for(chrono::milliseconds(100)); // Pause for 0.1 seconds
        }

       cout <<endl;
    }

    cout << pad(' ') << "----------------------------------\n";
}

// function that handles player move
void play()
{
    printBoard(board);
    cout << (player == 'X'? Name:Name2) << ", choose a column: ";
    string col_temp;
    cin >> col_temp;

    while (col_temp.size()!=1||col_temp[0] -'0'< 1 || col_temp[0]-'0' > COLS || board[ROWS - 1][col_temp[0]-'0' - 1] != ' ') {
       printBoard(board);
        cout << "Invalid move! Try again." << endl;
        cin >> col_temp;
    }
	int col=col_temp[0]-'0';
   makeMove(board, col, player);
}
// function that checks for tie
bool istie()
{
	for (int i = 0; i < COLS; i++)
	{
		if (board[ROWS - 1][i] == ' ')
			return false;
	}
	return true;
}

// function that handles ai moves
void ai()
{
    printBoard(board);
    cout << "Computer's turn..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    int col = levelChecker(board);
    makeMove(board, col, 'O');
}
// function that checks for end of game - Returns 0 if none - 1 if player 1 won - 2 if player 2 won - 3 if tie
int check() {
    if (istie())
        return 3;

    // Check rows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                return (player == 'O'? 2 : 1);
            }
        }
    }

    // Check columns
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                return (player == 'O' ? 2 : 1);
            }
        }
    }

    // Check diagonal (from bottom left to top right)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return (player == 'O' ? 2 : 1);
            }
        }
    }

    // Check diagonal (from top left to bottom right)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return (player == 'O' ? 2 : 1);
            }
        }
    }

    return 0;
}

// function that handels end of game - Returns 1 if player doesn't want to play again to end program flow
bool gameover(int x)
{
    char flag;
    printBoard(board);
    switch (x)
    {
    case 1:
        cout << (mode == "0" ? Name + " wins!" : "You win!");
        break;
    case 2:
        cout << (mode == "0" ? Name2 + " wins!" : "You lose!");
        break;
    case 3:
        cout << "It's a tie!";
        break;
    }
    this_thread::sleep_for(chrono::seconds(3));
    anim();
    do
    {
        cout << "do you want to play again ? (Y/n) "; flag = _getch();
        cout << '\r';
    } while ('y' != tolower(flag) && 'n' != tolower(flag));
    if (flag == 'y' || flag == 'Y')
        Menu();
    return 1;
}

// function that prints the board
void printBoard(char board[ROWS][COLS]) {
    clear;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // get console handle

    int colors[] = {
       FOREGROUND_RED,
       FOREGROUND_GREEN | FOREGROUND_RED,
       FOREGROUND_BLUE | FOREGROUND_RED,
       FOREGROUND_GREEN | FOREGROUND_BLUE,
       FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
       FOREGROUND_INTENSITY | FOREGROUND_RED,
       FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED,
       FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_RED,
       FOREGROUND_RED | FOREGROUND_BLUE
    }; // array of color attributes
    int numColors = 9; // the number of colors

    // Print top padding
    cout << pad(' ') << endl;

    // Print column numbers with padding
    cout << pad(' ');
    cout << "  ";
    for (int i = 0; i < sequenceLength; i++) {
        // Assign colors based on the pattern
        int colorIndex = i % numColors;
        int nextColorIndex = (i + 1) % numColors;

        // Set text color for the current number
        SetConsoleTextAttribute(hConsole, colors[colorIndex]);

        // Print the number with spacing
        cout << i + 1 << "  ";

        // Set text color for the next number
        SetConsoleTextAttribute(hConsole, colors[nextColorIndex]);
    }
    cout << endl;

    for (int i = ROWS - 1; i >= 0; i--) {
        // Print row separator
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        cout << pad(' ') << "|";

        for (int j = 0; j < COLS; j++) {
            // Set text color based on character
            if (board[i][j] == 'X')
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // set text color to green
            else if (board[i][j] == 'O')
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE); // set text color to magenta-like color

            cout << board[i][j];
            SetConsoleTextAttribute(hConsole, FOREGROUND_CYAN);// set text color to cyan
            cout << "_|";
        }
        // Reset text color to default
        SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
        cout << endl;
    }
    // Print bottom padding
    cout << pad(' ') << endl;
}


// function that allows the player to make a move
void makeMove(char board[ROWS][COLS], int col, char player) {
    for (int i = 0; i < ROWS; i++) {
        if (board[i][col - 1] == ' ') {
            board[i][col - 1] = player;
            return;
        }
    }
}


// function to check if there are consecutive pieces after each other
bool checkConsecutive(char board[ROWS][COLS], int row, int col, char player, int consecutiveCount) {
    // Check row
    int count = 0;
    for (int j = col - consecutiveCount + 1; j <= col + consecutiveCount - 1; j++) {
        if (j >= 0 && j + consecutiveCount <= COLS && board[row][j] == player) {
            count++;
            if (count == consecutiveCount) {
                return true;
            }
        }
        else {
            count = 0;
        }
    }

    // Check column
    count = 0;
    for (int i = row - consecutiveCount + 1; i <= row + consecutiveCount - 1; i++) {
        if (i >= 0 && i + consecutiveCount <= ROWS && board[i][col] == player) {
            count++;
            if (count == consecutiveCount) {
                return true;
            }
        }
        else {
            count = 0;
        }
    }

    // Check diagonal (top left to bottom right)
    count = 0;
    int i = row - consecutiveCount + 1;
    int j = col - consecutiveCount + 1;
    while (i <= row + consecutiveCount - 1 && j <= col + consecutiveCount - 1) {
        if (i >= 0 && i + consecutiveCount <= ROWS && j >= 0 && j + consecutiveCount <= COLS && board[i][j] == player) {
            count++;
            if (count == consecutiveCount) {
                return true;
            }
        }
        else {
            count = 0;
        }
        i++;
        j++;
    }

    // Check diagonal (top right to bottom left)
    count = 0;
    i = row - consecutiveCount + 1;
    j = col + consecutiveCount - 1;
    while (i <= row + consecutiveCount - 1 && j >= col - consecutiveCount + 1) {
        if (i >= 0 && i + consecutiveCount <= ROWS && j >= 0 && j + consecutiveCount <= COLS && board[i][j] == player) {
            count++;
            if (count == consecutiveCount) {
                return true;
            }
        }
        else {
            count = 0;
        }
        i++;
        j--;
    }

    return false;
}

// function used to allow the computer to make a random move in the simple mode
int getComputerMoveEasy(char board[ROWS][COLS]) {
    // Choose a random column that isn't full
    int col;
    do {
        col = rand() % COLS;
    } while (board[ROWS - 1][col] != ' ');
    return col+1;
}

// function for moderate and hard modes
int getComputerMoveModerate(char board[ROWS][COLS]) {
    // check if the computer can win with its next move
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }
        //    printBoard(board);
        //    system("pause");
            // check if the computer wins with this move
            player = 'O';
            if (check() == 2) {
                // undo the simulated move
                board[row][col] = ' ';
                return col + 1;
            }

            // undo the simulated move
            board[row][col] = ' ';
        }
    }

    // check if the player can win with their next move and block it
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // simulate making a move for the player in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'X';
                    break;
                }
            }
            //printBoard(board);
            //system("pause");
            // check if the player wins with this move
            player = 'X';
            if (check() == 1) {
                // undo the simulated move
                board[row][col] = ' ';

                return col + 1;
            }

            // undo the simulated move
            board[row][col] = ' ';
        }
    }

    // play tactically to create or block consecutive sequences
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }
            if (level == "3")
         {
            // play tactically to create or block consecutive sequences
            for (int col = 0; col < COLS; col++) {
                if (board[ROWS - 1][col] == ' ') {
                    // simulate making a move for the computer in this column
                    int row;
                    for (row = 0; row < ROWS; row++) {
                        if (board[row][col] == ' ') {
                            board[row][col] = 'O';
                            break;
                        }
                    }

                    // check if the computer can create a winning sequence
                    if (checkConsecutive(board, row, col, 'O', 2)) {
                        // undo the simulated move
                        board[row][col] = ' ';
                        return col+1;
                    }
                    // undo the simulated move
                    board[row][col] = ' ';
                }
            }
          }
            // check if the computer can create or block consecutive sequences
            if (checkConsecutive(board, row, col, 'O', 2)) {
                // undo the simulated move
                board[row][col] = ' ';
                return col + 1;
            }

            // undo the simulated move
            board[row][col] = ' ';
        }
    }


    // if no tactical move is available, use the easy mode strategy
    return getComputerMoveEasy(board);
}

char board[ROWS][COLS]; // game board

string Name; // player 1 name
string Name2; // player 2 name
string level; // difficulty
string mode; // game mode
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // used to control output like animations and colors
char player = 'X'; // player piece
int padding = 0; // padding for centering


//the 1v1 game mode
void Game1v1() {


    while (true) {
        int temp;
        // Player's turn
        play();
        // Check for game end
        temp = check();
        if (temp)
             if (gameover(temp))
                break;
        // Switch player
        player = (player == 'X') ? 'O' : 'X';
        // player two's turn
        play();
        // Check again for game end
        temp = check();
        if (temp)
            if (gameover(temp))
                break;
        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard(board);

}

// function for fully computer played game
void Start() {
    srand(time(NULL));
    int temp = 0;
    while (true) {
        // Player's turn
        player = 'X';
        play();
        // Check for game end
        temp = check();
        if (temp)
            if (gameover(temp))
                break;

        // Computer's turn
        ai();
        // Check again for game end
        player = 'O';
        temp = check();
        if (temp )
            if (gameover(temp))
                break;
    }
}

// menu function - takes mandatory input from user like game mode and their name
void Menu() {
    clear; // clears output to keep stdout clean

    fill(&board[0][0], &board[0][0] + sizeof(board), ' '); // initializes array
    string gameTitle = R"(

                   ______                                  __     __ __     ______
                  / ____/____   ____   ____   ___   _____ / /_   / // /    / ____/____ _ ____ ___   ___
                 / /    / __ \ / __ \ / __ \ / _ \ / ___// __/  / // /_   / / __ / __ `// __ `__ \ / _ \
                / /___ / /_/ // / / // / / //  __// /__ / /_   /__  __/  / /_/ // /_/ // / / / / //  __/
                \____/ \____//_/ /_//_/ /_/ \___/ \___/ \__/     /_/     \____/ \__,_//_/ /_/ /_/ \___/


)";

    // Calculate the necessary padding for centering
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        padding = (consoleWidth - (sequenceLength * 3)) / 2;
    }

    cout << pad(' ') << gameTitle << endl;
    cout << pad(' ') << "Press any key to start"; _getch(); cout << endl << endl;
    anim();
    cout << "welcome, player! please Choose game mode:" << endl;
    cout << "0.Player Vs Player" << endl;
    cout << "1.Player Vs AI\n";
    cin >> mode;
    anim();

    while (mode != "0" && mode != "1") // checks if user input is correct
    {
        cout << "Illegal input please only choose between 1 or 0: ";
        cin >> mode;
        anim();
    }
    if (mode == "0")
    {
        cout << "Player one's Name: "; cin >> Name;
        cout << "Player two's Name: "; cin >> Name2;
        Game1v1(); // player Vs player mode
    }
    else if (mode == "1")
    {
        cout << "Please enter your name: "; cin >> Name;
        anim();
        do {
            cout << "choose level [Easy(1), Moderate(2), Hard(3)]: "; cin >> level;
            anim();
        } while (level != "1" && level != "2" && level != "3");
        Start(); // Vs ai mode
    }
}
// the main function - starts program flow - always returns 0
int main() {

    Menu();
    anim();
    cout << "Thank you for playing <3\n";
    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}
