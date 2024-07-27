#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define V 6 // Number of vertices in the graph

// Function to find if there is a path from source to sink in the residual graph
// Also fills the parent array to store the path
bool findPath(int residualGraph[V][V], int source, int sink, int parent[]) {
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark it as visited
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1; // Parent of source is -1

    // Standard BFS Loop
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Traverse all adjacent vertices of u
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && residualGraph[u][v] > 0) {
                if (v == sink) { // If sink is reached, set its parent and return true
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u; // Set parent of v to u
                visited[v] = true;
            }
        }
    }
    // Sink is not reachable from source
    return false;
}

// Function to find the maximum flow from source to sink in the graph
int fordFulkerson(int graph[V][V], int source, int sink) {
    int u, v;

    // Create a residual graph and copy the capacities from the given graph
    int residualGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            residualGraph[u][v] = graph[u][v];

    int parent[V]; // To store path

    int maxFlow = 0; // Initialize max flow

    // Augment the flow while there is a path from source to sink
    while (findPath(residualGraph, source, sink, parent)) {
        // Find minimum residual capacity of the edges along the path
        int pathFlow = INT_MAX;
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update residual capacities of the edges and reverse edges along the path
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;
    }

    // Return the overall flow
    return maxFlow;
}

// Driver program to test the above functions
int main() {
    // Example graph as shown in the above example
    int graph[V][V] = { { 0, 16, 13, 0, 0, 0 }, 
                        { 0, 0, 10, 12, 0, 0 },
                        { 0, 4, 0, 0, 14, 0 }, 
                        { 0, 0, 9, 0, 0, 20 },
                        { 0, 0, 0, 7, 0, 4 }, 
                        { 0, 0, 0, 0, 0, 0 } };

    // Find the maximum flow from source (0) to sink (5) in the graph
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);

    return 0;
}
