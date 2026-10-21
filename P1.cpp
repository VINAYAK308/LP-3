/*Write a program non-recursive and recursive program to calculate Fibonacci numbers
and analyze their time and space complexity.*/

#include <iostream>
using namespace std;

// Recursive Fibonacci
long long fibonacciRecursive(int n) {
    if (n <= 1)
        return n;

    return fibonacciRecursive(n - 1) +
           fibonacciRecursive(n - 2);
}

// Non-recursive / Iterative Fibonacci
long long fibonacciIterative(int n) {
    if (n <= 1)
        return n;

    long long a = 0, b = 1;

    for (int i = 2; i <= n; i++) {
        long long c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main() {

    int n;

    cout << "Enter the value of n: ";
    cin >> n;

    if (n < 0) {
        cout << "Please enter a non-negative number." << endl;
        return 0;
    }

    cout << "\nFibonacci number using Recursive Method: "
         << fibonacciRecursive(n) << endl;

    cout << "Fibonacci number using Non-Recursive Method: "
         << fibonacciIterative(n) << endl;

    return 0;
}