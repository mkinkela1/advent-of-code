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
    pair<int, int> range;

    void parse()
    {
        string line;
        getline(this->fin, line);
        vector<string> parts = split(line, "-");

        if (parts.size() != 2)
            return;

        this->range = make_pair(stoi(parts[0]), stoi(parts[1]));
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
        int count = 0;
        for (int i = this->range.first; i <= this->range.second; i++)
        {
            string s = to_string(i);
            bool hasDouble = false;
            bool isIncreasing = true;
            for (int j = 0; j < s.size() - 1; j++)
            {
                if (s[j] == s[j + 1])
                    hasDouble = true;
                if (s[j] > s[j + 1])
                    isIncreasing = false;
            }
            if (hasDouble && isIncreasing)
                count++;
        }
        return count;
    }
    auto part2() -> int
    {
        int count = 0;
        for (int i = this->range.first; i <= this->range.second; i++)
        {
            string s = to_string(i);
            bool hasDouble = false;
            bool isIncreasing = true;
            for (int j = 0; j < s.size() - 1; j++)
            {
                if (s[j] == s[j + 1] && (j == 0 || s[j] != s[j - 1]) && (j == s.size() - 2 || s[j] != s[j + 2]))
                    hasDouble = true;
                if (s[j] > s[j + 1])
                    isIncreasing = false;
            }
            if (hasDouble && isIncreasing)
                count++;
        }
        return count;
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