#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct Result {
    int profit;
    int stock_idx;
    int buy_day;
    int sell_day;
};
static int sellDay = 0;
static int currentMax = 0;
Result maxProfitRecursive(vector<vector<int>>& prices, int m, int n, int k, int stock_idx, int transactions, int day, bool canBuy) {
    if (day == n || transactions == k * 2) {
        return {0, -1, -1, -1};
    }

    Result no_action_profit = maxProfitRecursive(prices, m, n, k, stock_idx, transactions, day + 1, canBuy);
    Result action_profit = {0, -1, -1, -1};

    if (canBuy) {
        Result tmp = maxProfitRecursive(prices, m, n, k, stock_idx, transactions + 1, day + 1, !canBuy);
        action_profit.profit = -prices[stock_idx][day] + tmp.profit;
        action_profit.buy_day = day;
    } else {
        Result tmp = maxProfitRecursive(prices, m, n, k, stock_idx, transactions + 1, day + 1, !canBuy);
        action_profit.profit = prices[stock_idx][day] + tmp.profit;
        if (currentMax < action_profit.profit) {
            currentMax = action_profit.profit;
            sellDay = day;
        }
    }

    if (action_profit.profit > no_action_profit.profit) {
        action_profit.stock_idx = stock_idx;
        no_action_profit = action_profit;
    } else {
        no_action_profit.stock_idx = stock_idx;
    }

    return no_action_profit;
}

Result maxProfit(vector<vector<int>>& prices, int m, int n, int k) {
    Result max_profit = {0, -1, -1, -1};

    for (int i = 0; i < m; ++i) {
        Result tmp = maxProfitRecursive(prices, m, n, k, i, 0, 0, true);
        if (tmp.profit > max_profit.profit) {
            max_profit = tmp;
        }
    }

    return max_profit;
}

int main() {
    vector<vector<int>> prices = {
        {1,2,3},
        {1,2,9},
        {1,2,4}
    };

    int m = prices.size();
    int n = prices[0].size();
    int k = 2;

    Result result = maxProfit(prices, m, n, k);

    cout << "Maximum profit: " << result.profit << endl;
    cout << "Stock: " << result.stock_idx + 1 << endl;
    cout << "Buy day: " << result.buy_day + 1 << endl;
    cout << "Sell day: " << sellDay + 1 << endl;

    return 0;
}
