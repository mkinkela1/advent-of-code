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
    vector<uint64_t> mass;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->mass.push_back(stoull(line));
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
        uint64_t sum = 0;
        for (auto m : this->mass)
        {
            sum += m / 3 - 2;
        }
        return sum;
    }
    auto part2() -> uint64_t
    {
        uint64_t sum = 0;
        for (auto m : this->mass)
        {
            int64_t fuel = m / 3 - 2;
            while (fuel > 0)
            {
                sum += fuel;
                fuel = fuel / 3 - 2;
            }
        }
        return sum;
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