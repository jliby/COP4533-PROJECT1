#include <iostream>
#include <vector>
using namespace std;

int max_profit(vector<vector<int>>& A, int stock, int day, vector<vector<int>>& memo, int& buyDay, int& sellDay) {
    if (day == A[0].size()) {
        return 0;
    }
    if (memo[stock][day] != -1) {
        return memo[stock][day];
    }
    int max_profit_so_far = 0;
    for (int i = day + 1; i < A[0].size(); i++) {
        int profit = A[stock][i] - A[stock][day];
        if (profit > 0) {
            int future_profit = max_profit(A, stock, i + 1, memo, buyDay, sellDay);
            if (profit + future_profit > max_profit_so_far) {
                max_profit_so_far = profit + future_profit;
                buyDay = day;
                sellDay = i;
            }
        }
    }
    int future_profit = max_profit(A, stock + 1, day, memo, buyDay, sellDay);
    if (future_profit > max_profit_so_far) {
        max_profit_so_far = future_profit;
    }
    memo[stock][day] = max_profit_so_far;
    return max_profit_so_far;
}

void task2() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> A(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    vector<vector<int>> memo(m, vector<int>(n, -1));
    int max_profit_so_far = 0;
    int stock = 0, buyDay = 0, sellDay = 0;
    for (int i = 0; i < m; i++) {
        int temp_buyDay = 0, temp_sellDay = 0;
        int temp_max_profit = max_profit(A, i, 0, memo, temp_buyDay, temp_sellDay);
        if (temp_max_profit > max_profit_so_far) {
            max_profit_so_far = temp_max_profit;
            stock = i;
            buyDay = temp_buyDay;
            sellDay = temp_sellDay;
        }
    }
    cout << stock + 1 << " " << buyDay + 1 << " " << sellDay + 1 << << endl;
}

int main() {
    task2();
    return 0;
}
