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
    vector<uint64_t> data;
    map<pair<uint64_t, int>, uint64_t> cache;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            vector<string> row = split(line, " ");
            for (auto x : row)
            {
                this->data.push_back(stoll(x, NULL, 10));
            }
        }
    }

    uint64_t rec(uint64_t num, int blinks)
    {
        if (blinks == 0)
            return 1;

        uint64_t &ref = this->cache[{num, blinks}];

        if (ref != 0)
            return this->cache[{num, blinks}];

        if (num == 0)
            return ref = rec(1, blinks - 1);

        string str = to_string(num);
        if (str.size() % 2 == 0)
        {
            string first = str.substr(0, str.size() / 2);
            string second = str.substr(str.size() / 2, str.size() / 2);
            return ref = rec(stoll(first, NULL, 10), blinks - 1) + rec(stoll(second, NULL, 10), blinks - 1);
        }
        else
        {
            return ref = rec(num * 2024, blinks - 1);
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
        uint64_t sol = 0;
        for (auto x : this->data)
        {
            sol += this->rec(x, 25);
        }

        return sol;
    }
    auto part2() -> uint64_t
    {
        uint64_t sol = 0ULL;
        for (auto x : this->data)
        {
            sol += this->rec(x, 75);
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