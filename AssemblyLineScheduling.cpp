#include <bits/stdc++.h>
using namespace std;

#define NUM_LINE 2
#define NUM_STATION 4

// Utility function to find the minimum of two numbers
int min(int a, int b) 
{
    return a < b ? a : b;
}

// Function to find the minimum time for car assembly
int ALS(int a[][NUM_STATION], int t[][NUM_STATION], int *e, int *x) 
{
    // Arrays to store the minimum time to reach each station on both assembly lines
    int T1[NUM_STATION], T2[NUM_STATION], i;
    
    // Time taken to leave the first station in line 1
    T1[0] = e[0] + a[0][0]; 
    
    // Time taken to leave the first station in line 2
    T2[0] = e[1] + a[1][0];  
    
    // Fill tables T1[] and T2[] using dynamic programming
    for (i = 1; i < NUM_STATION; ++i) 
    { 
        // Calculate the minimum time to reach the current station on line 1
        T1[i] = min(T1[i - 1] + a[0][i], T2[i - 1] + t[1][i] + a[0][i]); 
        
        // Calculate the minimum time to reach the current station on line 2
        T2[i] = min(T2[i - 1] + a[1][i], T1[i - 1] + t[0][i] + a[1][i]); 
    } 
    
    // Consider exit times and return the overall minimum time
    return min(T1[NUM_STATION - 1] + x[0], T2[NUM_STATION - 1] + x[1]); 
}

// Driver code
int main() 
{
    // Input values for assembly times, transfer times, entry times, and exit times
    int a[][NUM_STATION] = {{5, 7, 1, 8}, 
                            {21, 12, 11, 2}};
    int t[][NUM_STATION] = {{1, 5, 2, 9}, 
                            {0, 7, 5, 4}};
    int e[] = {11, 13}, x[] = {17, 8}; 

    // Output the minimum time required for car chassis assembly
    cout << "Minimum time for car assembly: " << ALS(a, t, e, x) << endl;

    return 0; 
}
