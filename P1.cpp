#include <iostream>
#include <vector>
using namespace std;


int max_profit_brute_force(const vector<vector<int>>& A) {
    int m = A.size();
    int n = A[0].size();
    int max_profit = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                int profit = A[i][k] - A[i][j];
                max_profit = max(max_profit, profit);
            }
        }
    }

    return max_profit;
}

int main() {
    vector<vector<int>> A = {
        {10, 12, 14, 18, 20},
        {13, 15, 19, 21, 25},
        {9, 10, 12, 16, 22}
    };

    int max_profit = max_profit_brute_force(A);
    std::cout << "Maximum profit: " << max_profit << std::endl;

    return 0;
}
