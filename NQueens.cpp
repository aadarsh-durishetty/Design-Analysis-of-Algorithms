#include <bits/stdc++.h>
#define N 8
using namespace std;

// Function to print the solution (placement of queens on the board)
void printSolution(int board[N][N])
{
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            // Print 'Q' if there is a queen at this position, otherwise print '.'
            if(board[row][col])
                cout << " Q ";
            else
                cout << " _ ";
        // Move to the next row
        cout << endl;
    }
}

// Function to check if it's safe to place a queen at position (row, col)
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;

    // Check this row on the left side for any attacking queens
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on the left side for any attacking queens
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on the left side for any attacking queens
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    // If no attacking queens are found, it's safe to place a queen here
    return true;
}

// Recursive function to solve the N Queen problem
bool solveNQueensUtil(int board[N][N], int col)
{
    // Base case: If all queens are placed, return true
    if (col >= N)
        return true;

    // Try placing the queen in each row of this column
    for (int row = 0; row < N; row++) {
        // Check if it's safe to place a queen at this position
        if (isSafe(board, row, col)) {
            // Place the queen at this position
            board[row][col] = 1;

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, col + 1))
                return true;

            // If placing the queen here doesn't lead to a solution, backtrack
            board[row][col] = 0; // Remove the queen (backtrack)
        }
    }

    // If no safe position is found in this column, return false
    return false;
}

// Function to solve the N Queen problem and print one of the solutions
bool solveNQueens()
{
    // Initialize the chessboard with all zeros (no queens placed)
    int board[N][N] = { { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 } };

    // Start solving the N Queen problem from the first column (0th column)
    if (solveNQueensUtil(board, 0) == false) {
        // If no solution exists, print a message and return false
        cout << "Solution does not exist";
        return false;
    }

    // If a solution is found, print the placement of queens on the board
    printSolution(board);
    return true;
}

// Driver program to test above functions
int main()
{
    // Call the function to solve the N Queen problem
    solveNQueens();
    return 0;
}

// This code is contributed by Aditya Kumar (adityakumar129)
