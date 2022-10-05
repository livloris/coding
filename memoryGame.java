#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

// You can change the size of the board to 2, 4, or 6
const int BOARD_SIZE = 4; // Must be less than 8 and even

void fill_board(char in_board[][BOARD_SIZE]);
void print_board(char in_board[][BOARD_SIZE]);
void intialize_board(char in_board[][BOARD_SIZE]);
void copy_board(char in_board[][BOARD_SIZE], char out_board[][BOARD_SIZE]);
bool is_winner(char in_board[][BOARD_SIZE]);

int main(){

    char answer;
    int points = 0;
    int card1x, card2x, card1y, card2y;
 
    char cards[BOARD_SIZE][BOARD_SIZE] = {0};
    char board[BOARD_SIZE][BOARD_SIZE];
    char tempBoard[BOARD_SIZE][BOARD_SIZE];

    intialize_board(board);
    fill_board(cards);

    cout << "Welcome to Memory Game!" << endl << endl;
    print_board(board);


    while(true) {
        cout << "Choose an option:" << endl 
            << "(F) Find a match" << endl
            << "(Q) Quit" << endl
            << "Choice: ";
        cin >> answer;
        cout << endl;
        answer = toupper(answer);
        if('F' == answer) {
            while(true) {
                while(true) {
                    cout << "Pick first card (row, column): ";
                    cin >> card1x >> card1y;
                    if(board[card1x][card1y] != '$') {
                        cout << endl <<"Card is already turned over! Try again." << endl << endl;
                        continue;
                    }
                    else {
                        break;
                    }
                }
                while(true) {
                    cout << "Pick second card (row, column): ";
                    cin >> card2x >> card2y;
                    if(board[card2x][card2y] != '$') {
                        cout << endl << "Card is already turned over! Try again." << endl << endl;
                        continue;
                    }
                    else {
                        break;
                    }
                }
                if(card1x == card2x && card1y == card2y) {
                    cout << endl << "You picked the same cards! Pick two different cards and try again." << endl << endl;
                    continue;
                }
                else {
                    break;
                }
            }
            // Check if cards match
            if(cards[card1x][card1y] == cards[card2x][card2y]) {
                cout << endl << "Cards match! You get a point." << endl;
                board[card1x][card1y] = cards[card1x][card1y];
                board[card2x][card2y] = cards[card2x][card2y];
                points++;
                cout << "Your current points: " << points << endl << endl;
                print_board(board);
                // Check if board is complete
                if(is_winner(board) == true) {
                    cout << endl << "Congratulations! You have completed the board." << endl;
                    cout << "Your current points: " << points << endl << endl;
                    break;
                }
            } 
            else {
                cout << endl << "Cards do not match! Try again!" << endl << endl;
                // Copy current board to temp board and turn over cards on temp board, then display temp board
                copy_board(board, tempBoard);
                tempBoard[card1x][card1y] = cards[card1x][card1y];
                tempBoard[card2x][card2y] = cards[card2x][card2y];
                print_board(tempBoard);
            }
        }
        else if('Q' == answer) {
            cout << "Your total points: " << points << endl;
            cout << "Goodbye!";
            break;
        }
    }
    return 0;
}

// Fill provided board array with random letter 'cards'
// - Array must be initialized with 0's
void fill_board(char in_board[][BOARD_SIZE]) {

    int letterCount = (BOARD_SIZE * BOARD_SIZE) / 2;
    char letters[letterCount];
    char temp;
    int count, tempX, tempY;

    // Seed the randomizer
    srand(time(NULL));

    // Generate a list of 8 random letters
    for(int i = 0; i < letterCount; i++) {
        while(true) {
            count =  0;
            // ASCII values: A -> 65 to Z -> 90
            temp = (rand() % 26) + 65;
            for(int j = 0; j < i; j++) {
                if(temp == letters[j]) {
                    count++;
                }
            }
            if(count == 0) {
                letters[i] = temp;
                break;
            }
        }
    }
    cout << endl;

    // Fill board with two of each letter at random coordinates
    for(int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        while(true) {
            count =  0;
            // ASCII values: A -> 65 to Z -> 90
            tempX = (rand() % BOARD_SIZE);
            tempY = (rand() % BOARD_SIZE);
            if(in_board[tempX][tempY] == 0) {
                in_board[tempX][tempY] = letters[i % letterCount];
                break;
            }
        }
    }
    return;
}

void print_board(char in_board[][BOARD_SIZE]) {
    // Can we draw this to the correct length based on BOARD_SIZE?
    string rowBreak = "--";
    for(int i = 0; i < BOARD_SIZE; i++) {
        rowBreak = rowBreak + "----";
    }
    rowBreak = rowBreak + "\n";

    cout << "Here's the board: " << endl << endl;
    
    // Header
    cout << "  ";
    for(int i = 0; i < BOARD_SIZE; i++){
        printf(" %2d ", i);
    }
    cout << endl;
    
    cout << rowBreak;

    for(int i = 0; i < BOARD_SIZE; i++) {
        printf("%-2d", i);
        for(int j = 0; j < BOARD_SIZE; j++){
            printf("| %c ", in_board[i][j]);
        }
        cout << endl;
        cout << rowBreak;
    }
    return;
}

void intialize_board(char in_board[][BOARD_SIZE]) {

   for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            in_board[i][j] = '$';
        }
    }
    return;
}

void copy_board(char in_board[][BOARD_SIZE], char out_board[][BOARD_SIZE]) {

   for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            out_board[i][j] = in_board[i][j];
        }
    }
    return;
}

bool is_winner(char in_board[][BOARD_SIZE]) {

    bool isWinner = true;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            if(in_board[i][j] == '$') {
                isWinner = false;
            }
        }
    }
    return isWinner;

}



