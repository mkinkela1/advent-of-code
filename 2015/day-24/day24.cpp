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
    vector<long long> weights;
    int sum = 0;

    void parse()
    {
        string line;
        long long weight;
        while (getline(this->fin, line))
        {
            weight = stoi(line);
            this->weights.push_back(weight);
            this->sum += weight;
        }
    }

    auto solve(int target) -> long long
    {
        int n = this->weights.size();
        long long quantumEntanglement = __LONG_LONG_MAX__;
        int minUsed = n;
        for (int i = 0; i < (1 << n); ++i)
        {
            int used = __builtin_popcount(i);

            if (used > minUsed)
                continue;

            long long prod = 1;
            int sum = 0;
            for (int j = 0; j < n; ++j)
            {
                if (i & (1 << j))
                {
                    prod *= (long long)this->weights[j];
                    sum += this->weights[j];
                }
            }
            if (sum == target)
            {
                if (used < minUsed)
                {
                    minUsed = used;
                    quantumEntanglement = prod;
                }
                else if (used == minUsed)
                {
                    quantumEntanglement = min(quantumEntanglement, prod);
                }
            }
        }

        return quantumEntanglement;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> long long { return this->solve(this->sum / 3); }
    auto part2() -> long long { return this->solve(this->sum / 4); }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}