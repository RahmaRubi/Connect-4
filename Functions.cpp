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
    return (level == 1 ? getComputerMoveEasy(board) : getComputerMoveModerate(board));
}

// draws animations before displaying text
void anim()
{
    system("cls");
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
    int col;
    cin >> col;

    while (col < 1 || col > COLS || board[ROWS - 1][col - 1] != ' ') {
        printBoard(board);
        cout << "Invalid move! Try again." << endl;
        cin >> col;
    }

    makeMove(board, col, player);
}
// function that checks for tie
bool istie()
{
    int x = 0;
    for (int i = 0; i < COLS; i++)
        if (board[ROWS - 1][i] == ' ')
            x++;
    return (x == 0);
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
        cout << (mode == '0' ? Name + " wins!" : "You win!");
        break;
    case 2:
        cout << (mode == '0' ? Name2 + " wins!" : "You lose!");
        break;
    case 3:
        cout << "It's a tie!";
        break;
    }
    this_thread::sleep_for(chrono::seconds(3));
    anim();
    do
    {
        cout << "do you want to play again ? (y/N) "; flag = _getch();
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
