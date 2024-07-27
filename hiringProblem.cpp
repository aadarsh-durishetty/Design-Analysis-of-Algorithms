#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <cmath>   // For round()

#define EULER_NUMBER 2.71828

using namespace std;

// Function to round a float number to the nearest integer
int roundToNearestInt(float num)
{
    return num < 0 ? static_cast<int>(num - 0.5) : static_cast<int>(num + 0.5);
}

// Function to find the best candidate based on the n/e rule
void findBestCandidate(int candidates[], int numCandidates)
{
    // Calculating sample size for benchmarking
    int sampleSize = roundToNearestInt(numCandidates / EULER_NUMBER);
    cout << "\nSample size is " << sampleSize << endl;

    // Finding the best candidate in the sample size
    int bestIndex = 0;
    for (int i = 1; i < sampleSize; i++)
    {
        if (candidates[i] > candidates[bestIndex])
        {
            bestIndex = i;
        }
    }

    // Finding the first best candidate that is better than the benchmark set
    for (int i = sampleSize; i < numCandidates; i++)
    {
        if (candidates[i] >= candidates[bestIndex])
        {
            bestIndex = i;
            break;
        }
    }

    // Outputting the best candidate found
    if (bestIndex >= sampleSize)
    {
        cout << "\nBest candidate found is " << bestIndex + 1 << " with talent " << candidates[bestIndex] << endl;
    }
    else
    {
        cout << "\nCouldn't find a best candidate\n";
    }
}

int main()
{
    const int numCandidates = 8;
    int talents[numCandidates];

    srand(time(0));

    // Generating random talents for candidates
    for (int i = 0; i < numCandidates; i++)
    {
        talents[i] = 1 + rand() % 8;
    }

    // Displaying the candidate entries and talents
    cout << "Candidate Entry : ";
    for (int i = 0; i < numCandidates; i++)
    {
        cout << i + 1 << " ";
    }
    cout << endl;

    cout << "Talent Entry  :   ";
    for (int i = 0; i < numCandidates; i++)
    {
        cout << talents[i] << " ";
    }

    // Finding and printing the best candidate
    findBestCandidate(talents, numCandidates);

    return 0;
}
