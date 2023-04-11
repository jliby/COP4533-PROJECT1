#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int task6(vector<vector<int>>& prices, int m, int n, int k, int& max_stock_idx, int& buy_day, int& sell_day) {
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(k + 1, vector<int>(n, 0)));

    for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
        for (int t = 1; t <= k; ++t) {
            int max_diff = -prices[stock_idx][0];
            for (int day = 1; day < n; ++day) {
                dp[stock_idx][t][day] = max(dp[stock_idx][t][day - 1], prices[stock_idx][day] + max_diff);
                max_diff = max(max_diff, dp[stock_idx][t - 1][day] - prices[stock_idx][day]);
            }
        }
    }

    int max_profit = 0;
    for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
        if (dp[stock_idx][k][n - 1] > max_profit) {
            max_profit = dp[stock_idx][k][n - 1];
            max_stock_idx = stock_idx;
        }
    }

    sell_day = -1;
    for (int day = n - 1; day >= 0; --day) {
        if (dp[max_stock_idx][k][day] == max_profit && sell_day == -1) {
            sell_day = day;
        } else if (dp[max_stock_idx][k][day] < max_profit) {
            buy_day = day;
            break;
        }
    }

    vector<pair<int,int>> transactions;
    int day = sell_day;
    while (k > 0 && day >= 0) {
        if (dp[max_stock_idx][k][day] == dp[max_stock_idx][k][day-1]) {
            day--;
        } else {
            transactions.push_back(make_pair(day, -1));
            for (int prev_day = day-1; prev_day >= 0; prev_day--) {
                if (dp[max_stock_idx][k-1][prev_day] - prices[max_stock_idx][prev_day] == dp[max_stock_idx][k][day]) {
                    transactions.back().second = prev_day;
                    break;
                }
            }
            k--;
            day = transactions.back().second - 1;
        }
    }
    reverse(transactions.begin(), transactions.end());

    cout << "Maximum profit: " << max_profit << endl;
    cout << "Stock index: " << max_stock_idx << endl;
    cout << "Buy day: " << buy_day << endl;
    cout << "Sell day: " << sell_day << endl;
    cout << "Transactions:" << endl;
    for (const auto& transaction : transactions) {
        cout << "Buy day: " << transaction.second << ", Sell day: " << transaction.first << endl;
    }

    return max_profit;
}
int main() {
    vector<vector<int>> prices = {{3,2,6,5,0,3},{1,3,1,2,5,4},{3,3,3,3,3,3}};
    int m = 3;
    int n = 6;
    int k = 3;
    int max_stock_idx, buy_day, sell_day;
    int max_profit = task6(prices, m, n, k, max_stock_idx, buy_day, sell_day);
    return 0;
}
