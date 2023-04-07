#include <iostream>
#include <vector>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> A(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    int max_profit = 0;
    int stock, buy_day, sell_day;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int profit = A[i][k] - A[i][j];
                if (profit > max_profit) {
                    max_profit = profit;
                    stock = i;
                    buy_day = j;
                    sell_day = k;
                }
            }
        }
    }

    cout << stock << " " << buy_day << " " << sell_day << endl;
    return 0;
}
