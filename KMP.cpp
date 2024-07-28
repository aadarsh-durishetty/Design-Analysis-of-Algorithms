#include <bits/stdc++.h>

// Function to compute the Longest Prefix Suffix (lps) array for the given pattern
// Parameters:
//   pattern: The pattern string
//   pattern_length: The length of the pattern string
//   lps_array: Array to store the computed lps values
void computeLPSArray(char* pattern, int pattern_length, int* lps_array)
{
    // Length of the previous longest prefix suffix
    int previous_longest_suffix_length = 0;

    lps_array[0] = 0; // lps[0] is always 0

    // Calculate lps[i] for i = 1 to pattern_length - 1
    int i = 1;
    while (i < pattern_length) {
        if (pattern[i] == pattern[previous_longest_suffix_length]) {
            previous_longest_suffix_length++;
            lps_array[i] = previous_longest_suffix_length;
            i++;
        }
        else {
            // If there is a mismatch and previous_longest_suffix_length is not 0,
            // update previous_longest_suffix_length using lps[previous_longest_suffix_length - 1]
            if (previous_longest_suffix_length != 0) {
                previous_longest_suffix_length = lps_array[previous_longest_suffix_length - 1];
            }
            else {
                // If previous_longest_suffix_length is 0, set lps[i] to 0 and move to the next character
                lps_array[i] = 0;
                i++;
            }
        }
    }
}

// Function to perform pattern searching using Knuth-Morris-Pratt (KMP) algorithm
// Parameters:
//   pattern: The pattern string to search for
//   text: The text string in which to search for the pattern
void KMPSearch(char* pattern, char* text)
{
    int pattern_length = strlen(pattern);
    int text_length = strlen(text);

    // Create lps_array that will hold the Longest Prefix Suffix (lps) values for pattern
    int lps_array[pattern_length];

    // Preprocess the pattern (calculate lps_array)
    computeLPSArray(pattern, pattern_length, lps_array);

    int text_index = 0; // Index for text
    int pattern_index = 0; // Index for pattern

    // Iterate through the text
    while ((text_length - text_index) >= (pattern_length - pattern_index)) {
        if (pattern[pattern_index] == text[text_index]) {
            pattern_index++;
            text_index++;
        }

        // If the entire pattern is found in the text
        if (pattern_index == pattern_length) {
            printf("Pattern found at index %d ", text_index - pattern_index);
            pattern_index = lps_array[pattern_index - 1];
        }

        // If there is a mismatch after some matches
        else if (text_index < text_length && pattern[pattern_index] != text[text_index]) {
            // Do not match lps_array[0..lps_array[pattern_index - 1]] characters,
            // they will match anyway
            if (pattern_index != 0)
                pattern_index = lps_array[pattern_index - 1];
            else
                text_index = text_index + 1;
        }
    }
}

// Driver code
int main()
{
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    KMPSearch(pattern, text);
    return 0;
}
