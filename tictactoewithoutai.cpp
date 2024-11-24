#include <iostream>

using namespace std;

const char PLAYER = 'X';
const char COMPUTER = 'O';
const char EMPTY = ' ';


void printBoard(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}


bool checkWinningCondition(char board[3][3], char player) {
    
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}


bool isGameBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}


bool makeMovePlayer(char board[3][3], int pos, char player) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;
    if (pos >= 1 && pos <= 9 && board[row][col] == EMPTY) {
        board[row][col] = player;
        return true;
    }
    return false;
}


void computerMove(char board[3][3]) {
    for (int pos = 1; pos <= 9; ++pos) {
        if (makeMovePlayer(board, pos, COMPUTER)) {
            break;
        }
    }
}

int main() {
    char board[3][3] = {{EMPTY, EMPTY, EMPTY},
                        {EMPTY, EMPTY, EMPTY},
                        {EMPTY, EMPTY, EMPTY}};
    
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    printBoard(board);

    while (true) {
        int pos;
        cout << "Enter your move (position 1-9): ";
        cin >> pos;

        if (!makeMovePlayer(board, pos, PLAYER)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        
        printBoard(board);

        if (checkWinningCondition(board, PLAYER)) {
            cout << "Congratulations! You win!" << endl;
            break;
        }

        if (isGameBoardFull(board)) {
            cout << "The game is a draw!" << endl;
            break;
        }

        computerMove(board);
        cout << "Computer's move:" << endl;
        printBoard(board);

        if (checkWinningCondition(board, COMPUTER)) {
            cout << "Computer wins! Better luck next time." << endl;
            break;
        }

        if (isGameBoardFull(board)) {
            cout << "The game is a draw!" << endl;
            break;
        }
    }

    return 0;
}





