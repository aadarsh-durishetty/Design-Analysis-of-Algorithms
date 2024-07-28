#include <bits/stdc++.h>
using namespace std;

// d is the number of characters in the input alphabet
#define ALPHABET_SIZE 256

/* searchPatternInText function searches for occurrences of a pattern
   within a given text using the Rabin-Karp algorithm.
   Parameters:
   - pattern: the pattern to search for
   - text: the text to search within
   - prime: a prime number used for hashing
*/
void searchPatternInText(char pattern[], char text[], int prime)
{
	int patternLength = strlen(pattern);
	int textLength = strlen(text);
	int i, j;
	int patternHash = 0; // hash value for pattern
	int textHash = 0;    // hash value for text
	int hashMultiplier = 1;

	// Calculate the value of hashMultiplier: (ALPHABET_SIZE ^ (patternLength - 1)) % prime
	for (i = 0; i < patternLength - 1; i++)
		hashMultiplier = (hashMultiplier * ALPHABET_SIZE) % prime;

	// Calculate the hash value of pattern and the first window of text
	for (i = 0; i < patternLength; i++) {
		patternHash = (ALPHABET_SIZE * patternHash + pattern[i]) % prime;
		textHash = (ALPHABET_SIZE * textHash + text[i]) % prime;
	}

	// Slide the pattern over text one by one
	for (i = 0; i <= textLength - patternLength; i++) {

		// Check if the hash values of the current window of text
		// and pattern match. If they match, compare characters one by one.
		if (patternHash == textHash) {
			/* Check for characters one by one */
			for (j = 0; j < patternLength; j++) {
				if (text[i + j] != pattern[j]) {
					break;
				}
			}

			// If patternHash == textHash and pattern[0...patternLength-1] = text[i, i+1, ...i+patternLength-1]
			if (j == patternLength)
				cout << "Pattern found at index " << i << endl;
		}

		// Calculate hash value for the next window of text:
		// Remove leading character, add trailing character
		if (i < textLength - patternLength) {
			textHash = (ALPHABET_SIZE * (textHash - text[i] * hashMultiplier) + text[i + patternLength]) % prime;

			// We might get a negative value of textHash, so convert it to positive
			if (textHash < 0)
				textHash = (textHash + prime);
		}
	}
}

/* main function */
int main()
{
	char text[] = "CODING IS FUN WHEN YOU ARE CODING";
	char pattern[] = "CODING";

	// Choose a prime number to avoid overflowing of values in hashing,
	// but it should be as large as possible to reduce the chance of collisions
	int prime = INT_MAX;

	// Call the searchPatternInText function
	searchPatternInText(pattern, text, prime);
	return 0;
}
