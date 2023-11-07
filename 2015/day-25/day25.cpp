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

const int MOD = 33554393;
const int MULT = 252533;

class Solution
{
private:
    fstream fin;
    int row, col;

    void parse()
    {
        string line;
        getline(this->fin, line);
        sscanf(line.c_str(), "To continue, please consult the code grid in the manual.  Enter the code at row %d, column %d.", &this->row, &this->col);
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        int idx = 1;
        int r = 1, c = 1;
        long long sol = 20151125;

        while (true)
        {
            for (int i = 0; i < idx; ++i)
            {
                if (r == this->row && c == this->col)
                    return sol;
                sol = (sol * MULT) % MOD;
                --r;
                ++c;
            }
            ++idx;
            r = idx;
            c = 1;
        }

        return sol;
    }
    auto part2() -> string { return "Not solved"; }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}