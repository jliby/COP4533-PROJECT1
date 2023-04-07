#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

bool validInput(string& input)
{
    /*
        Input is considered valid if the task number is within range.
        Acceptable input includes: 1, 2, 3a or 3A, 3b or 3B, 4, 5, 6, 7, 8, 9.
        All other input is invalid, as there are no tasks associated with it.
    */

    // If input is not valid, return false.
    if (input == "1" || input == "2" || input == "3a" || input == "3A" ||
        input == "3b" || input == "3B" || input == "4" || input == "5" ||
        input == "6" || input == "7" || input == "8" || input == "9")
        {
            return true;
        }

    // If input is valid, return true.
    return false;
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

bool getValues(int &problemNumber, string &inputString, int &m, int &n, int &k, int &c, vector<vector<int>> &stock_v, map<int, vector<int>> &stock_m)
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
        getline(cin, inputString);
        extractMN(inputString, m, n);

        // Lines 2 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(cin, inputString);
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
        getline(cin, inputString);
        k = stoi(inputString);

        // Line 2: m & n
        getline(cin, inputString);
        extractMN(inputString, m, n);

        // Lines 3 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(cin, inputString);
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
        getline(cin, inputString);
        c = stoi(inputString);

        // Line 2: m & n
        getline(cin, inputString);
        extractMN(inputString, m, n);

        // Lines 3 to m: numbers.
        for (int i = 0; i < m; i++)
        {
            getline(cin, inputString);
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

        // Enter a while(true) loop to keep program execution going if the user wishes to change their input without exiting the program again.
        while(true)
        {
            // Identify associated problem.
            int problem = findProblem(task);
            cout << "You have chosen Task " << task << ". ";
            cout << "This task corresponds to Problem " << problem << ".\n\n";
            cout << "Below is the expected input for your problem:\n";
            printProblemInstructions(problem);
            cout << "\nPlease input the corresponding information.\n";

            // Obtain the values from the user input.
            if (getValues(problem, input, m, n, k, c, stockVector, stockMap))
            {
                cout << "Input successfully parsed; values obtained.\n\n";
            }
            else
            {
                cout << "Please try again from the start." << endl;
                return 0;
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

            cout << "The algorithm for task " << task << ", problem " << problem << " will now execute.\n\n";

            if (task == "1")
            {
                cout << "PLACEHOLDER: TASK 1 OUTPUT." << endl;
            }
            else if (task == "2")
            {
                cout << "PLACEHOLDER: TASK 2 OUTPUT." << endl;
            }
            else if (task == "3a" || task == "3A")
            {
                cout << "PLACEHOLDER: TASK 3a OUTPUT." << endl;
            }
            else if (task == "3b" || task == "3B")
            {
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
            cout << "If you would like to restart the program, enter \"YES\". If not, enter \"EXIT\".\n";
            getline(cin, input);
            if (input == "YES")
            {
                resetValues(m, n, k, c, stockVector, stockMap);
                cout << "Please enter a task number.\n";
                getline(cin, input);
                task = input;
                if (validInput(task)) {
                    continue;
                }
                else
                {
                    cout << "Invalid task number; please try again from the start." << endl;
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
        cout << "Invalid input; please enter a valid task number." << endl;
        return 0;
    }

    return 0;
}