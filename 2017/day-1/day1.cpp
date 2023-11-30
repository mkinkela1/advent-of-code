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
    string number;

    void parse()
    {
        getline(this->fin, this->number);
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> int
    {
        int sum = 0;

        for (int i = 0; i < this->number.size(); i++)
            if (this->number[i] == this->number[(i + 1) % this->number.size()])
                sum += this->number[i] - '0';

        return sum;
    }
    auto part2() -> int
    {
        int sum = 0;

        for (int i = 0; i < this->number.size(); i++)
            if (this->number[i] == this->number[(i + this->number.size() / 2) % this->number.size()])
                sum += this->number[i] - '0';

        return sum;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}