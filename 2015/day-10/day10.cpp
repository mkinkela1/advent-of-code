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

using namespace std;

class Solution
{
private:
    fstream fin;
    string input;

    void parse()
    {
        getline(this->fin, this->input);
    }

    auto solve(int times) -> int
    {
        string current = this->input;

        for (int i = 0; i < times; ++i)
        {
            string next = "";
            int count = 1;
            for (int j = 1; j < current.size(); ++j)
            {
                if (current[j] == current[j - 1])
                {
                    count++;
                }
                else
                {
                    next += to_string(count) + current[j - 1];
                    count = 1;
                }
            }
            next += to_string(count) + current[current.size() - 1];
            current = next;
        }

        return current.size();
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        return this->solve(40);
    }
    auto part2() -> int { return this->solve(50); }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}