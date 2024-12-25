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

    void parse()
    {
        string line;
        getline(this->fin, line);
        vector<string> parts = split(line, ",");

        for (auto &part : parts)
            this->data.push_back(stoull(part));
    }

    uint64_t calc(vector<uint64_t> data, uint64_t a, uint64_t b)
    {
        data[1] = a;
        data[2] = b;

        for (int i = 0; i < data.size(); i += 4)
        {
            if (data[i] == 99)
                break;

            if (i + 3 >= data.size())
                break;
            if (data[i + 1] >= data.size() || data[i + 2] >= data.size() || data[i + 3] >= data.size())
                break;

            uint64_t a = data[data[i + 1]];
            uint64_t b = data[data[i + 2]];
            uint64_t c = data[i + 3];

            if (data[i] == 1)
                data[c] = a + b;
            else if (data[i] == 2)
                data[c] = a * b;
        }

        return data[0];
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
        return this->calc(this->data, 12, 2);
    }
    auto part2() -> uint64_t
    {
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 100; j++)
                if (this->calc(this->data, i, j) == 19690720)
                    return 100 * i + j;

        return -1;
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
    // cout << "Part 2 test: " << test2.part2() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}