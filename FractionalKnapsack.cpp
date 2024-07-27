#include <iostream>
#include <algorithm>

using namespace std;

// Structure to represent each item
struct Item {
    int weight;     // Weight of the item
    int value;      // Value of the item
    double ratio;   // Value-to-weight ratio
};

// Comparator function for sorting items in descending order of value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to solve the fractional knapsack problem
double fractionalKnapsack(int capacity, Item items[], int n) {
    // Sort items based on value-to-weight ratio in descending order
    sort(items, items + n, compare);

    double maxTotalValue = 0.0;

    // Iterate through the sorted items
    for (int i = 0; i < n; ++i) {
        // If knapsack capacity is exhausted, break out of the loop
        if (capacity == 0) {
            break;
        }

        // Determine the weight to add to the knapsack (either the full item or a fraction)
        int weightToAdd = min(items[i].weight, capacity);

        // Add the corresponding value to the total value
        maxTotalValue += (static_cast<double>(weightToAdd) / items[i].weight) * items[i].value;

        // Update the remaining capacity of the knapsack
        capacity -= weightToAdd;
    }

    // Return the maximum total value in the knapsack
    return maxTotalValue;
}

// Main function to take user input and call the fractionalKnapsack function
int main() {
    int n; // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    Item items[n];

    // Take input for weights and values of each item
    cout << "Enter the weight and value of each item:\n";
    for (int i = 0; i < n; ++i) {
        cin >> items[i].weight >> items[i].value;

        // Calculate and store the value-to-weight ratio for each item
        items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
    }

    int capacity;
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    // Call the fractionalKnapsack function and store the result
    double result = fractionalKnapsack(capacity, items, n);

    // Display the maximum total value in the knapsack
    cout << "Maximum total value in the knapsack: " << result << endl;

    return 0;
}


// #include <iostream>
// #include <algorithm>

// using namespace std;

// struct Item {
//     int weight;
//     int value;
//     double ratio; // Value-to-weight ratio
// };

// bool compare(Item a, Item b) {
//     return a.ratio > b.ratio;
// }

// double fractionalKnapsack(int capacity, Item items[], int n) {
//     sort(items, items + n, compare);

//     double maxTotalValue = 0.0;

//     for (int i = 0; i < n; ++i) {
//         if (capacity == 0) {
//             break;
//         }
//         int weightToAdd = min(items[i].weight, capacity);
//         maxTotalValue += (static_cast<double>(weightToAdd) / items[i].weight) * items[i].value;
//         capacity -= weightToAdd;
//     }

//     return maxTotalValue;
// }

// int main() {
//     int n; // Number of items
//     cout << "Enter the number of items: ";
//     cin >> n;

//     Item items[n];

//     cout << "Enter the weight and value of each item:\n";
//     for (int i = 0; i < n; ++i) {
//         cin >> items[i].weight >> items[i].value;
//         items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
//     }

//     int capacity;
//     cout << "Enter the capacity of the knapsack: ";
//     cin >> capacity;

//     double result = fractionalKnapsack(capacity, items, n);

//     cout << "Maximum total value in the knapsack: " << result << endl;

//     return 0;
// }


