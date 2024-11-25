#include <iostream>
using namespace std;

// Function to print the solution (the chessboard with queens)
void printSolution(int board[][100], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place a queen at board[row][col]
bool isSafe(int board[][100], int row, int col, int N) {
    // Check this row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

// A utility function to solve N Queens problem using backtracking
bool solveNQUtil(int board[][100], int col, int N) {
    // Base case: If all queens are placed, return true
    if (col >= N) {
        return true;
    }

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            // Place this queen on board[i][col]
            board[i][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQUtil(board, col + 1, N)) {
                return true;
            }

            // If placing the queen in board[i][col] doesn't lead to a solution, backtrack
            board[i][col] = 0;  // Remove the queen (backtrack)
        }
    }

    // If the queen cannot be placed in any row in this column, return false
    return false;
}

// Function to solve the N Queens problem
bool solveNQ(int N) {
    int board[100][100] = {0}; // Initialize the board to 0

    // Try to solve the problem
    if (!solveNQUtil(board, 0, N)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    // Print the solution
    printSolution(board, N);
    return true;
}

// Main function
int main() {
    int N;
    cout << "Enter the size of the chessboard (N): ";
    cin >> N;

    // Ensure N is a positive integer
    if (N <= 0) {
        cout << "Please enter a valid size for N (greater than 0)." << endl;
        return 1;
    }

    // Solve the N-Queens problem for the given N
    solveNQ(N);
    return 0;
}
