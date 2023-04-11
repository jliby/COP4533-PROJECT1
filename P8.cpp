#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> maxProfit(vector<vector<int>> &prices, int c) {
  int m = prices.size();
  int n = prices[0].size();
  vector<vector<int>> dp(m, vector<int>(n, 0));

  for (int stock = 0; stock < m; stock++) {
    for (int day = 0; day < n; day++) {
      int max_profit = 0;
      for (int sell_day = day + 1; sell_day < n; sell_day++) {
        int profit = prices[stock][sell_day] - prices[stock][day];
        if (sell_day + c < n) {
          profit += dp[stock][sell_day + c];
        }
        max_profit = max(max_profit, profit);
      }
      dp[stock][day] =
          day == 0 ? max_profit : max(max_profit, dp[stock][day - 1]);
    }
  }

  return dp;
}

void printTransactions(vector<vector<int>> &prices, vector<vector<int>> &dp,
                       int c) {
  int m = prices.size();
  int n = prices[0].size();
  int max_profit = 0;

  for (int stock = 0; stock < m; stock++) {
    int day = 0;
    while (day < n) {
      if (day == 0 || dp[stock][day] != dp[stock][day - 1]) {
        int buy_day = day;
        int sell_day = day + 1;
        max_profit = 0;
        for (int d = day + 1; d < n; d++) {
          int profit = prices[stock][d] - prices[stock][day];
          if (d + c < n) {
            profit += dp[stock][d + c];
          }

          if (profit > max_profit) {
            max_profit = profit;
            sell_day = d;
          }
        }
        cout << "Stock: " << stock + 1 << ", Buy Day: " << buy_day + 1
             << ", Sell Day: " << sell_day + 1 << endl;
        day = sell_day + c;
      } else {
        day++;
      }
    }
  }
  cout << "MAX PROFIT " << max_profit << endl;
}

int main() {
  vector<vector<int>> prices = {
      {5, 8, 1, 7, 2, 6, 3, 10},
      {1, 2, 3, 4, 5, 6, 7, 8},
  };
  int c = 2;

  vector<vector<int>> dp = maxProfit(prices, c);
  printTransactions(prices, dp, c);

  return 0;
}
