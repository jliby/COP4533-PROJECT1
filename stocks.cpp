#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include <algorithm>
#include <chrono>
#include <deque>
using namespace std;
using namespace std::chrono;

/*=============
INPUT FUNCTIONS
=============*/
static int sellDay = 0;
static int currentMax = 0;
void logTime(auto& start, auto& stop, string& taskNumber, string outputFileDesignation)
{   
    auto duration_hr = duration_cast<hours>(stop - start);
    auto duration_min = duration_cast<minutes>(stop - start); 
    auto duration_sec = duration_cast<seconds>(stop - start);
    auto duration_millisec = duration_cast<milliseconds>(stop - start);
    auto duration_microsec = duration_cast<microseconds>(stop - start);

    cout << "Outputting execution time of task's algorithm to " << outputFileDesignation << "." << endl; 

    ofstream outputFile(outputFileDesignation);
    if (outputFile.is_open())
    {
        outputFile << "TASK " << taskNumber << "'s ALGORITHM EXECUTION TIME IN INDIVIDUAL UNITS, NOT AS A COMBINED VALUE:" << endl;
        outputFile << "Hours: " << duration_hr.count() << endl;
        outputFile << "Minutes: " << duration_min.count() << endl;
        outputFile << "Seconds: " << duration_sec.count() << endl;
        outputFile << "Milliseconds: " << duration_millisec.count() << endl;
        outputFile << "Microseconds: " << duration_microsec.count();
        outputFile.close();
        cout << "Values written to file." << endl;
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

bool isFile(string& input)
{
    // Checks if the inputted string has the .txt extension as a suffix.

    // If the input length is less than 4, return false.
    // The logic behind this is that the file name must be at least 5 characters long because ".txt" is 4 characters. 
    if (input.size() <= 4)
    {
        return false;
    }
    else if (input.substr(input.find(".")) == ".txt")
    {
        // If the input is at least 5 characters long, check if it has ".txt". If yes, return true.
        return true;
    }

    return false;
}

bool validInput(string& input)
{
    /*
        Input is considered valid if the task number is within range.
        Acceptable input includes:
        - A task number in the range: 1, 2, 3a or 3A, 3b or 3B, 4, 5, 6, 7, 8, 9.
        - A file ending with ".txt".
        All other input is invalid, as there are no tasks associated with it.
    */

    // Checking task number.
    if (input == "1" || input == "2" || input == "3a" || input == "3A" ||
        input == "3b" || input == "3B" || input == "4" || input == "5" ||
        input == "6" || input == "7" || input == "8" || input == "9")
    {
        // The task number is within range.
        return true;
    }
    else if (isFile(input))
    {
        // File with .txt extension is inputted.
        return true;
    }
    // If input is invalid, return false.
    return false;
}

string isValidFile(string& fileName)
{
    string taskNum = "-1";
    ifstream inputFile(fileName);

    inputFile >> taskNum;
    inputFile.close();

    if (validInput(taskNum))
    {
        return taskNum;
    }

    cout << "Error: the task specified in the file does not exist." << endl;
    return taskNum;
}

void extractMN(string infoString, int& m, int& n)
{
    /*
        This function takes in a string that was parsed via getline()
        and splits it according to a space delimiter.

        These values are inserted into a vector which is of size 2.
        Element 1 is m, and element 2 is n. These values are passed in and assigned via reference.
    */

    size_t pos = 0;
    vector<string> values;
    string value;

    while ((pos = infoString.find(" ")) != string::npos)
    {
        value = infoString.substr(0, pos);
        values.push_back(value);
        infoString.erase(0, pos + 1);
    }
    values.push_back(infoString);
    
    m = stoi(values[0]);
    n = stoi(values[1]);
}

bool extractStockPrices(string stockString, vector<vector<int>>& stock_v, map<int, vector<int>>& stock_m, int& n, int day)
{
    /*
        This function extracts the stock prices from a given string.
        A single space character is the delimiter.
    */
    size_t pos = 0;
    vector<int> values;
    string value;

    while ((pos = stockString.find(" ")) != string::npos)
    {
        value = stockString.substr(0, pos);
        values.push_back(stoi(value));
        stockString.erase(0, pos + 1);
    }
    values.push_back(stoi(stockString));

    /*
        The following if statement checks if the number of stock prices matches the inputted n.
        If not, then "false" is returned and the program is ultimately terminated.  
    */
    if (values.size() != n)
    {
        cout << "Error: inputted number of stock prices does not match inputted n on line ";
        return false;
    }
    
    // If the input is valid, push it into the vector of stocks.
    stock_v.push_back(values);
    stock_m.emplace(day, values);
    return true;
}

bool getValues(istream& inputStream, int &problemNumber, string &inputString, int &m, int &n, int &k, int &c, vector<vector<int>> &stock_v, map<int, vector<int>> &stock_m)
{
    /*
        ==========
        USER INPUT
        ==========
        Now, the program will accept user input based on the problem to which the
        inputted task corresponds.

        PROBLEM 1 (Tasks 1, 2, 3a, and 3b)
        - Line 1 consists of two integers m and n separated by a single space.
        - The next m lines consist of n integers (prices for n days) separated by a single space.

        PROBLEM 2 (Tasks 4, 5, and 6)
        - Line 1 consists of one integer, k.
        - Line 2 consists of two integers, m and n, separated by one space character.
        - The next m lines consist of n integers (predicted prices) separated by a single space.

        PROBLEM 3 (Tasks 7, 8, and 9)
        - Line 1 consists of one integer, c.
        - Line 2 consists of two integers, m and n, separated by one space character.
        - The next m lines consist of n integers (predicted prices) separated by a single space.
    */
    if (problemNumber == 1)
    {
        // Line 1: m & n
        getline(inputStream, inputString);
        extractMN(inputString, m, n);

        // Lines 2 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(inputStream, inputString);
            if (extractStockPrices(inputString, stock_v, stock_m, n, i + 1))
                continue;
            else
            {
                cout << (i + 2) << ".\n";
                return false;
            }
        }
    }
    else if (problemNumber == 2)
    {
        // Line 1: k
        getline(inputStream, inputString);
        k = stoi(inputString);

        // Line 2: m & n
        getline(inputStream, inputString);
        extractMN(inputString, m, n);

        // Lines 3 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(inputStream, inputString);
            if (extractStockPrices(inputString, stock_v, stock_m, n, i + 1))
                continue;
            else
            {
                cout << (i + 2) << ".\n";
                return false;
            }
        }
    }
    else if (problemNumber == 3)
    {
        // Line 1: c
        getline(inputStream, inputString);
        c = stoi(inputString);

        // Line 2: m & n
        getline(inputStream, inputString);
        extractMN(inputString, m, n);

        // Lines 3 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(inputStream, inputString);
            if (extractStockPrices(inputString, stock_v, stock_m, n, i + 1))
                continue;
            else
            {
                cout << (i + 2) << ".\n";
                return false;
            }
        }
    }
    return true;
}

void resetValues(int& m, int& n, int& k, int& c, vector<vector<int>>& stock_v, map<int, vector<int>>& stock_m)
{
    m = -1;
    n = -1;
    k = -1;
    c = -1;
    stock_v.clear();
    stock_m.clear();
}

void printValues(int& m, int& n, int& k, int& c, vector<vector<int>>& stock_v, map<int, vector<int>>& stock_m)
{
    cout << "m: " << m << endl;
    cout << "n: " << n << endl;
    cout << "k: " << k << endl;
    cout << "c: " << c << endl;

    cout << "STOCK VECTOR:\n";
    for (int i = 0; i < stock_v.size(); i++)
    {
        cout << "Stock " << (i + 1) << ":";
        for (auto stock : stock_v[i]) {
            cout << " " << stock;
        }
        cout << endl;
    }

    cout << "STOCK MAP:\n";
    for (auto element : stock_m) {
        cout << "Stock " << element.first << ":";
        for (auto stock : element.second) {
            cout << " " << stock;
        }
        cout << endl;
    }
}

int findProblem(string& taskNumber)
{
    /*
        Finding the problem corresponding to the inputted task number.
        - 1, 2, 3a, 3b = Problem 1.
        - 4, 5, 6 = Problem 2.
        - 7, 8, 9 = Problem 3.
    */
    int problemNumber = -1;
    if (taskNumber == "1" || taskNumber == "2" || taskNumber == "3a" ||
        taskNumber == "3A" || taskNumber == "3b" || taskNumber == "3B")
        {
            problemNumber = 1;
        }
    else if (taskNumber == "4" || taskNumber == "5" || taskNumber == "6")
    {
        problemNumber = 2;
    }
    else if (taskNumber == "7" || taskNumber == "8" || taskNumber == "9")
    {
        problemNumber = 3;
    }
    return problemNumber;
}

void printProblemInstructions(int problemNumber)
{
    if (problemNumber == 1)
    {
        cout << "Line 1: 2 integers, m and n, separated by a single space.\n";
        cout << "Lines 2 to m: n integers (prices for n days), separated by a space.\n";
    }
    else if (problemNumber == 2)
    {
        cout << "Line 1: 1 integer, k.\n";
        cout << "Line 2: 2 integers, m and n, separated by a single space.\n";
        cout << "Lines 3 to m: n integers (prices for n days), separated by a space.\n";
    }
    else if (problemNumber == 3)
    {
        cout << "Line 1: 1 integer, c.\n";
        cout << "Line 2: 2 integers, m and n, separated by a single space.\n";
        cout << "Lines 3 to m: n integers (predicted prices) separated by a single space.\n";
    }
}

/*=============
TASK FUNCTIONS
=============*/

void printProblem1Output(int& stock, int& buy_day, int& sell_day)
{
    /*
        OUTPUT:
        Note that stock, buy_day, and sell_day must all be incremented by 1 before printing
        because they represent an INDEX, which begins from 0, but the instructions request output to be indexed from 1.
    */
    cout << (stock + 1) << " " << (buy_day + 1) << " " << (sell_day + 1) << endl;
}

// Task 1: Big Theta(m * n^2) time brute force algorithm for solving problem 1.
void task1(vector<vector<int>>& stocks, int& m, int& n)
{
    int max_profit = 0;
    int stock, buy_day, sell_day;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int profit = stocks[i][k] - stocks[i][j];
                if (profit > max_profit) {
                    max_profit = profit;
                    stock = i;
                    buy_day = j;
                    sell_day = k;
                }
            }
        }
    }

    printProblem1Output(stock, buy_day, sell_day);
}

// Task 2: Big Theta(m * n) time greedy algorithm for solving problem 1.
void task2(vector<vector<int>>& stocks)
{
    int maxProfit = 0;
    int stock = 0, buyDay = 0, sellDay = 0, tempStock = 0, tempBuyDay = 0, tempSellDay = 0;

    for (auto i = 0; i < stocks.size(); ++i) {
        int maxProfitPerStock = 0;
        int minPrice = stocks[i][0];

        for (auto j = 1; j < stocks[i].size(); ++j) {
            if (stocks[i][j] < minPrice) {
                minPrice = stocks[i][j];
                tempBuyDay = j;
            } else {
                int currentProfit = stocks[i][j] - minPrice;
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

    printProblem1Output(stock, buyDay, sellDay);
}

// Task 3a: Recursive implementation of Big Theta(m * n) time dynamic programming algorithm for solving problem 1.

int max_profit(vector<vector<int>>& A, int stock, int day, vector<vector<int>>& memo) {
    if (day < 0) {
        return 0;
    }
    if (memo[stock][day] != -1) {
        return memo[stock][day];
    }

    int min_price = A[stock][0];
    for (int i = 1; i <= day; i++) {
        min_price = min(min_price, A[stock][i]);
    }
    int max_profit_current_day = A[stock][day] - min_price;

    memo[stock][day] = max(max_profit(A, stock, day - 1, memo), max_profit_current_day);

    return memo[stock][day];
}

void task3a(vector<vector<int>>& stocks)
{
    int m = stocks.size();
    int n = stocks[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    int max_profit_so_far = 0;
    int stock = 0, buyDay = 0, sellDay = 0;
    for (int i = 0; i < m; i++) {
        int temp_max_profit = max_profit(stocks, i, n - 1, memo);
        if (temp_max_profit > max_profit_so_far) {
            max_profit_so_far = temp_max_profit;
            stock = i;
        }
    }

    int min_price = stocks[stock][0];
    for (int i = 1; i < n; i++) {
        if (stocks[stock][i] - min_price == max_profit_so_far) {
            sellDay = i;
            break;
        }
        min_price = min(min_price, stocks[stock][i]);
    }
    for (int i = 0; i < sellDay; i++) {
        if (stocks[stock][i] == min_price) {
            buyDay = i;
            break;
        }
    }

    printProblem1Output(stock, buyDay, sellDay);
}

// Task 3b: Bottom-Up implementation of Big Theta(m * n) time dynamic programming algorithm for solving problem 1.

void task3b(vector<vector<int>>& stocks)
{
    int m = stocks.size();
    int n = stocks[0].size();

    vector<vector<int>> memo(m, vector<int>(n, 0));
    int max_profit_so_far = 0;
    int stock = 0, buyDay = 0, sellDay = 0;

    // Calculate the maximum profit for each stock
    for (int i = 0; i < m; i++) {
        int min_price = stocks[i][0];
        for (int j = 1; j < n; j++) {
            min_price = min(min_price, stocks[i][j]);
            memo[i][j] = max(memo[i][j - 1], stocks[i][j] - min_price);
        }
    }

    // Find the maximum profit among all stocks and the corresponding buy and sell days
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (memo[i][j] > max_profit_so_far) {
                max_profit_so_far = memo[i][j];
                stock = i;
                sellDay = j;
            }
        }
    }

    int min_price = stocks[stock][0];
    for (int i = 1; i < sellDay; i++) {
        if (stocks[stock][i] < min_price) {
            min_price = stocks[stock][i];
            buyDay = i;
        }
    }

    printProblem1Output(stock, buyDay, sellDay);
}

// Task 4: Big Theta(m * (n choose 2k)) time brute force algorithm for solving problem 2.
void task4(const vector<vector<int>>& stocks, const int k) {
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
        cout << get<0>(transaction) + 1 << " " << get<1>(transaction) + 1 << " " << get<2>(transaction) + 1 << endl;
    }
}

// Task 5: Big Theta(m * n^2 * k) time dynamic programming algorithm for solving problem 2.
vector<vector<int>> task5(vector<vector<int>>& prices, int m, int n, int k) {
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

// Task 6: Big Theta(m * n * k) time dynamic programming algorithm for solving problem 2.
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

    return max_profit;
}

// Task 7: Big Theta(m * 2^n) time brute force algorithm for solving problem 3.
int task7helper(vector<vector<int>>& A, int m, int n, int c, int current_day, int current_stock, int current_profit, vector<pair<int, pair<int, int>>>& transactions) {
    if (current_day >= n || current_stock >= m) {
        return current_profit;
    }

    int max_profit = current_profit;
    vector<pair<int, pair<int, int>>> best_transactions = transactions;

    // Sell current stock
    vector<pair<int, pair<int, int>>> sell_transactions = transactions;
    sell_transactions.push_back({current_stock, {current_day - c - 1, current_day}});
    int sell_profit = A[current_stock][current_day] + task7helper(A, m, n, c, current_day + c + 1, 0, current_profit + A[current_stock][current_day], sell_transactions);
    if (sell_profit > max_profit) {
        max_profit = sell_profit;
        best_transactions = sell_transactions;
    }

    // Move to next stock without selling
    vector<pair<int, pair<int, int>>> next_stock_transactions = transactions;
    int next_stock_profit = task7helper(A, m, n, c, current_day, current_stock + 1, current_profit, next_stock_transactions);
    if (next_stock_profit > max_profit) {
        max_profit = next_stock_profit;
        best_transactions = next_stock_transactions;
    }

    // Move to next day without selling
    vector<pair<int, pair<int, int>>> next_day_transactions = transactions;
    int next_day_profit = task7helper(A, m, n, c, current_day + 1, 0, current_profit, next_day_transactions);
    if (next_day_profit > max_profit) {
        max_profit = next_day_profit;
        best_transactions = next_day_transactions;
    }

    transactions = best_transactions;
    return max_profit;
}

int task7(vector<vector<int>>& A, int m, int n, int c, vector<pair<int, pair<int, int>>>& transactions) {
    return task7helper(A, m, n, c, 0, 0, 0, transactions);
}

// Task 8: Big Theta(m * n^2) time dynamic programming algorithm for solving problem 3.
vector<vector<int>> task8DPFinder(vector<vector<int>> &prices, int c) {
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

void task8(vector<vector<int>> &prices, vector<vector<int>> &dp,
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
        cout << stock + 1 << " " << buy_day + 1 << " " << sell_day + 1 << endl;
        day = sell_day + c;
      } else {
        day++;
      }
    }
  }
}

// Task 9: Big Theta(m * n) time dynamic programming algorithm for solving problem 3.
int task9(vector<vector<int>> &A, int c, vector<vector<int>> &transaction) {
    int m = A.size(), n = A[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    transaction.resize(m, vector<int>(2, -1));

    for (int i = 0; i < m; ++i) {
        deque<int> max_profit, transaction_idx;
        for (int j = 0; j < n; ++j) {
            if (j >= c) {
                max_profit.push_back(A[i][j - c] - A[i][j - c - 1]);
                transaction_idx.push_back(j - c);
            }

            if (j == 0 || A[i][j] > A[i][j - 1] + (max_profit.empty() ? 0 : max_profit.front())) {
                dp[i][j] = A[i][j];
                transaction[i] = {j, j};
            } else {
                dp[i][j] = A[i][j - 1] + max_profit.front();
                transaction[i] = {transaction_idx.front(), j};
            }

            if (!max_profit.empty() && max_profit.front() == A[i][j - c] - A[i][j - c - 1]) {
                max_profit.pop_front();
                transaction_idx.pop_front();
            }
        }
    }

    int max_profit_val = 0, best_stock = -1;
    for (int i = 0; i < m; ++i) {
        if (dp[i][n - 1] > max_profit_val) {
            max_profit_val = dp[i][n - 1];
            best_stock = i;
        }
    }

    cout << best_stock + 1 << " " << transaction[best_stock][0] + 1 << " " << transaction[best_stock][1] + 1 << endl;
    return max_profit_val;
}

/*==
MAIN
==*/

int main(int argc, char *argv[])
{
    // Checking input validity: number of arguments (should be 2 - the program name and the task number).
    if (argc != 2)
    {
        cout << "Invalid input; please enter \"./Stocks\" followed by the task number." << endl;
        return 0;
    }

    /*
        ==================
        COMMAND-LINE INPUT
        ==================
        The program will be executed with the program name (Stocks)
        followed by the task number, ranging from 1 to 9.
        - Note there is a special case with tasks 3a and 3b.

        The second element in the argv array (argv[1]) contains the task number.
    */
    string task = argv[1];
    
    // Checking input validity: task number (see above).
    if (validInput(task))
    {
        // Input is valid.

        /*
            =========
            VARIABLES
            =========
            Below are the variables used in the scope of this loop:
            - string input: user input per line, used with getline().
            - vector<vector<int>> stocks: a vector of integer vectors used to represent the stocks.
            - map<int, vector<int>> stockMap: a map of the stock values.
                KEY = STOCK #, VALUE = {DAY 1 PRICE, ..., DAY N PRICE}
            - int m: The number of stocks. Used for all problems.
            - int n: The number of days. Used for all problems.
            - int k: The number of transactions in a sequence. Used for problem 2.
            - int c: The number of days in a "cooldown period" after buying a stock. Used for problem 3.
        */
        string input;
        vector<vector<int>> stockVector;
        map<int, vector<int>> stockMap;
        int m = -1;
        int n = -1;
        int k = -1;
        int c = -1;
        bool input_is_file = isFile(task);
        string strippedFileName = task;
        int problem = -1;
        // Figure out if the input is user-based within the CLI or a text file.
        // True = File; False = CLI
        if (input_is_file)
        {
            // The input type is a file.
            cout << "Input is a file!" << endl;
            string fileName = task;
            string taskFromFile = isValidFile(task);

            if (taskFromFile != "-1")
            {
                cout << "File is valid!" << endl;
                // Parse the file.
            }
            else
            {
                cout << "Please format the file correctly and try again." << endl;
                return 0;
            }

            task = taskFromFile;
            problem = findProblem(task);
            cout << "This file is testing Task " << task << ". ";
            cout << "This task corresponds to Problem " << problem << ".\n\n";

            // Obtain the values from the user input.
            ifstream inputFile(fileName);

            // The first line always contains the task number.
            // In this function, it is irrelevant, but it must be parsed to get to the next line.
            string taskNum;
            getline(inputFile, taskNum);

            if (getValues(inputFile, problem, input, m, n, k, c, stockVector, stockMap))
            {
                cout << "Input successfully parsed; values obtained.\n\n";
            }
            else
            {
                cout << "Please try again from the start." << endl;
                return 0;
            }
            inputFile.close();
            // printValues(m, n, k, c, stockVector, stockMap);
        }
        else
        {
            // Identify associated problem.
            problem = findProblem(task);
            cout << "You have chosen Task " << task << ". ";
            cout << "This task corresponds to Problem " << problem << ".\n\n";
            cout << "Below is the expected input for your problem:\n";
            printProblemInstructions(problem);
            cout << "\nPlease input the corresponding information.\n";

            // Obtain the values from the user input.
            if (getValues(cin, problem, input, m, n, k, c, stockVector, stockMap))
            {
                cout << "Input successfully parsed; values obtained.\n\n";
            }
            else
            {
                cout << "Please try again from the start." << endl;
                return 0;
            }
        }

        /*
            =========
            ALGORITHM
            =========
            Now that the stock prices have been extracted and inputted into a vector as well as an ordered map,
            operations can begin upon them.

            These operations depend on the problem and task type.
            Functions exist to call upon each of the algorithms associated with a given task.

            Execution time will be measured with the "chrono" library.
        */

        cout << "The algorithm for task " << task << ", problem " << problem << " will now execute.\n";
        cout << "OUTPUT:\n\n";
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        if (task == "1")
        {
            start = high_resolution_clock::now();
            task1(stockVector, m, n);
            stop = high_resolution_clock::now();
        }
        else if (task == "2")
        {
            start = high_resolution_clock::now();
            task2(stockVector);
            stop = high_resolution_clock::now();
        }
        else if (task == "3a" || task == "3A")
        {
            start = high_resolution_clock::now();
            task3a(stockVector);
            stop = high_resolution_clock::now();
        }
        else if (task == "3b" || task == "3B")
        {
            start = high_resolution_clock::now();
            task3b(stockVector);
            stop = high_resolution_clock::now();
        }
        else if (task == "4")
        {
            start = high_resolution_clock::now();
            task4(stockVector, k);
            stop = high_resolution_clock::now();
        }
        else if (task == "5")
        {
            start = high_resolution_clock::now();
            vector<vector<int>> transactions = task5(stockVector, m, n, k);
            for (int i = 0; i < k; ++i)
            {
                int stock = transactions[i][0];
                int buy_day = transactions[i][1];
                int sell_day = transactions[i][2];
                cout << stock + 1 << " " << buy_day + 1 << " " << sell_day + 1 << endl;
            }
            stop = high_resolution_clock::now();
        }
        else if (task == "6")
        {
            int max_stock_idx = 0, buy_day = 0, sell_day = 0;
            start = high_resolution_clock::now();
            int max_profit = task6(stockVector, m, n, k, max_stock_idx, buy_day, sell_day);
            cout << max_stock_idx + 1 << " " << buy_day + 1 << " " << sell_day + 1 << endl;
            stop = high_resolution_clock::now();
        }
        else if (task == "7")
        {
            start = high_resolution_clock::now();
            vector<pair<int, pair<int, int>>> transactions;
            int maxProfit = task7(stockVector, m, n, c, transactions);
            for (const auto& t : transactions){
                cout << t.first + 1 << " " << t.second.first + 1 << " " << t.second.second << endl;
            }
            stop = high_resolution_clock::now();
        }
        else if (task == "8")
        {
            start = high_resolution_clock::now();
            vector<vector<int>> task8_dp = task8DPFinder(stockVector, c);
            task8(stockVector, task8_dp, c);
            stop = high_resolution_clock::now();
        }
        else if (task == "9")
        {
            vector<vector<int>> transaction;
            start = high_resolution_clock::now();
            int maxProfit = task9(stockVector, c, transaction);
            stop = high_resolution_clock::now();
        }

        cout << "\nExecution cycle complete.\n";
        if (input_is_file)
        {
            strippedFileName = strippedFileName.substr(0, strippedFileName.size() - 4);
            strippedFileName += "_time.txt";
            logTime(start, stop, task, strippedFileName);
        }
        else
        {
            logTime(start, stop, task, "CLI_time.txt");
        }

        /*
            ============
            END OF CYCLE
            ============
            At this point, the program has generated output.
            The user may now choose to test again with different values for the same task or a different one.
        */
    }
    else
    {
        // Input is invalid because the task does not exist; error message and program termination results.
        cout << "Invalid input; please enter a valid task number or a testing file ending with .txt." << endl;
        return 0;
    }

    return 0;
}