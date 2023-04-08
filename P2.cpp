#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

int run_ALG2(std::vector<std::vector<int>> &copy) {
    int maxProfit = 0;

    for (auto i = 0; i < copy.size(); ++i) {
        int maxProfitPerStock = 0;
        int minPrice = copy[i][0];

        for (auto j = 1; j < copy[i].size(); ++j) {
            if (copy[i][j] < minPrice) {
                minPrice = copy[i][j];
            } else {
                int currentProfit = copy[i][j] - minPrice;
                maxProfitPerStock = std::max(currentProfit, maxProfitPerStock);
            }
        }

        maxProfit = std::max(maxProfit, maxProfitPerStock);
    }

    return maxProfit;
}

void task2() {
    std::string lineOne;
    getline(std::cin, lineOne);
    std::istringstream lineOneStream(lineOne);
    int rows, cols;
    lineOneStream >> rows >> cols;

    std::vector<std::vector<int>> copy(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        std::string temp;
        getline(std::cin, temp);
        std::istringstream tempStream(temp);
        for (int j = 0; j < cols; ++j) {
            tempStream >> copy[i][j];
        }
    }

    int maxProfit = 0;
    int stock = 0, buyDay = 0, sellDay = 0, tempStock = 0, tempBuyDay = 0, tempSellDay = 0;

    for (auto i = 0; i < copy.size(); ++i) {
        int maxProfitPerStock = 0;
        int minPrice = copy[i][0];

        for (auto j = 1; j < copy[i].size(); ++j) {
            if (copy[i][j] < minPrice) {
                minPrice = copy[i][j];
                tempBuyDay = j;
            } else {
                int currentProfit = copy[i][j] - minPrice;
                if (currentProfit > maxProfitPerStock) {
                    maxProfitPerStock = currentProfit;
                    tempStock = i;
                    tempSellDay = j;
                }
            }
        }

        if (maxProfitPerStock > maxProfit) {
            maxProfit = maxProfitPerStock;
            stock = tempStock;
            buyDay = tempBuyDay;
            sellDay = tempSellDay;
        }
    }

    std::cout << (stock + 1) << " " << (buyDay + 1) << " " << (sellDay + 1) << std::endl;
}

int main() {
    task2();
    return 0;
}
