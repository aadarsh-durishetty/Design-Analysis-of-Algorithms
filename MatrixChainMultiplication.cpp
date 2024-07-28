#include <bits/stdc++.h>
using namespace std;

// Global 2D array to store intermediate results
int temp[100][100];

// Function to calculate the minimum number of scalar multiplications
// needed to multiply matrices from index i to j in array p
int MatrixChainMultiply(int* p, int i, int j)
{
    // Base case: If there is only one matrix in the sequence
    if (i == j) 
    {
        return 0;
    }

    // If the result for this subproblem is already calculated, return it
    if (temp[i][j] != -1) 
    {
        return temp[i][j];
    }

    // Initialize the result for this subproblem
    temp[i][j] = INT_MAX;

    // Iterate through all possible split points and find the one
    // that minimizes the total number of scalar multiplications
    for (int k = i; k < j; k++) 
    {
        temp[i][j] = min(
            temp[i][j],
            MatrixChainMultiply(p, i, k) 
            + MatrixChainMultiply(p, k + 1, j)
            + p[i - 1] * p[k] * p[j]
        );
    }

    // Return the minimum number of scalar multiplications for this subproblem
    return temp[i][j];
}

// Function to calculate the minimum number of scalar multiplications
// needed to multiply a sequence of matrices represented by array p
int MatrixChainOrder(int* p, int n)
{
    // Set initial values and call the recursive function
    int i = 1, j = n - 1;
    return MatrixChainMultiply(p, i, j);
}

// Driver Code
int main()
{
    // Example matrix dimensions represented by array 'arr'
    int arr[] = { 1, 2, 3, 4 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // Initialize the 2D array 'temp' with -1 to mark uninitialized entries
    memset(temp, -1, sizeof temp);

    // Display the minimum number of multiplications required
    cout << "Minimum number of multiplications : " << MatrixChainOrder(arr, n);
}
