#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; // Adding the 'std' namespace

struct Point {
    double x;
    double y;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

struct Line {
    double m; // Slope
    double c; // y-Intercept

    Line(const Point& p1, const Point& p2) {
        // Calculate slope (m) and y-intercept (c) of the line passing through p1 and p2
        m = (p2.y - p1.y) / (p2.x - p1.x);
        c = p1.y - m * p1.x;
    }
};

// Function to find intersection point of two lines
Point findIntersection(const Line& line1, const Line& line2) {
    double x = (line2.c - line1.c) / (line1.m - line2.m);
    double y = line1.m * x + line1.c;
    return Point(x, y);
}

// Function to compute orientation of ordered triplet (p, q, r)
// Returns:
// 0 -> p, q, r are collinear
// 1 -> Clockwise
// 2 -> Counterclockwise
int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // clock or counterclockwise
}

// Function to compute the convex hull using Graham's scan algorithm
vector<Point> grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points; // Convex hull not possible with less than 3 distinct points

    // Sort points lexicographically
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    // Function to check if three points make a counterclockwise turn
    auto ccw = [](const Point& p, const Point& q, const Point& r) {
        return (q.y - p.y) * (r.x - q.x) > (q.x - p.x) * (r.y - q.y);
    };

    // Build lower hull
    vector<Point> lowerHull;
    for (const Point& p : points) {
        while (lowerHull.size() >= 2 && !ccw(lowerHull[lowerHull.size() - 2], lowerHull.back(), p)) {
            lowerHull.pop_back();
        }
        lowerHull.push_back(p);
    }

    // Build upper hull
    vector<Point> upperHull;
    for (int i = points.size() - 1; i >= 0; --i) {
        while (upperHull.size() >= 2 && !ccw(upperHull[upperHull.size() - 2], upperHull.back(), points[i])) {
            upperHull.pop_back();
        }
        upperHull.push_back(points[i]);
    }

    // Remove last point of each half because it's repeated at the beginning of the other half
    lowerHull.pop_back();
    upperHull.pop_back();

    // Concatenate lower and upper hull to form the full convex hull
    vector<Point> convexHull(lowerHull);
    convexHull.insert(convexHull.end(), upperHull.begin(), upperHull.end());

    // Remove duplicate points in case of collinear points
    convexHull.erase(unique(convexHull.begin(), convexHull.end(),
                             [](const Point& a, const Point& b) {
                                 return a.x == b.x && a.y == b.y;
                             }),
                     convexHull.end());

    return convexHull;
}

int main() {
    // Input four points (representing two lines)
    vector<Point> points;
    cout << "Enter four points (x y each):" << endl;
    for (int i = 0; i < 4; ++i) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    // Define lines using pairs of points
    Line line1(points[0], points[1]);
    Line line2(points[2], points[3]);

    // Calculate intersection point of the two lines
    Point intersection = findIntersection(line1, line2);
    cout << "Intersection Point: (" << intersection.x << ", " << intersection.y << ")\n";

    // Compute convex hull around the intersection point
    vector<Point> intersectionPoint = {intersection};
    vector<Point> convexHull = grahamScan(intersectionPoint);

    cout << "Convex Hull of Intersection Point:\n";
    for (const Point& p : convexHull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
