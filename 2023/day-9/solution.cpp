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
    vector<vector<int>> histories;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> tokens = split(line, " ");
            vector<int> history;
            for (auto token : tokens)
            {
                if (token != "")
                    history.push_back(stoi(token));
            }

            this->histories.push_back(history);
        }
    }

    auto predictFuture(vector<int> history) -> int
    {
        vector<vector<int>> differences = {history};
        int step = 0;

        while (true)
        {
            vector<int> last;
            bool allZero = true;
            for (int i = 1; i < differences[step].size(); i++)
            {
                int diff = differences[step][i] - differences[step][i - 1];
                if (diff != 0)
                    allZero = false;
                last.push_back(diff);
            }

            differences.push_back(last);
            if (allZero)
                break;
            ++step;
        }

        int sol = 0;
        for (int i = step; i >= 0; i--)
        {
            sol += differences[i].back();
        }

        return sol;
    }

    auto predictPast(vector<int> history) -> int
    {
        vector<vector<int>> differences = {history};
        int step = 0;

        while (true)
        {
            vector<int> last;
            bool allZero = true;
            for (int i = 1; i < differences[step].size(); i++)
            {
                int diff = differences[step][i] - differences[step][i - 1];
                if (diff != 0)
                    allZero = false;
                last.push_back(diff);
            }

            differences.push_back(last);
            if (allZero)
                break;
            ++step;
        }

        int sol = 0;
        for (int i = step; i >= 0; i--)
        {
            sol = differences[i].front() - sol;
        }

        return sol;
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

        for (auto history : this->histories)
        {
            sol += this->predictFuture(history);
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        for (auto history : this->histories)
        {
            sol += this->predictPast(history);
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