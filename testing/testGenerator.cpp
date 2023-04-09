#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

string task, m, n, c, k;
int problem;
int seed = time(0);

void writeFile(string& fileName)
{
    srand(seed);
    ofstream file(fileName);

    if (!file.is_open())
    {
        cout << "Error opening output file!" << endl;
    }

    file << task << endl;
    if (problem == 2)
    {
        file << k << endl;
    }
    else if (problem == 3)
    {
        file << c << endl;
    }
    file << m << " " << n << endl;

    for (int i = 0; i < stoi(m); i++)
    {
        bool first = true; // flag variable to keep track of first number

        for (int j = 0; j < stoi(n); j++)
        {
            // depending on the problem, the value can be different.
            // problem 1: 0 <= A[i][j] < 10000
            if (problem == 1)
            {
                if (!first)
                { // write a space character before every number except the first
                    file << " ";
                }
                file << (rand() % 10000);
                first = false; // set flag variable to false after writing the first number
            }
            else if (problem == 2 || problem == 3)
            {
                // problems 2 & 3: 0 <= A[i][j] < 1000
                if (!first)
                { // write a space character before every number except the first
                    file << " ";
                }
                file << (rand() % 1000);
                first = false; // set flag variable to false after writing the first number
            }
        }
        file << endl;
    }

    file.close();

    cout << "Output file generated successfully." << endl;
}

int main()
{
    int seed = time(0);
    srand(seed);

    cout << "Enter problem:\n";
    cin >> problem;

    cout << "m random? Enter Y or N.\n";
    cin >> m;
    if (m == "Y")
    {
        // m is random. generate 1 <= m < 100
        int minM = 1;
        int maxM = 99;
        int randomM = (rand() % (maxM - minM + 1)) + minM;
        m = to_string(randomM);
    }
    else
    {
        cout << "Enter m: ";
        cin >> m;
    }

    cout << "n random? Enter Y or N.\n";
    cin >> n;
    if (n == "Y")
    {
        // n is random. depending on the problem, generate:
        if (problem == 1)
        {
            // generate 1 <= n < 10^5
            int minN = 1;
            int maxN = 99999;
            int randomN = (rand() % (maxN - minN + 1)) + minN;
            n = to_string(randomN);
        }
        else
        {
            // generate 1 <= n < 1000
            int minN = 1;
            int maxN = 999;
            int randomN = (rand() % (maxN - minN + 1)) + minN;
            n = to_string(randomN);
        }
    }
    else
    {
        cout << "Enter n: ";
        cin >> n;
    }

    // depending on problem, ask for input on c and k.
    if (problem == 2)
    {
        cout << "k random? Enter Y or N.\n";
        cin >> k;
        if (k == "Y")
        {
            // k is random. generate 1 <= k < 100
            int kValue = rand() % 99 + 1; // generate random number from 1 to 99
            k = to_string(kValue);
        }
        else
        {
            cout << "Enter k: ";
            cin >> k;
        }
    }
    else if (problem == 3)
    {
        cout << "c random? Enter Y or N.\n";
        cin >> c;
        if (c == "Y")
        {
            // c is random. generate: 1 <= c < 100
            int cValue = rand() % 99 + 1; // generate random number from 1 to 99
            c = to_string(cValue);
        }
        else
        {
            cout << "Enter c: ";
            cin >> c;
        }
    }

    string fileName = "_m" + m + "_n" + n;
    
    if (problem == 2)
    {
        fileName += "_k" + k;
    }
    else if (problem == 3)
    {
        fileName += "_c" + c;
    }

    fileName += "_test.txt";
    string tempFileName = fileName;

    if (problem == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == 0)
            {
                task = "1";
            }
            else if (i == 1)
            {
                task = "2";
            }
            else if (i == 2)
            {
                task = "3a";
            }
            else if (i == 3)
            {
                task = "3b";
            }
            fileName = "t" + task + fileName;
            writeFile(fileName);
            fileName = tempFileName;
        }
    }
    else if (problem == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
            {
                task = "4";
            }
            else if (i == 1)
            {
                task = "5";
            }
            else if (i == 2)
            {
                task = "6";
            }
            fileName = "t" + task + fileName;
            writeFile(fileName);
            fileName = tempFileName;
        }
    }
    else if (problem == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == 0)
            {
                task = "7";
            }
            else if (i == 1)
            {
                task = "8";
            }
            else if (i == 2)
            {
                task = "9";
            }
            fileName = "t" + task + fileName;
            writeFile(fileName);
            fileName = tempFileName;
        }
    }

    return 0;
}
