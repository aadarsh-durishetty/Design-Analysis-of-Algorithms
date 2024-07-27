#include <bits/stdc++.h> 
using namespace std; 

// Recursive function to solve the 0/1 Knapsack problem with memoization
int KnapSack(int W, int wt[], int val[], int index, int** dp) 
{ 
    // Base case: if no items are left
	if (index < 0) 
		return 0; 
    
    // If the result for the current state is already computed, return it
	if (dp[index][W] != -1) 
		return dp[index][W]; 

    // If the weight of the current item is greater than the remaining capacity
	if (wt[index] > W) { 
        // Exclude the current item and move to the previous item
		dp[index][W] = KnapSack(W, wt, val, index - 1, dp); 
		return dp[index][W]; 
	} 
	else { 
        // Include the current item or exclude it, and choose the option with maximum value
		dp[index][W] = max(val[index] 
						+ KnapSack(W - wt[index], wt, val, 
										index - 1, dp), 
					KnapSack(W, wt, val, index - 1, dp)); 
		return dp[index][W]; 
	} 
} 

// Wrapper function to initialize the memoization table and call the recursive function
int knapSack(int W, int wt[], int val[], int n) 
{ 
    // Initialize the memoization table
	int** dp; 
	dp = new int*[n]; 

	for (int i = 0; i < n; i++) 
		dp[i] = new int[W + 1]; 
    
    // Set all values in the memoization table to -1
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < W + 1; j++) 
			dp[i][j] = -1; 
    
    // Call the recursive function with the initial parameters
	return KnapSack(W, wt, val, n - 1, dp); 
} 

int main() 
{ 
    // Example values for profits, weights, knapsack capacity, and number of items
	int profit[] = { 70, 110, 90 }; 
	int weight[] = { 20, 50, 40 }; 
	int W = 70; 
	int n = sizeof(profit) / sizeof(profit[0]); 
    
    // Display the maximum possible profit
	cout << "The Maximum Possible Profit: " << knapSack(W, weight, profit, n); 
	return 0; 
}
