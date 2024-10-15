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
#include <numeric>
#include "../../utils/split.h"

using namespace std;

class Solution
{
private:
    fstream fin;
    uint64_t timestamp;
    vector<uint64_t> data;

    void parse()
    {
        string line;
        getline(this->fin, line);

        getline(this->fin, line);
        vector<string> tokens = split(line, ",");
        for (auto token : tokens)
        {
            if (token == "x")
            {
                this->data.push_back(0);
            }
            else
            {
                this->data.push_back(stoll(token));
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

    auto part1() -> uint64_t
    {
        uint64_t min = UINT64_MAX;
        uint64_t bus = 0;
        for (auto d : this->data)
        {
            if (d == 0)
            {
                continue;
            }
            uint64_t next = (this->timestamp / d + 1) * d;
            if (next < min)
            {
                min = next;
                bus = d;
            }
        }
        return bus * (min - this->timestamp);
    }
    auto part2() -> uint64_t
    {
        uint64_t timestamp = 0;
        uint64_t step = this->data[0];
        for (int i = 1; i < this->data.size(); i++)
        {
            if (this->data[i] == 0)
            {
                continue;
            }
            while ((timestamp + i) % this->data[i] != 0)
            {
                timestamp += step;
            }
            step *= this->data[i];
        }
        return timestamp;
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