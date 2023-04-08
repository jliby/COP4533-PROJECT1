#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

/*=============
INPUT FUNCTIONS
=============*/
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

int isValidFile(string& fileName)
{
    int result = -1;
    ifstream inputFile(fileName);

    string taskNum;
    inputFile >> taskNum;
    inputFile.close();

    if (validInput(taskNum))
    {
        return stoi(taskNum);
    }

    cout << "Error: the task specified in the file does not exist." << endl;
    return result;
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

void task3a(vector<vector<int>>& stocks, int& m, int& n)
{
    vector<vector<int>> memo(m, vector<int>(n, -1));
    int max_profit_so_far = 0;
    int stock = 0, buyDay = 0, sellDay = 0;
    for (int i = 0; i < m; i++) {
        int temp_buyDay = 0, temp_sellDay = 0;
        int temp_max_profit = max_profit(stocks, i, 0, memo, temp_buyDay, temp_sellDay);
        if (temp_max_profit > max_profit_so_far) {
            max_profit_so_far = temp_max_profit;
            stock = i;
            buyDay = temp_buyDay;
            sellDay = temp_sellDay;
        }
    }

    printProblem1Output(stock, buyDay, sellDay);
}

// Task 3b: Bottom-Up implementation of Big Theta(m * n) time dynamic programming algorithm for solving problem 1.
void task3b(vector<vector<int>>& stocks, int& m, int& n)
{

    vector<vector<int>> memo(m, vector<int>(n, 0));
    int stock = 0, buyDay = 0, sellDay = 0;
    int max_profit_so_far = 0;

    // Calculate the maximum profit for the last day for each stock
    for (int i = 0; i < m; i++) {
        memo[i][n-1] = 0;
        for (int j = n-2; j >= 0; j--) {
            memo[i][j] = max(0, stocks[i][j+1] - stocks[i][j] + memo[i][j+1]);
        }
    }

    // Calculate the maximum profit for each stock and each day
    for (int j = n-2; j >= 0; j--) {
        for (int i = 0; i < m; i++) {
            int future_profit = (i == m-1) ? 0 : memo[i+1][j];
            memo[i][j] = max(memo[i][j], future_profit);
            if (stocks[i][j] < stocks[stock][buyDay]) {
                stock = i;
                buyDay = j;
            } else if (stocks[i][j] - stocks[stock][buyDay] + memo[i][j] > max_profit_so_far) {
                sellDay = j;
                max_profit_so_far = stocks[i][j] - stocks[stock][buyDay] + memo[i][j];
            }
        }
    }

    cout << "STOCK: " << stock+1 << " BUY DAY: " << buyDay+1 << " SELL DAY: " << sellDay+1 << endl;
    cout << "PLACEHOLDER FOR TASK 3b\n";
}

// Task 4: Big Theta(m * (n choose 2k)) time brute force algorithm for solving problem 2.
void task4(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 4\n";
}

// Task 5: Big Theta(m * n^2 * k) time dynamic programming algorithm for solving problem 2.
void task5(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 5\n";
}

// Task 6: Big Theta(m * n * k) time dynamic programming algorithm for solving problem 2.
void task6(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 6\n";
}

// Task 7: Big Theta(m * 2^n) time brute force algorithm for solving problem 3.
void task7(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 7\n";
}

// Task 8: Big Theta(m * n^2) time dynamic programming algorithm for solving problem 3.
void task8(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 8\n";
}

// Task 9: Big Theta(m * n) time dynamic programming algorithm for solving problem 3.
void task9(vector<vector<int>>& stocks)
{
    cout << "PLACEHOLDER FOR TASK 9\n";
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
        
        // (implicit else) - the input type is the CLI.

        // Enter a while(true) loop to keep program execution going if the user wishes to change their input without exiting the program again.
        while(true)
        {
            int problem = -1;
            // Figure out if the input is user-based within the CLI or a text file.
                // True = File; False = CLI
            bool input_is_file = isFile(task);
            if (input_is_file)
            {
                // The input type is a file.
                cout << "Input is a file!" << endl;
                string fileName = task;
                int taskFromFile = isValidFile(task);

                if (taskFromFile != -1) {
                    cout << "File is valid!" << endl;
                    
                    // Parse the file.

                }
                else
                {
                    cout << "Please format the file correctly and try again." << endl;
                    return 0;
                }

                task = to_string(taskFromFile);
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
            */

            cout << "The algorithm for task " << task << ", problem " << problem << " will now execute.\n";
            cout << "OUTPUT:\n\n";

            if (task == "1")
            {
                task1(stockVector, m, n);
            }
            else if (task == "2")
            {
                task2(stockVector);
            }
            else if (task == "3a" || task == "3A")
            {
                task3a(stockVector, m, n);
            }
            else if (task == "3b" || task == "3B")
            {
                task3b(stockVector, m, n);
                cout << "PLACEHOLDER: TASK 3b OUTPUT." << endl;
            }
            else if (task == "4")
            {
                cout << "PLACEHOLDER: TASK 4 OUTPUT." << endl;
            }
            else if (task == "5")
            {
                cout << "PLACEHOLDER: TASK 5 OUTPUT." << endl;
            }
            else if (task == "6")
            {
                cout << "PLACEHOLDER: TASK 6 OUTPUT." << endl;
            }
            else if (task == "7")
            {
                cout << "PLACEHOLDER: TASK 7 OUTPUT." << endl;
            }
            else if (task == "8")
            {
                cout << "PLACEHOLDER: TASK 8 OUTPUT." << endl;
            }
            else if (task == "9")
            {
                cout << "PLACEHOLDER: TASK 9 OUTPUT." << endl;
            }

            cout << "\nExecution cycle complete.\n";
            // printValues(m, n, k, c, stockVector, stockMap);

            /*
                ============
                END OF CYCLE
                ============
                At this point, the program has generated output.
                The user may now choose to test again with different values for the same task or a different one.
            */
            cout << "If you would like to restart the program, enter \"YES\". If not, enter \"EXIT\".\n\n";
            getline(cin, input);
            if (input == "YES")
            {
                resetValues(m, n, k, c, stockVector, stockMap);
                cout << "Please enter a task number or file name.\n\n";
                getline(cin, input);
                task = input;
                if (validInput(task)) {
                    continue;
                }
                else
                {
                    cout << "Invalid task number or file name; please try again from the start." << endl;
                    break;
                }
            }
            else if (input == "EXIT")
            {
                cout << "Goodbye!\n";
                break;
            }
            else
            {
                cout << "Invalid input; please try again from the start." << endl;
                break;
            }
        }
    }
    else
    {
        // Input is invalid because the task does not exist; error message and program termination results.
        cout << "Invalid input; please enter a valid task number or a testing file ending with .txt." << endl;
        return 0;
    }

    return 0;
}