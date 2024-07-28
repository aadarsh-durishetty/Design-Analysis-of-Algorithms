#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate the number of digits in a number
int numDigits(long long n) {
    return n > 0 ? (int) log10((double) n) + 1 : 1;
}

// Function to implement Karatsuba multiplication
long long karatsuba(long long x, long long y) {
    // Base case
    if (x < 10 || y < 10)
        return x * y;

    // Calculate the number of digits of the numbers
    int numDigitsX = numDigits(x);
    int numDigitsY = numDigits(y);
    int n = max(numDigitsX, numDigitsY);

    // Split the numbers into two halves
    int half = n / 2;
    long long power = (long long) pow(10, half);

    long long a = x / power;
    long long b = x % power;
    long long c = y / power;
    long long d = y % power;

    // Recursively calculate the products
    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);
    long long ad_plus_bc = karatsuba(a + b, c + d) - ac - bd;

    // Combine the results using the Karatsuba formula
    return ac * (long long) pow(10, 2 * half) + (ad_plus_bc * (long long) pow(10, half)) + bd;
}

int main() {
    long long x, y;
    cout << "Enter two numbers to multiply: " << endl;
    cin >> x >> y;

    // Call the karatsuba function
    long long result = karatsuba(x, y);
    cout << "Result of multiplication: " << result << endl;

    return 0;
}
