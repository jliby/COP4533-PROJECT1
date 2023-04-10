#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void Task4(const vector<vector<int>>& stocks, const int k) {
    vector<tuple<int, int, int>> transactions;
    int total_profit = 0;

    for (int t = 0; t < k; t++) {
        int max_profit = 0;
        int stock_index = 0;
        int buy_day = 0;
        int sell_day = 0;

        for (int i = 0; i < stocks.size(); i++) {
            for (int j = 0; j < stocks[i].size(); j++) {
                const int buy_price = stocks[i][j];
                for (int s = j + 1; s < stocks[i].size(); s++) {
                    const int sell_price = stocks[i][s];
                    const int profit = sell_price - buy_price;
                    if (profit > max_profit) {
                        bool is_valid_transaction = all_of(transactions.begin(), transactions.end(),
                            [&](const tuple<int, int, int>& t) {
                                const int stock = get<0>(t);
                                const int buy = get<1>(t);
                                const int sell = get<2>(t);
                                return (i != stock) || (j > sell) || (s < buy);
                            });
                        if (is_valid_transaction) {
                            max_profit = profit;
                            stock_index = i;
                            buy_day = j;
                            sell_day = s;
                        }
                    }
                }
            }
        }
        transactions.emplace_back(stock_index, buy_day, sell_day);
        total_profit += max_profit;
    }

    for (const auto& transaction : transactions) {
        cout << "Stock: " << get<0>(transaction) << ", Buy Day: " << get<1>(transaction) 
             << ", Sell Day: " << get<2>(transaction) << endl;
    }
    cout << "Total profit: " << total_profit << endl;
}


int main() {
    vector<vector<int>> stocks = {
        {10, 22, 5, 75, 65, 80},
        {12, 45, 50, 65, 10, 80},
        {90, 80, 70, 60, 50, 40}
    };
    const int k = 3;
    Task4(stocks, k);
    return 0;
}
