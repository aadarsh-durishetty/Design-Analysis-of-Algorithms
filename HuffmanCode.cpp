#include <iostream>
#include <queue>
using namespace std;
#define MAX_SIZE 100

class HuffmanTreeNode {
public:
    char data;
    int freq;
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;
    HuffmanTreeNode(char character, int frequency)
    {
        data = character;
        freq = frequency;
        left = right = NULL;
    }
};

class Compare {
public:
    bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b)
    {
        // Comparison function for priority queue
        // Used to prioritize nodes based on their frequencies
        return a->freq > b->freq;
    }
};

// Function to generate the Huffman tree
HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> pq)
{
    // Continue until there is only one node in the priority queue
    while (pq.size() != 1) {
        // Extract two nodes with the lowest frequencies
        HuffmanTreeNode* left = pq.top();
        pq.pop();
        HuffmanTreeNode* right = pq.top();
        pq.pop();

        // Create a new internal node with a special character ('$')
        // Its frequency is the sum of the frequencies of the two nodes
        HuffmanTreeNode* node = new HuffmanTreeNode('$', left->freq + right->freq);
        node->left = left;
        node->right = right;

        // Add the new internal node back to the priority queue
        pq.push(node);
    }
    // The remaining node in the priority queue is the root of the Huffman tree
    return pq.top();
}

// Function to print Huffman codes for each character
void printCodes(HuffmanTreeNode* root, int arr[], int top)
{
    // Recursive function to traverse the Huffman tree and print codes
    if (root->left) {
        // If moving to the left child, append '0' to the code
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        // If moving to the right child, append '1' to the code
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        // If a leaf node is reached, print the character and its code
        cout << root->data << " ";
        cout << " --> ";
        for (int i = 0; i < top; i++) {
            cout << arr[i];
        }
        cout << endl;
    }
}

// Function to generate Huffman codes for given characters and frequencies
void HuffmanCodes(char data[], int freq[], int size)
{
    // Priority queue to store Huffman tree nodes
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, Compare> pq;

    // Create a leaf node for each character and its frequency, and add it to the priority queue
    for (int i = 0; i < size; i++) {
        HuffmanTreeNode* newNode = new HuffmanTreeNode(data[i], freq[i]);
        pq.push(newNode);
    }

    // Generate the Huffman tree and get the root
    HuffmanTreeNode* root = generateTree(pq);

    // Array to store the binary codes during traversal
    int arr[MAX_SIZE], top = 0;

    // Print Huffman codes for each character
    printCodes(root, arr, top);
}

int main()
{
    // Example data and frequencies
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 15, 29, 2, 13, 56, 35 };
    int size = sizeof(data) / sizeof(data[0]);

    // Call the HuffmanCodes function with the provided data and frequencies
    HuffmanCodes(data, freq, size);

    return 0;
}


// #include <iostream>
// #include <queue>
// using namespace std;
// #define MAX_SIZE 100
 
// class HuffmanTreeNode {
// public:
//     char data;
//     int freq;
//     HuffmanTreeNode* left;
//     HuffmanTreeNode* right;
//     HuffmanTreeNode(char character,int frequency)
//     {
//         data = character;
//         freq = frequency;
//         left = right = NULL;
//     }
// };

// class Compare {
// public:
//     bool operator()(HuffmanTreeNode* a,HuffmanTreeNode* b)
//     {
//         return a->freq > b->freq;
//     }
// };
 
// HuffmanTreeNode* generateTree(priority_queue<HuffmanTreeNode*,vector<HuffmanTreeNode*>,Compare> pq)
// {
//     while (pq.size() != 1) {
//         HuffmanTreeNode* left = pq.top();
//         pq.pop();
//         HuffmanTreeNode* right = pq.top();
//         pq.pop();
//         HuffmanTreeNode* node = new HuffmanTreeNode('$',left->freq + right->freq);
//         node->left = left;
//         node->right = right;
//         pq.push(node);
//     }
//     return pq.top();
// }
 
// void printCodes(HuffmanTreeNode* root,int arr[], int top)
// {
//     if (root->left) {
//         arr[top] = 0;
//         printCodes(root->left, arr, top + 1);
//     }
//     if (root->right) {
//         arr[top] = 1;
//         printCodes(root->right, arr, top + 1);
//     }
//     if (!root->left && !root->right) {
//         cout << root->data << " ";
//         cout << " --> ";
//         for (int i = 0; i < top; i++) {
//             cout << arr[i];
//         }
//         cout << endl;
//     }
// }
 
// void HuffmanCodes(char data[], int freq[], int size)
// {
//     priority_queue<HuffmanTreeNode*,vector<HuffmanTreeNode*>,Compare>pq;
//     for (int i = 0; i < size; i++) {
//         HuffmanTreeNode* newNode = new HuffmanTreeNode(data[i], freq[i]);
//         pq.push(newNode);
//     }
//     HuffmanTreeNode* root = generateTree(pq);

//     int arr[MAX_SIZE], top = 0;
//     printCodes(root, arr, top);
// }
 
// int main()
// {
//     char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
//     int freq[] = { 5, 9, 12, 13, 16, 45 };
//     int size = sizeof(data) / sizeof(data[0]);
 
//     HuffmanCodes(data, freq, size);
//     return 0;
// }