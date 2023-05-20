#include "main.h"



// Function to set text color
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// return the player game based on the level the player choose 
int levelChecker(char board[ROWS][COLS]) 
{
    return (level == 1 ? getComputerMoveEasy(board) : 0);//level == 2 ? getComputerMoveModerate(board) : getComputerMoveHard(board));
}

void anim()
{
    system("cls");
    for (int line = 0; line < 2; line++) {
        // Print three dots in a line
        for (int i = 0; i < 3; i++) {
            cout << string(padding, ' ') << ".";
            cout.flush(); // Flush the output stream to ensure dots are immediately visible
            this_thread::sleep_for(chrono::milliseconds(100)); // Pause for 0.1 seconds
        }

       cout <<endl;
    }

    cout << string(padding, ' ') << "----------------------------------\n";
}


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

bool istie()
{
    int x = 0;
    for (int i = 0; i < COLS; i++)
        if (board[ROWS - 1][i] == ' ')
            x++;
    return (x == 0);
}


void ai()
{
    printBoard(board);
    cout << "Computer's turn..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    int col = levelChecker(board);
    makeMove(board, col, 'O');
}
/**
* 
* check - checks for game end
* Return: 0 if game continues - 1 if player 1 won - 2 if player 2 won - 3 if tie
* 
*/


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

bool gameover(int x)
{
    char flag;
    printBoard(board);
    switch (x)
    {
    case 1:
        cout << Name << " wins!";
        break;
    case 2:
        cout << Name2 << " wins!";
        break;
    case 3:
        cout << "It's a tie!";
        break;
    }
    this_thread::sleep_for(chrono::seconds(2));
    anim();
    cout << "do you want to play again ? (y/N) "; cin >> flag;
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
       FOREGROUND_RED | FOREGROUND_BLUE // magenta-like color
    }; // array of color attributes
    int numColors = sizeof(colors) / sizeof(colors[0]); // calculate the number of colors




    // Calculate the necessary padding for centering
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        padding = (consoleWidth - (sequenceLength * 3)) / 2;
    }

    // Print top padding
    cout << string(padding, ' ') << endl;

    // Print column numbers with padding
    cout << string(padding, ' ');
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
        cout << string(padding, ' ') << "|";

        for (int j = 0; j < COLS; j++) {
            // Set text color based on character
            if (board[i][j] == 'X') {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // set text color to green
            }
            else if (board[i][j] == 'O') {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE); // set text color to magenta-like color
            }
            else if (board[i][j] == ' ' || board[i][j] == '_') {
                SetConsoleTextAttribute(hConsole, FOREGROUND_CYAN); // set text color to cyan
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); // set text color to white (default)
            }

            cout << board[i][j] << "_|";
        }

        // Reset text color to default
        SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);

        cout << endl;
    }

    // Print bottom padding
    cout << string(padding, ' ') << endl;

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
