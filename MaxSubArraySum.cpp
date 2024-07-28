#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum sum of a subarray
int findMaxSubarraySum(int arr[], int size) {
    // Initialize variables to track maximum sum
    int maxSoFar = INT_MIN; // Initialize maxSoFar to the smallest possible integer value
    int maxEndingHere = 0; // Initialize maxEndingHere to 0

    // Loop through the array to find the maximum sum of a subarray
    for (int i = 0; i < size; i++) {
        // Update maxEndingHere by adding the current element of the array
        maxEndingHere = maxEndingHere + arr[i];
        
        // If maxEndingHere becomes greater than maxSoFar, update maxSoFar
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
        
        // If maxEndingHere becomes negative, reset it to 0
        if (maxEndingHere < 0)
            maxEndingHere = 0;
    }
    
    // Return the maximum sum of a subarray
    return maxSoFar;
}

// Driver Code
int main() {
    int arr[] = { -4, -1, 7, 1, -2, 2, 8, -3 };
    int size = sizeof(arr) / sizeof(arr[0]); // Calculate the size of the array

    // Call the function to find the maximum sum of a subarray
    int maxSum = findMaxSubarraySum(arr, size);
    
    // Output the result
    cout << "Maximum subarray sum is " << maxSum;

    return 0;
}
