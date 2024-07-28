#include <bits/stdc++.h>
using namespace std;

#define Point pair<double, double>

void displayPoint(Point P)
{
    cout << "(" << P.first << ", " << P.second << ")" << endl;
}

Point calculateLineIntersection(Point A, Point B, Point C, Point D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1 * A.first + b1 * A.second;

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2 * C.first + b2 * C.second;

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        return make_pair(numeric_limits<double>::infinity(), numeric_limits<double>::infinity());
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        return make_pair(x, y);
    }
}

// Driver code
int main()
{
    Point A = make_pair(1, 2);
    Point B = make_pair(3, 5);
    Point C = make_pair(5, 6);
    Point D = make_pair(7, 12);

    Point intersection = calculateLineIntersection(A, B, C, D);

    if (intersection.first == numeric_limits<double>::infinity() &&
        intersection.second == numeric_limits<double>::infinity())
    {
        cout << "The given lines AB and CD are parallel.\n";
    }
    else
    {
        cout << "The intersection of the given lines AB and CD is: ";
        displayPoint(intersection);
    }

    return 0;
}
