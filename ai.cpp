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
    return col;
}

// moderate function ....to be edited
int getComputerMoveModerate(char board[ROWS][COLS]) {
    // check if the computer can win with its next move
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'o';
                    break;
                }
            }

            // check if the computer wins with this move
            if (checkwin(board, 'o')) {
                // undo the simulated move
                board[row][col] = ' ';
                return col;
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
                    board[row][col] = 'x';
                    break;
                }
            }

            // check if the player wins with this move
            if (checkwin(board, 'x')) {
                // undo the simulated move
                board[row][col] = ' ';

                // check if the computer can block this move
                if (col > 0 && board[ROWS - 1][col - 1] == ' ' && board[0][col - 1] != ' ') {
                    return col - 1;
                }
                if (col < COLS - 1 && board[ROWS - 1][col + 1] == ' ' && board[0][col + 1] != ' ') {
                    return col + 1;
                }

                // if blocking is not possible, proceed with tactical moves
                break;
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
                    board[row][col] = 'o';
                    break;
                }
            }

            // check if the computer can create or block consecutive sequences
            if (checkConsecutive(board, row, col, 'o', 3)) {
                // undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // undo the simulated move
            board[row][col] = ' ';
        }
    }

    // if no tactical move is available, use the easy mode strategy
    return getComputerMoveEasy(board);
}


// hard computer function ....to be edited
int getComputerMoveHard(char board[ROWS][COLS]) {
    // check if the computer can win with its next move
    for (int col = 0; col < COLS; col++) {
        if (board[ROWS - 1][col] == ' ') {
            // simulate making a move for the computer in this column
            int row;
            for (row = 0; row < ROWS; row++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'o';
                    break;
                }
            }

            // check if the computer wins with this move
            if (checkwin(board, 'o')) {
                // undo the simulated move
                board[row][col] = ' ';
                return col;
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
                    board[row][col] = 'x';
                    break;
                }
            }

            // check if the player wins with this move
            if (checkwin(board, 'x')) {
                // undo the simulated move
                board[row][col] = ' ';

                // check if the computer can block this move
                if (col > 0 && board[ROWS - 1][col - 1] == ' ' && board[0][col - 1] != ' ') {
                    return col - 1;
                }
                if (col < COLS - 1 && board[ROWS - 1][col + 1] == ' ' && board[0][col + 1] != ' ') {
                    return col + 1;
                }

                // if blocking is not possible, proceed with tactical moves
                break;
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
                    board[row][col] = 'o';
                    break;
                }
            }

            // check if the computer can create a winning sequence
            if (checkConsecutive(board, row, col, 'o', 3)) {
                // undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // check if the computer needs to block the player's potential winning move
            if (checkConsecutive(board, row, col, 'x', 3)) {
                // undo the simulated move
                board[row][col] = ' ';
                continue;  // try another column
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
                    board[row][col] = 'o';
                    break;
                }
            }

            // check if the computer can create a winning sequence
            if (checkConsecutive(board, row, col, 'o', 4)) {
                // undo the simulated move
                board[row][col] = ' ';
                return col;
            }

            // check if the computer needs to block the player's potential winning move
            if (checkConsecutive(board, row, col, 'x', 4)) {
                // undo the simulated move
                board[row][col] = ' ';
                continue;  // try another column
            }

            // undo the simulated move
            board[row][col] = ' ';
        }
    }

    // if no winning move, blocking move, or tactical move is available
    return getComputerMoveEasy(board);
}
