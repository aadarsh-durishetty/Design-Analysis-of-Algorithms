#include <bits/stdc++.h>
using namespace std;

// Function to find the length of the Longest Common Subsequence
int longestCommonSubsequence(string& text1, string& text2)
{
    // Get the sizes of the input strings
    int n = text1.size();
    int m = text2.size();

    // Create vectors to store lengths of common subsequences
    vector<int> prev(m + 1, 0), cur(m + 1, 0);

    // Base case initialization: Set all elements of prev and cur to 0
    for (int idx2 = 0; idx2 < m + 1; idx2++)
        cur[idx2] = 0;

    // Dynamic Programming Loop
    for (int idx1 = 1; idx1 < n + 1; idx1++) {
        for (int idx2 = 1; idx2 < m + 1; idx2++) {
            // Compare characters of text1 and text2
            if (text1[idx1 - 1] == text2[idx2 - 1])
                // If characters are equal, update cur[idx2] accordingly
                cur[idx2] = 1 + prev[idx2 - 1];
            else
                // If characters are not equal, update cur[idx2] using the maximum length
                cur[idx2] = max(cur[idx2 - 1], prev[idx2]);
        }
        // Update prev to be equal to cur for the next iteration
        prev = cur;
    }

    // Return the length of the Longest Common Subsequence
    return cur[m];
}

// Main function
int main()
{
    // Input strings
    string S1 = "WXXFAB";
    string S2 = "SYGYAXD";

    // Function call
    cout << "Length of Longest Common Subsequence : " << longestCommonSubsequence(S1, S2);

    return 0;
}
