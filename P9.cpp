#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int max_profit(vector<vector<int>> &A, int c, vector<vector<int>> &transaction) {
    int m = A.size(), n = A[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    transaction.resize(m, vector<int>(2, -1));

    for (int i = 0; i < m; ++i) {
        deque<int> max_profit, transaction_idx;
        for (int j = 0; j < n; ++j) {
            if (j >= c) {
                max_profit.push_back(A[i][j - c] - A[i][j - c - 1]);
                transaction_idx.push_back(j - c);
            }

            if (j == 0 || A[i][j] > A[i][j - 1] + (max_profit.empty() ? 0 : max_profit.front())) {
                dp[i][j] = A[i][j];
                transaction[i] = {j, j};
            } else {
                dp[i][j] = A[i][j - 1] + max_profit.front();
                transaction[i] = {transaction_idx.front(), j};
            }

            if (!max_profit.empty() && max_profit.front() == A[i][j - c] - A[i][j - c - 1]) {
                max_profit.pop_front();
                transaction_idx.pop_front();
            }
        }
    }

    int max_profit_val = 0, best_stock = -1;
    for (int i = 0; i < m; ++i) {
        if (dp[i][n - 1] > max_profit_val) {
            max_profit_val = dp[i][n - 1];
            best_stock = i;
        }
    }

    cout << "Stock: " << best_stock << ", Buy day: " << transaction[best_stock][0] << ", Sell day: " << transaction[best_stock][1] << endl;
    return max_profit_val;
}

int main() {
    vector<vector<int>> A = {{1, 2, 3, 0, 2},
                             {3, 2, 6, 5, 0},
                             {1, 2, 3, 0, 2}};
    int c = 2;
    vector<vector<int>> transaction;

    cout << "Max profit: " << max_profit(A, c, transaction) << endl;

    return 0;
}
