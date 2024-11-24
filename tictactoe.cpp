#include <iostream>
#include <algorithm>
#include<limits.h>

using namespace std;

class TicTacToe {
public:
    char board[3][3];
    char player, ai;

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == ' ')
                    return true;
        return false;
    }

    int evaluate() {
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == ai)
                    return +10;
                else if (board[row][0] == player)
                    return -10;
            }
        }
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == ai)
                    return +10;
                else if (board[0][col] == player)
                    return -10;
            }
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == ai)
                return +10;
            else if (board[0][0] == player)
                return -10;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == ai)
                return +10;
            else if (board[0][2] == player)
                return -10;
        }
        return 0;
    }

    int minimax(int depth, bool isMax) {
        int score = evaluate();

        if (score == 10)
            return score;
        if (score == -10)
            return score;
        if (!isMovesLeft())
            return 0;

        if (isMax) {
            int best = INT_MIN;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = ai;
                        best = max(best, minimax(depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        } else {
            int best = INT_MAX;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = player;
                        best = min(best, minimax(depth + 1, !isMax));
                        board[i][j] = ' ';
                    }
                }
            }
            return best;
        }
    }

    void printBoard() {
        cout << "-------------\n";
        for (int i = 0; i < 3; i++) {
            cout << "| ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j] << " | ";
            }
            cout << "\n-------------\n";
        }
    }

    void aiMove() {
        int bestVal = -1000;
        int row = -1, col = -1;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = ai;
                    int moveVal = minimax(0, false);
                    board[i][j] = ' ';
                    if (moveVal > bestVal) {
                        row = i;
                        col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        board[row][col] = ai;
    }

    void playerMove() {
        int pos;
        cout << "Enter your move (1-9): ";
        cin >> pos;
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (board[row][col] == ' ')
            board[row][col] = player;
        else {
            cout << "Cell already occupied! Try again.\n";
            playerMove();
        }
    }

    bool isGameOver() {
        int score = evaluate();
        if (score == 10 || score == -10)
            return true;
        if (!isMovesLeft())
            return true;
        return false;
    }

    TicTacToe() {
        player = 'X';
        ai = 'O';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';
    }

    void playGame() {
        printBoard();
        while (!isGameOver()) {
            playerMove();
            printBoard();
            if (isGameOver())
                break;
            aiMove();
            printBoard();
        }
        int score = evaluate();
        if (score == 10)
            cout << "AI wins!\n";
        else if (score == -10)
            cout << "Player wins!\n";
        else
            cout << "It's a draw!\n";
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
