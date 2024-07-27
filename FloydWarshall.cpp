#include <bits/stdc++.h>
using namespace std;

// Number of vertices in the graph
#define NUM_VERTICES 4

/* Define INF as a large enough value.
   This value will be used for vertices not connected to each other */
#define INF 99999

// Function to print the shortest distance matrix
void printShortestDistances(int distance[][NUM_VERTICES]);

// Function to solve the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall(int distance[][NUM_VERTICES])
{
    int i, j, k;

    /* Iterate over all vertices as intermediate points.
       Update shortest distances between all pairs of vertices using the Floyd Warshall algorithm. */
    for (k = 0; k < NUM_VERTICES; k++) {
        // Pick all vertices as source one by one
        for (i = 0; i < NUM_VERTICES; i++) {
            // Pick all vertices as destination for the above picked source
            for (j = 0; j < NUM_VERTICES; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of distance[i][j]
                if (distance[i][j] > (distance[i][k] + distance[k][j]) &&
                    (distance[k][j] != INF && distance[i][k] != INF))
                    distance[i][j] = distance[i][k] + distance[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printShortestDistances(distance);
}

// Utility function to print the shortest distance matrix
void printShortestDistances(int distance[][NUM_VERTICES])
{
    cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (distance[i][j] == INF)
                cout << "INF"
                     << " ";
            else
                cout << distance[i][j] << " ";
        }
        cout << endl;
    }
}

// Driver's code
int main()
{
    /* Let us create the following weighted graph
         10
      (0)------->(3)
       |         /|\
     5 |          |
       |          | 1
      \|/         |
      (1)------->(2)
           3     */
    int weightedGraph[NUM_VERTICES][NUM_VERTICES] = {{0, 5, INF, 10},
                                                     {INF, 0, 3, INF},
                                                     {INF, INF, 0, 1},
                                                     {INF, INF, INF, 0}};

    // Solve the all-pairs shortest path problem using Floyd Warshall algorithm
    floydWarshall(weightedGraph);
    return 0;
}
