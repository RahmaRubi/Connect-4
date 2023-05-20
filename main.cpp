#include "main.h"

char board[ROWS][COLS]; // game board
int level = 0; // difficulty
string Name; // player 1 name
string Name2; // player 2 name
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // used to control output like animations and colors
char player = 'X'; // player piece
int padding = 0; // padding for centering
char mode;

//the 1v1 game mode
void Game1v1() {


    srand(time(NULL));

    while (true) {
        int temp;
        // Player's turn
        play();
        // Check for game end
        temp = check();
        // Switch player
        player = (player == 'X') ? 'O' : 'X';
        if (temp)
             if (gameover(temp))
                break;
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

    while (mode != '0' && mode != '1') // checks if user input is correct
    {
        cout << "Illegal input please only choose between 1 or 0: \n";
        cin >> mode;
    }
    if (mode == '0')
    {
        cout << "Player one's Name: "; cin >> Name;
        cout << "Player two's Name: "; cin >> Name2;
        Game1v1(); // player Vs player mode
    }
    else if (mode == '1')
    {
        cout << "Please enter your name: "; cin >> Name;
        anim();
        cout << "choose level [Easy(1), Moderate(2), Hard(3)]: "; cin >> level;
        anim();
        Start(); // Vs ai mode
    }
}
// the main function - starts program flow - always returns 0
int main() {

    Menu();
    anim();
    cout << "Thank you for playing <3\n";
    return 0;
}