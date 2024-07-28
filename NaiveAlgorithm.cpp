#include <bits/stdc++.h>
using namespace std;

// Function to search for a pattern within a text using Naive Pattern Searching algorithm
void naivePatternSearch(string& pattern, string text)
{
    int patternLength = pattern.size(); // Length of the pattern
    int textLength = text.size(); // Length of the text

    /* A loop to slide the pattern one by one over the text */
    for (int i = 0; i <= textLength - patternLength; i++) {
        int j;

        /* Check for pattern match at current index i */
        for (j = 0; j < patternLength; j++)
            if (text[i + j] != pattern[j]) // If characters don't match, break
                break;

        // If the entire pattern matches the substring starting at index i
        if (j == patternLength) 
            cout << "Pattern found at index " << i << endl; // Print the index
    }
}

// Driver's code
int main()
{
    string text = "AABAACAADAABAAABAA";
    string pattern = "AABA";

    // Call the function to search for pattern in text
    naivePatternSearch(pattern, text);
    return 0;
}
