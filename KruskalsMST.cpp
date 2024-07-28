#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

class Graph {
    int V; // Number of vertices
    vector<Edge> edges; // Vector to store edges

public:
    Graph(int V) : V(V) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    // Function to find the parent of a node
    int find(vector<Subset>& subsets, int i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    // Function to perform union of two subsets
    void Union(vector<Subset>& subsets, int x, int y) {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

    // Function to find MST using Kruskal's algorithm
    void kruskalMST() {
        vector<Edge> result; // Stores the resultant MST
        int e = 0; // An index variable, used for result[]
        int i = 0; // An index variable, used for sorted edges

        // Sort all the edges in non-decreasing order of their weight
        sort(edges.begin(), edges.end(), [](Edge const& a, Edge const& b) {
            return a.weight < b.weight;
        });

        // Allocate memory for creating V subsets
        vector<Subset> subsets(V);
        for (int v = 0; v < V; ++v) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }

        // Number of edges to be taken is equal to V-1
        while (e < V - 1 && i < edges.size()) {
            // Pick the smallest edge
            Edge next_edge = edges[i++];
            int x = find(subsets, next_edge.src);
            int y = find(subsets, next_edge.dest);

            // If including this edge does not cause cycle, include it in the result and increment the index
            if (x != y) {
                result.push_back(next_edge);
                Union(subsets, x, y);
                ++e;
            }
        }

        // Print the result
        cout << "Edge \tWeight\n";
        int minCost = 0;
        for (i = 0; i < e; ++i) {
            cout << result[i].src << " - " << result[i].dest << " \t" << result[i].weight << endl;
            minCost += result[i].weight;
        }
        cout << "Minimum Spanning Tree Cost: " << minCost << endl;
    }
};

int main() {
    int V = 5; // Number of vertices in the graph
    Graph g(V);

    // Sample graph represented using edges
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    // Function call to find MST
    g.kruskalMST();

    return 0;
}
