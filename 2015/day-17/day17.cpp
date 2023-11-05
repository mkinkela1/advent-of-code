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
    vector<int> containers;

    void parse()
    {
        string line;
        int containerSize;
        while (getline(this->fin, line))
        {
            sscanf(line.c_str(), "%d", &containerSize);
            this->containers.push_back(containerSize);
        }
    }

    auto solveTotalCombinations(int liters) -> int
    {
        int sol = 0;

        for (int i = 0; i <= (1 << this->containers.size()); ++i)
        {
            int sum = 0;
            for (int j = 0; j < this->containers.size(); ++j)
                if (i & (1 << j))
                    sum += this->containers[j];
            if (sum == liters)
                ++sol;
        }

        return sol;
    }

    auto solveMaxSpareCombinations(int liters) -> int
    {
        int sol = 0;
        int minContainers = this->containers.size();

        for (int i = 0; i <= (1 << this->containers.size()); ++i)
        {
            int sum = 0;
            for (int j = 0; j < this->containers.size(); ++j)
                if (i & (1 << j))
                    sum += this->containers[j];
            if (sum == liters)
            {
                int numContainers = __builtin_popcount(i);
                if (numContainers < minContainers)
                {
                    minContainers = numContainers;
                    sol = 1;
                }
                else if (numContainers == minContainers)
                {
                    ++sol;
                }
            }
        }

        return sol;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int { return this->solveTotalCombinations(150); }
    auto part2() -> int { return this->solveMaxSpareCombinations(150); }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}