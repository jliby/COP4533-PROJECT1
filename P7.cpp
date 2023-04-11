#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxProfitHelper(vector<vector<int>>& A, int m, int n, int c, int current_day, int current_stock, int current_profit, vector<pair<int, pair<int, int>>>& transactions) {
    if (current_day >= n || current_stock >= m) {
        return current_profit;
    }

    int max_profit = current_profit;
    vector<pair<int, pair<int, int>>> best_transactions = transactions;

    // Sell current stock
    vector<pair<int, pair<int, int>>> sell_transactions = transactions;
    sell_transactions.push_back({current_stock, {current_day - c - 1, current_day}});
    int sell_profit = A[current_stock][current_day] + maxProfitHelper(A, m, n, c, current_day + c + 1, 0, current_profit + A[current_stock][current_day], sell_transactions);
    if (sell_profit > max_profit) {
        max_profit = sell_profit;
        best_transactions = sell_transactions;
    }

    // Move to next stock without selling
    vector<pair<int, pair<int, int>>> next_stock_transactions = transactions;
    int next_stock_profit = maxProfitHelper(A, m, n, c, current_day, current_stock + 1, current_profit, next_stock_transactions);
    if (next_stock_profit > max_profit) {
        max_profit = next_stock_profit;
        best_transactions = next_stock_transactions;
    }

    // Move to next day without selling
    vector<pair<int, pair<int, int>>> next_day_transactions = transactions;
    int next_day_profit = maxProfitHelper(A, m, n, c, current_day + 1, 0, current_profit, next_day_transactions);
    if (next_day_profit > max_profit) {
        max_profit = next_day_profit;
        best_transactions = next_day_transactions;
    }

    transactions = best_transactions;
    return max_profit;
}

int maxProfit(vector<vector<int>>& A, int m, int n, int c, vector<pair<int, pair<int, int>>>& transactions) {
    return maxProfitHelper(A, m, n, c, 0, 0, 0, transactions);
}

int main() {
    vector<vector<int>> A = {
        {1, 2, 3, 4, 5},
        {3, 4, 5, 6, 7},
        {2, 3, 1, 8, 7}
    };
    int m = 3;
    int n = 5;
    int c = 1;

    vector<pair<int, pair<int, int>>> transactions;
    cout << "Maximum profit: " << maxProfit(A, m, n, c, transactions) << endl;

    for (const auto& t : transactions) {
        cout << "Stock: " << t.first << ", Buy day: " << t.second.first << ", Sell day: " << t.second.second << endl;
    }

    return 0;
}
