#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int maxProfit(vector<vector<int>>& prices, int m, int n, int& max_stock_idx, int& buy_day, int& sell_day) {
    vector<vector<int>> dp(m, vector<int>(n, 0));

    // Fill the DP table by iterating through all stocks and days
    for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
        int min_price = prices[stock_idx][0];
        for (int day = 1; day < n; ++day) {
            // minimum price if a lower price is found
            min_price = min(min_price, prices[stock_idx][day]);
            //  current stock and day
            dp[stock_idx][day] = max(dp[stock_idx][day - 1], prices[stock_idx][day] - min_price);
        }
    }

    //  corresponding stock index and selling day
    int max_profit = 0;
    for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
        for (int day = 1; day < n; ++day) {
            if (dp[stock_idx][day] > max_profit) {
                max_profit = dp[stock_idx][day];
                max_stock_idx = stock_idx;
                sell_day = day;
            }
        }
    }

    //  maximum profit
    int min_price = prices[max_stock_idx][0];
    for (int day = 1; day < sell_day; ++day) {
        if (prices[max_stock_idx][day] < min_price) {
            min_price = prices[max_stock_idx][day];
            buy_day = day;
        }
    }

    return max_profit;
}

int main() {
    vector<vector<int>> prices = {
        {1, 2, 3},
        {1, 2, 9},
        {1, 2, 4}
    };

    int m = prices.size();
    int n = prices[0].size();

    int max_stock_idx = 0, buy_day = 0, sell_day = 0;
    int max_profit = maxProfit(prices, m, n, max_stock_idx, buy_day, sell_day);

    cout << "Maximum profit: " << max_profit << endl;
    cout << "Stock: " << max_stock_idx + 1 << " Buy day: " << buy_day + 1 << " Sell day: " << sell_day + 1 << endl;

    return 0;
}
