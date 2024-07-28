#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// This function partitions the array using Lomuto's partition scheme
int lomutoPartition(int array[], int low, int high)
{
    int pivot = array[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) 
    {
        if (array[j] <= pivot) {
            i++; 
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

// This function chooses a random pivot and calls lomutoPartition
int randomizedPartition(int array[], int low, int high)
{
    srand(time(NULL));
    int random = low + rand() % (high - low + 1);
    swap(array[random], array[high]);
    return lomutoPartition(array, low, high);
}

// This is the main QuickSort function
void quickSort(int array[], int low, int high)
{
    if (low < high) {
        int pivotIndex = randomizedPartition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

// Function to print the array
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
        cout << array[i] << " "; 
    cout << endl;
}

// Driver code
int main()
{
    int array[] = { 11, 4, 12, 7, 2, 3 };
    int size = sizeof(array) / sizeof(array[0]);
    
    quickSort(array, 0, size - 1);
    
    cout << "Sorted array using randomization: " << endl;
    printArray(array, size);
    
    return 0;
}
