#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define V 6 // Number of vertices in the graph

// Breadth First Search to find augmenting paths in the residual graph
bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[sink];
}

// Edmonds-Karp algorithm to find maximum flow in a flow network
int edmondsKarp(vector<vector<int>>& capacityGraph, int source, int sink) {
    // Create a residual graph and initialize it with the capacities
    vector<vector<int>> residualGraph = capacityGraph;
    vector<int> parent(V); // To store the augmenting path

    int maxFlow = 0;

    // While there exists an augmenting path in the residual graph
    while (bfs(residualGraph, source, sink, parent)) {
        int pathFlow = INT_MAX;

        // Find the minimum residual capacity of the augmenting path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Update the residual capacities of the edges and reverse edges
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Add the path flow to the total flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    // Example graph represented using an adjacency matrix
    vector<vector<int>> capacityGraph = { { 0, 16, 13, 0, 0, 0 }, 
                        { 0, 0, 10, 12, 0, 0 },
                        { 0, 4, 0, 0, 14, 0 }, 
                        { 0, 0, 9, 0, 0, 20 },
                        { 0, 0, 0, 7, 0, 4 }, 
                        { 0, 0, 0, 0, 0, 0 } };

    int source = 0;
    int sink = 5;
    cout << "The maximum possible flow is: " << edmondsKarp(capacityGraph, source, sink) << endl;
    return 0;
}
