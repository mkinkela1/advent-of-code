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
    vector<pair<int, int>> instructions;
    vector<vector<int>> updates;

    void parse()
    {
        string line;
        bool isBeforeNewline = true;
        while (getline(this->fin, line))
        {
            if (line.empty())
            {
                isBeforeNewline = false;
                continue;
            }

            if (isBeforeNewline)
            {
                vector<string> parts = split(line, "|");
                this->instructions.push_back({stoi(parts[0]), stoi(parts[1])});
            }
            else
            {
                vector<string> parts = split(line, ",");
                vector<int> nums = {};
                for (string part : parts)
                {
                    nums.push_back(stoi(part));
                }

                this->updates.push_back(nums);
            }
        }
    }

    bool followsRule(int a, int b)
    {
        for (auto instruction : this->instructions)
        {
            if (instruction.first == b && instruction.second == a)
            {
                return false;
            }
        }

        return true;
    }

    bool isSorted(vector<int> arr)
    {
        for (int i = 0; i < arr.size() - 1; i++)
        {
            for (int j = i + 1; j < arr.size(); j++)
            {
                if (!this->followsRule(arr[i], arr[j]))
                {
                    return false;
                }
            }
        }

        return true;
    }

    void sort(vector<int> &arr)
    {
        while (!this->isSorted(arr))
        {
            for (int i = 0; i < arr.size() - 1; i++)
            {
                for (int j = i + 1; j < arr.size(); j++)
                {
                    if (!this->followsRule(arr[i], arr[j]))
                    {
                        swap(arr[i], arr[j]);
                    }
                }
            }
        }
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

        for (auto update : this->updates)
        {
            if (this->isSorted(update))
            {
                sol += update[update.size() / 2];
            }
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        for (auto update : this->updates)
        {
            if (this->isSorted(update))
                continue;

            vector<int> sorted = update;
            this->sort(sorted);

            sol += sorted[sorted.size() / 2];
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