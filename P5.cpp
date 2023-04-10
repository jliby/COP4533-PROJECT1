#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

vector<vector<int>> maxProfitKTransactions(vector<vector<int>>& prices, int m, int n, int k) {
    vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(m, vector<int>(n, 0)));

    // Fill the DP table by iterating through all transactions, stocks, and days
    for (int t = 1; t <= k; ++t) {
        for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
            int max_diff = -prices[stock_idx][0];
            for (int day = 1; day < n; ++day) {
                max_diff = max(max_diff, dp[t - 1][stock_idx][day - 1] - prices[stock_idx][day]);
                dp[t][stock_idx][day] = max(dp[t][stock_idx][day - 1], prices[stock_idx][day] + max_diff);
            }
        }
    }

    // Find the maximum profit and the corresponding stock, buy day, and sell day
    int max_profit = 0;
    vector<vector<int>> transactions(k, vector<int>(3, 0));
    for (int t = k; t >= 1; --t) {
        int max_stock_idx = 0, sell_day = 0;
        for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
            for (int day = 1; day < n; ++day) {
                if (dp[t][stock_idx][day] > max_profit) {
                    max_profit = dp[t][stock_idx][day];
                    max_stock_idx = stock_idx;
                    sell_day = day;
                }
            }
        }

        int buy_day = 0;
        int max_diff = -prices[max_stock_idx][0];
        for (int day = 1; day < sell_day; ++day) {
            if (dp[t - 1][max_stock_idx][day - 1] - prices[max_stock_idx][day] > max_diff) {
                max_diff = dp[t - 1][max_stock_idx][day - 1] - prices[max_stock_idx][day];
                buy_day = day;
            }
        }

        transactions[t - 1] = {max_stock_idx, buy_day, sell_day};
    }

    return transactions;
}

int main() {
    vector<vector<int>> prices = {
        {1, 2, 3},
        {1, 2, 9},
        {1, 2, 4}
    };

    int m = prices.size();
    int n = prices[0].size();
    int k = 2;

    vector<vector<int>> transactions = maxProfitKTransactions(prices, m, n, k);

    int total_profit = 0;
    for (int i = 0; i < k; ++i) {
        int stock = transactions[i][0];
        int buy_day = transactions[i][1];
        int sell_day = transactions[i][2];
        int profit = prices[stock][sell_day] - prices[stock][buy_day];
        total_profit += profit;

        cout << "Transaction " << i + 1 << ": Stock " << stock + 1 << " | Buy day: " << buy_day + 1 << " | Sell day: " << sell_day + 1 << " | Profit: " << profit << endl;
    }

   
    return 0;
}