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
    vector<tuple<string, long long unsigned>> instructions;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            if (line.empty())
                continue;

            vector<string> tokens = split(line, " ");

            long long unsigned arg = stoull(tokens[1]);
            this->instructions.push_back(make_tuple(tokens[0], arg));
        }
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long unsigned
    {
        long long unsigned depth = 0LLU;
        long long unsigned horizontal = 0LLU;

        for (auto instruction : this->instructions)
        {
            string op = get<0>(instruction);
            long long unsigned arg = get<1>(instruction);

            if (op == "forward")
            {
                horizontal += arg;
            }
            else if (op == "down")
            {
                depth += arg;
            }
            else if (op == "up")
            {
                depth -= arg;
            }
        }

        return depth * horizontal;
    }
    auto part2() -> long long unsigned
    {
        long long unsigned depth = 0LLU;
        long long unsigned horizontal = 0LLU;
        long long unsigned aim = 0LLU;

        for (auto instruction : this->instructions)
        {
            string op = get<0>(instruction);
            long long unsigned arg = get<1>(instruction);

            if (op == "forward")
            {
                horizontal += arg;
                depth += aim * arg;
            }
            else if (op == "down")
            {
                aim += arg;
            }
            else if (op == "up")
            {
                aim -= arg;
            }
        }

        return depth * horizontal;
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