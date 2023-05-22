#include "main.h"


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

// function for hard mode
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