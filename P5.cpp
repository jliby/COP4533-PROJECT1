#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Transaction {
    int stock_idx;
    int buy_day;
    int sell_day;
    int profit;
};

// Task 5: Big Theta(m * n^2 * k) time dynamic programming algorithm for solving problem 2.
int task5(std::vector<std::vector<int>> &prices, int m, int n, int k, std::vector<Transaction> &transactions) {
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));

    // Fill the DP table by iterating through all stocks and days
    for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
        int min_price = prices[stock_idx][0];
        for (int day = 1; day < n; ++day) {
            // minimum price if a lower price is found
            min_price = std::min(min_price, prices[stock_idx][day]);
            //  current stock and day
            dp[stock_idx][day] = std::max(dp[stock_idx][day - 1], prices[stock_idx][day] - min_price);
        }
    }

    // Find the top k transactions
    for (int t = 0; t < k; ++t) {
        Transaction best_trans;
        best_trans.profit = 0;

        for (int stock_idx = 0; stock_idx < m; ++stock_idx) {
            for (int day = 1; day < n; ++day) {
                if (dp[stock_idx][day] > best_trans.profit) {
                    best_trans.profit = dp[stock_idx][day];
                    best_trans.stock_idx = stock_idx;
                    best_trans.sell_day = day;
                }
            }
        }

        // Find the buy day for the best transaction
        int min_price = prices[best_trans.stock_idx][0];
        for (int day = 1; day < best_trans.sell_day; ++day) {
            if (prices[best_trans.stock_idx][day] < min_price) {
                min_price = prices[best_trans.stock_idx][day];
                best_trans.buy_day = day;
            }
        }

        // Add the best transaction to the transactions vector
        transactions.push_back(best_trans);

        // Update the prices for the selected stock to avoid reusing the same transaction
        for (int day = best_trans.buy_day; day <= best_trans.sell_day; ++day) {
            prices[best_trans.stock_idx][day] = 0;
        }
    }

    // Calculate the total profit
    int total_profit = 0;
    for (const Transaction &trans : transactions) {
        total_profit += trans.profit;
    }

    return total_profit;
}

int main() {
    // Example usage of task5 function
    std::vector<std::vector<int>> prices = {{100, 180, 260, 310, 40, 535, 695} ,{90, 80, 70, 60, 50, 40, 30}};
    int m = 2, n = 7, k = 3;
    std::vector<Transaction> transactions;

    int total_profit = task5(prices, m, n, k, transactions);
    std::cout << "Total profit: " << total_profit << std::endl;

    for (const Transaction &trans : transactions) {
        std::cout << "Stock: " << trans.stock_idx << ", BuyDay: " << trans.buy_day << ", SellDay: " << trans.sell_day << std::endl;
    }
return 0;
}