#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

// A structure to represent a Point in 2D plane 
class Point 
{ 
public:
    int x, y; 
}; 

// Utility function to calculate Euclidean distance between two points
float dist(Point p1, Point p2) 
{ 
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + 
                (p1.y - p2.y) * (p1.y - p2.y)); 
} 

// Function to compare points based on x-coordinate for sorting
int compareX(const void* a, const void* b) 
{ 
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->x - p2->x); 
} 

// Function to compare points based on y-coordinate for sorting
int compareY(const void* a, const void* b) 
{ 
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    return (p1->y - p2->y); 
} 

// Function to find the closest pair of points using a brute-force approach
pair<Point, Point> bruteForceClosestPair(Point P[], int n) 
{ 
    float minDist = numeric_limits<float>::max();
    pair<Point, Point> closestPair;

    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            float currentDist = dist(P[i], P[j]);
            if (currentDist < minDist) 
            {
                minDist = currentDist;
                closestPair = {P[i], P[j]};
            }
        }
    }

    return closestPair;
} 

// Function to find the closest pair of points in a strip of points
pair<Point, Point> stripClosest(Point strip[], int size, float d) 
{ 
    float minDist = d;
    pair<Point, Point> closestPair;

    // Sort strip array based on y-coordinate
    qsort(strip, size, sizeof(Point), compareY); 

    // Compare each point with the next points in the strip
    for (int i = 0; i < size; ++i) 
    {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minDist; ++j) 
        {
            float currentDist = dist(strip[i], strip[j]);
            if (currentDist < minDist) 
            {
                minDist = currentDist;
                closestPair = {strip[i], strip[j]};
            }
        }
    }

    return closestPair;
} 

// Recursive function to find the closest pair of points using divide and conquer
pair<Point, Point> closestPairUtil(Point P[], int n) 
{ 
    if (n <= 3) 
        return bruteForceClosestPair(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    // Recursively find the closest pairs in left and right halves
    pair<Point, Point> leftClosest = closestPairUtil(P, mid);
    pair<Point, Point> rightClosest = closestPairUtil(P + mid, n - mid);

    // Get the minimum distance from left and right halves
    float d = min(dist(leftClosest.first, leftClosest.second), dist(rightClosest.first, rightClosest.second));

    // Create a strip of points within distance d from the middle line
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) 
    {
        if (abs(P[i].x - midPoint.x) < d) 
        {
            strip[j] = P[i];
            j++;
        }
    }

    // Find the closest pair in the strip
    pair<Point, Point> stripClosestPair = stripClosest(strip, j, d);

    // Compare distances to get the overall closest pair
    if (dist(leftClosest.first, leftClosest.second) < dist(rightClosest.first, rightClosest.second)) 
    {
        return leftClosest;
    }
    else 
    {
        return rightClosest;
    }
} 

// Function to find the closest pair of points in the given array of points
pair<Point, Point> closestPair(Point P[], int n) 
{ 
    // Sort points based on x-coordinate
    qsort(P, n, sizeof(Point), compareX); 
    
    // Find the closest pair of points recursively
    return closestPairUtil(P, n); 
} 

// Driver code
int main() 
{ 
    Point P[] = {{3, 4}, {17, 43}, {15, 32}, {6, 2}};
    int n = sizeof(P) / sizeof(P[0]); 

    // Find the closest pair of points
    pair<Point, Point> closestPoints = closestPair(P, n);

    // Output the smallest distance
    cout << "The smallest distance is " << dist(closestPoints.first, closestPoints.second) << endl;

    // Output the closest pair of points
    cout << "Closest pair of points: (" << closestPoints.first.x << ", " << closestPoints.first.y << ") and (" 
         << closestPoints.second.x << ", " << closestPoints.second.y << ")" << endl;

    return 0; 
} 
