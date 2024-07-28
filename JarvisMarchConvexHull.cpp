#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

// Utility function to find orientation of ordered triplet (p, q, r).
// Returns:
// 0 -> p, q, r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return; // Convex hull is not possible

    // Initialize result
    vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x)
            l = i;
    }

    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again
    int p = l, q;
    do {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x, q)
        // is counterclockwise for all points 'x'
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        // Set p as q for next iteration
        p = q;

    } while (p != l); // While we don't come to first point

    // Print result
    for (auto point : hull) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                            {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    cout << "Convex Hull points: \n";
    convexHull(points);

    return 0;
}
