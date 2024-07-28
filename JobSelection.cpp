#include <bits/stdc++.h>
using namespace std;
#define N 4

// Struct to represent a node in the search tree
struct Node
{
    Node* parent; // Parent node of the current node
    int pathCost; // Cost for ancestors nodes including current node
    int cost; // Least promising cost
    int workerID; // Worker ID
    int jobID; // Job ID
    bool assigned[N]; // Boolean array indicating assigned jobs
};

// Function to create a new node in the search tree
Node* createNode(int worker, int job, bool assigned[], Node* parent)
{
    Node* node = new Node;

    // Copy assigned array
    for (int i = 0; i < N; i++)
        node->assigned[i] = assigned[i];

    // Assign worker to job
    node->assigned[job] = true;

    node->parent = parent;
    node->workerID = worker;
    node->jobID = job;

    return node;
}

// Function to calculate the least promising cost after assigning worker x to job y
int calculateCost(int costMatrix[N][N], int worker, int job, bool assigned[])
{
    int cost = 0;

    // Boolean array to track available jobs
    bool available[N] = {true};

    // Iterate through workers starting from the next worker
    for (int i = worker + 1; i < N; i++)
    {
        int minCost = INT_MAX, minIndex = -1;

        // Iterate through jobs
        for (int j = 0; j < N; j++)
        {
            // Check if job is unassigned and available
            if (!assigned[j] && available[j] && costMatrix[i][j] < minCost)
            {
                // Update minimum cost and index
                minIndex = j;
                minCost = costMatrix[i][j];
            }
        }

        // Add minimum cost for next worker
        cost += minCost;

        // Mark job as unavailable
        available[minIndex] = false;
    }

    return cost;
}

// Comparison object to be used to order the heap
struct Compare
{
    bool operator()(const Node* left, const Node* right) const
    {
        return left->cost > right->cost;
    }
};

// Function to print job assignments
void printAssignments(Node *min)
{
    if(min->parent == NULL)
        return;

    // Recursively print assignments
    printAssignments(min->parent);
    cout << "Assign Worker " << char(min->workerID + 'A')
         << " to Job " << min->jobID << endl;
}

// Function to find the minimum cost using Branch and Bound algorithm
int findMinCost(int costMatrix[N][N])
{
    
    // Priority queue to store live nodes of search tree
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Initialize root node with dummy values
    bool assigned[N] = {false};
    Node* root = createNode(-1, -1, assigned, NULL);
    root->pathCost = root->cost = 0;
    root->workerID = -1;

    // Add root node to priority queue
    pq.push(root);

    // Loop until priority queue is not empty
    while (!pq.empty())
    {
        // Get node with least estimated cost
        Node* minNode = pq.top();
        pq.pop();

        // Get next worker
        int worker = minNode->workerID + 1;

        // Check if all workers are assigned a job
        if (worker == N)
        {
            printAssignments(minNode);
            return minNode->cost;
        }

        // Iterate through jobs
        for (int job = 0; job < N; job++)
        {
            // Check if job is unassigned
            if (!minNode->assigned[job])
            {
                // Create a new node
                Node* child = createNode(worker, job, minNode->assigned, minNode);

                // Update path cost and calculate least promising cost
                child->pathCost = minNode->pathCost + costMatrix[worker][job];
                child->cost = child->pathCost + calculateCost(costMatrix, worker, job, child->assigned);

                // Add child node to priority queue
                pq.push(child);
            }
        }
    }
}

// Main function
int main()
{
    // Cost matrix representing the cost of assigning each worker to each job
    int costMatrix[N][N] =
    {
        {6, 1, 8, 2},
        {9, 7, 6, 3},
        {2, 6, 1, 9},
        {3, 4, 5, 2}
    };

    // Find and print optimal cost
    cout << "\n---------Optimal Cost-----------\n" << findMinCost(costMatrix);

    return 0;
}
