/*Write a program to solve a 0-1 Knapsack problem using dynamic programming
strategy.*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // DP table
    vector<vector<int>> dp(
        n + 1,
        vector<int>(capacity + 1, 0)
    );

    // Build DP table
    for (int i = 1; i <= n; i++) {

        for (int w = 0; w <= capacity; w++) {

            // Item cannot be included
            dp[i][w] = dp[i - 1][w];

            // Item can be included
            if (weight[i - 1] <= w) {

                dp[i][w] = max(
                    dp[i][w],
                    value[i - 1] +
                    dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    // Maximum value
    cout << "\nMaximum value: "
         << dp[n][capacity] << endl;

    // Find selected items
    cout << "Selected items: ";

    int w = capacity;

    for (int i = n; i > 0; i--) {

        if (dp[i][w] != dp[i - 1][w]) {

            cout << i << " ";

            w -= weight[i - 1];
        }
    }

    cout << endl;

    return 0;
}