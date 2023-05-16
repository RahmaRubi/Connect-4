#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <windows.h>
#include <chrono>
#include <thread>


using namespace std;

#define FOREGROUND_WHITE 0x0007
#define FOREGROUND_CYAN 0x0003



// the global variables for the players names, the grid size, level,
int level = 0;
string Name, Name2;
int sequenceLength = 8; // length of the sequence
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int ROWS = 8;
const int COLS = 8;

//...flag to check if the player want to play again
char flag;


// prototypes for the functions for the different game levels
int getComputerMoveEasy(char board[ROWS][COLS]);
int getComputerMoveModerate(char board[ROWS][COLS]);
int getComputerMoveHard(char board[ROWS][COLS]);

// game start for the computer vs human 
void Start();

// menu function prototype
void Menu();

// Function to set text color
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// return the player game based on the level the player choose 
int levelChecker(char board[ROWS][COLS]) {
    int col = 0;
    if (level == 1) {
        col = getComputerMoveEasy(board);
    }

    if (level == 2) {
        col = getComputerMoveModerate(board);
    }


    if (level == 3) {
        col = getComputerMoveHard(board);
    }

    return col;
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


// function that prints the board
void printBoard(char board[ROWS][COLS]) {
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

    int sequenceLength = 8; // length of the sequence
    int padding = 0; // padding for centering

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

// function that checks the winner based on a specific charachter
bool checkWin(char board[ROWS][COLS], char player) {
    // Check rows
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player) {
                return true;
            }
        }
    }

    // Check columns
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == player && board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player) {
                return true;
            }
        }
    }

    // Check diagonal (from bottom left to top right)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
                return true;
            }
        }
    }

    // Check diagonal (from top left to bottom right)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[i][j] == player && board[i - 1][j + 1] == player && board[i - 2][j + 2] == player && board[i - 3][j + 3] == player) {
                return true;
            }
        }
    }

    return false;
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


// function used to allow the computer to make a random move in the simple mode
int getComputerMoveEasy(char board[ROWS][COLS]) {
    // Choose a random column that isn't full
    int col;
    do {
        col = rand() % COLS;
    } while (board[ROWS - 1][col] != ' ');
    return col;
}

// moderate function ....to be edited
int getComputerMoveModerate(char board[ROWS][COLS]) {
    // Check if the computer can win with its next move
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            // Check if the computer wins with this move
            if (checkWin(board, 'O')) {
                // Undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // Check if the player can win with their next move and block it
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the player in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'X';
                    break;
                }
            }

            // Check if the player wins with this move
            if (checkWin(board, 'X')) {
                // Undo the simulated move
                board[row][col] = ' ';

                // Check if the computer can block this move
                if (col > 0 && board[ROWS - 1][col - 1] == ' ' && board[0][col - 1] != ' ') {
                    return col - 1;
                }
                if (col < COLS - 1 && board[ROWS - 1][col + 1] == ' ' && board[0][col + 1] != ' ') {
                    return col + 1;
                }

                // If blocking is not possible, proceed with tactical moves
                break;
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // Play tactically to create or block consecutive sequences
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            // Check if the computer can create or block consecutive sequences
            if (checkConsecutive(board, row, col, 'O', 3)) {
                // Undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // If no tactical move is available, use the easy mode strategy
    return getComputerMoveEasy(board);
}


// hard computer function ....to be edited
int getComputerMoveHard(char board[ROWS][COLS]) {
    // Check if the computer can win with its next move
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            // Check if the computer wins with this move
            if (checkWin(board, 'O')) {
                // Undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // Check if the player can win with their next move and block it
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the player in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'X';
                    break;
                }
            }

            // Check if the player wins with this move
            if (checkWin(board, 'X')) {
                // Undo the simulated move
                board[row][col] = ' ';

                // Check if the computer can block this move
                if (col > 0 && board[ROWS - 1][col - 1] == ' ' && board[0][col - 1] != ' ') {
                    return col - 1;
                }
                if (col < COLS - 1 && board[ROWS - 1][col + 1] == ' ' && board[0][col + 1] != ' ') {
                    return col + 1;
                }

                // If blocking is not possible, proceed with tactical moves
                break;
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // Play tactically to create or block consecutive sequences
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            // Check if the computer can create a winning sequence
            if (checkConsecutive(board, row, col, 'O', 3)) {
                // Undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // Check if the computer needs to block the player's potential winning move
            if (checkConsecutive(board, row, col, 'X', 3)) {
                // Undo the simulated move
                board[row][col] = ' ';
                continue;  // Try another column
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // Play tactically to create or block consecutive sequences
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // Simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'O';
                    break;
                }
            }

            // Check if the computer can create a winning sequence
            if (checkConsecutive(board, row, col, 'O', 4)) {
                // Undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // Check if the computer needs to block the player's potential winning move
            if (checkConsecutive(board, row, col, 'X', 4)) {
                // Undo the simulated move
                board[row][col] = ' ';
                continue;  // Try another column
            }

            // Undo the simulated move
            board[row][col] = ' ';
        }
    }

    // If no winning move, blocking move, or tactical move is available
    return getComputerMoveEasy(board);
}


// the 1v1 game mode
void Game1v1() {
    cout << "Player one's Name: "; cin >> Name;
    cout << "Player two's Name: "; cin >> Name2;

    srand(time(NULL));
    char board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }

    char player = 'X';
    char player2 = 'O';
    while (true) {

        // Player's turn
        printBoard(board);
        cout << Name << ", choose a column: ";
        int col;
        cin >> col;

        if (col < 0 || col - 1 > COLS || board[ROWS - 1][col - 1] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        makeMove(board, col, player);

        if (checkWin(board, player)) {
            cout << "Player " << Name << " wins!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Check for a tie
        bool isTie = true;
        for (int i = 0; i < COLS; i++) {
            if (board[ROWS - 1][i] == ' ') {
                isTie = false;
                break;
            }
        }
        if (isTie) {
            cout << "It's a tie!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';

        // player two's turn
        printBoard(board);
        cout << Name2 << "'s turn..." << endl;
        cin >> col;

        if (col < 0 || col - 1 > COLS || board[ROWS - 1][col - 1] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        makeMove(board, col, player2);

        if (checkWin(board, player2)) {
            cout << Name2 << " wins!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard(board);

}

// menue function
void Menu() {
    int play = 0;
    string gameTitle = R"(

                   ______                                  __     __ __     ______                      
                  / ____/____   ____   ____   ___   _____ / /_   / // /    / ____/____ _ ____ ___   ___ 
                 / /    / __ \ / __ \ / __ \ / _ \ / ___// __/  / // /_   / / __ / __ `// __ `__ \ / _ \
                / /___ / /_/ // / / // / / //  __// /__ / /_   /__  __/  / /_/ // /_/ // / / / / //  __/
                \____/ \____//_/ /_//_/ /_/ \___/ \___/ \__/     /_/     \____/ \__,_//_/ /_/ /_/ \___/ 
                                                                                        
                                         
)";
    int padding = 0; // padding for centering

    // Calculate the necessary padding for centering
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        padding = (consoleWidth - (sequenceLength * 3)) / 2;
    }

    cout << string(padding, ' ') << gameTitle << endl;
    cout << string(padding, ' ') << "please Enter player's Name: "; cin >> Name; cout << endl << endl;

    for (int line = 0; line < 2; line++) {
        // Print three dots in a line
        for (int i = 0; i < 3; i++) {
            std::cout << string(padding, ' ') << ".";
            std::cout.flush(); // Flush the output stream to ensure dots are immediately visible
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause for 0.1 seconds
        }

        std::cout << std::endl;
    }

    cout << string(padding, ' ') << "----------------------------------\n";
    cout << string(padding, ' ') << "welcome," << Name << ". Choose game mode:" << endl;
    cout << string(padding, ' ') << "0.Player Vs Player"<< endl;
    cout << string(padding, ' ') << "1.Player Vs AI\n";
    cout << string(padding, ' '); cin >> play;
    for (int line = 0; line < 2; line++) {
        // Print three dots in a line
        for (int i = 0; i < 3; i++) {
            std::cout << string(padding, ' ') << ".";
            std::cout.flush(); // Flush the output stream to ensure dots are immediately visible
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause for 0.1 seconds
        }

        std::cout << std::endl;
    }

    cout << string(padding, ' ') << "----------------------------------\n";
    if (play == 0){
        for (int line = 0; line < 2; line++) {
            // Print three dots in a line
            for (int i = 0; i < 3; i++) {
                std::cout << string(padding, ' ') << ".";
                std::cout.flush(); // Flush the output stream to ensure dots are immediately visible
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause for 0.1 seconds
            }

            std::cout << std::endl;
        }

        cout << string(padding, ' ') << "----------------------------------\n";
        Game1v1();
    }
        
    else if (play == 1) {
        cout << string(padding, ' ') << "choose level [Easy(1), Moderate(2), Hard(3)]: "; cin >> level;
        for (int line = 0; line < 2; line++) {
            // Print three dots in a line
            for (int i = 0; i < 3; i++) {
                std::cout << string(padding, ' ') << ".";
                std::cout.flush(); // Flush the output stream to ensure dots are immediately visible
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause for 0.1 seconds
            }

            std::cout << std::endl;
        }

        cout << string(padding, ' ') << "----------------------------------\n";
        Start();
    }

    else
        cout << string(padding, ' ') << "Illegal input please only choose between 1 or 0";



}

// function for fully computer played game
void Start() {
    srand(time(NULL));
    char board[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }

    char player = 'X';
    while (true) {
        // Player's turn
        printBoard(board);
        cout << Name << ", choose a column: ";
        int col;
        cin >> col;

        if (col < 0 || col - 1 > COLS || board[ROWS - 1][col - 1] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        makeMove(board, col, player);

        if (checkWin(board, player)) {
            printBoard(board);
            cout << Name << "  wins!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Check for a tie
        bool isTie = true;
        for (int i = 0; i < COLS; i++) {
            if (board[ROWS - 1][i] == ' ') {
                isTie = false;
                break;
            }
        }
        if (isTie) {
            printBoard(board);
            cout << "It's a tie!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';

        // Computer's turn
        printBoard(board);
        cout << "Computer's turn..." << endl;

        col = levelChecker(board);
        makeMove(board, col, player);

        if (checkWin(board, player)) {
            printBoard(board);
            cout << "Computer wins!" << endl;
            cout << "do you want to play again ? (y,n)"; cin >> flag;
            if (flag == 'y' || flag == 'Y')
                Menu();
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard(board);

}

// the main function
int main() {
    Menu();
    return 0;

}
