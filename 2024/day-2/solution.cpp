#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <tuple>
#include <map>
#include <queue>
#include <stack>
#include <array>
#include <unordered_map>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<vector<int>> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> temp = split(line, " ");
            vector<int> temp2;
            for (auto &x : temp)
            {
                temp2.push_back(stoi(x));
            }
            this->data.push_back(temp2);
        }
    }

    bool isSafe(vector<int> &report)
    {
        int isInc = report[0] < report[1];

        for (int i = 1; i < report.size(); i++)
        {
            if (isInc && report[i - 1] > report[i])
            {
                return 0;
            }

            if (!isInc && report[i - 1] < report[i])
            {
                return 0;
            }

            long diff = report[i - 1] - report[i];

            if (abs(diff) < 1 || abs(diff) > 3)
            {
                return 0;
            }
        }
        return 1;
    }

    bool isSafeWithRemoving(vector<int> &report)
    {
        if (this->isSafe((report)))
            return 1;

        for (int i = 0; i < report.size(); i++)
        {
            vector<int> temp = report;
            temp.erase(temp.begin() + i);
            if (this->isSafe(temp))
                return 1;
        }

        return 0;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sol = 0;
        for (auto &report : this->data)
        {
            sol += isSafe(report);
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;
        for (auto &report : this->data)
        {
            sol += isSafeWithRemoving(report);
        }

        return sol;
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1() << endl;
    cout << "Part 1: " << aoc.part1() << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}