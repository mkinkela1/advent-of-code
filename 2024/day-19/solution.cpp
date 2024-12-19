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
    vector<string> patterns;
    vector<string> designs;

    void parse()
    {
        string line;
        getline(this->fin, line);
        this->patterns = split(line, ", ");

        getline(this->fin, line);

        while (getline(this->fin, line))
        {
            this->designs.push_back(line);
        }
    }

    bool canCreate(string design, vector<string> patterns)
    {
        int n = design.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;

        for (int i = 1; i <= n; i++)
        {
            for (string pattern : patterns)
            {
                int len = pattern.size();
                if (i >= len && design.substr(i - len, len) == pattern)
                {
                    dp[i] = dp[i] || dp[i - len];
                }
            }
        }

        return dp[n];
    }

    uint64_t waysToCrate(string design, vector<string> patterns)
    {
        int n = design.size();
        vector<uint64_t> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (string pattern : patterns)
            {
                int len = pattern.size();
                if (i >= len && design.substr(i - len, len) == pattern)
                {
                    dp[i] += dp[i - len];
                }
            }
        }

        return dp[n];
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
        int sol = 0;
        for (string design : this->designs)
            sol += this->canCreate(design, this->patterns);

        return sol;
    }
    auto part2() -> uint64_t
    {
        uint64_t sol = 0;
        for (string design : this->designs)
            sol += this->waysToCrate(design, this->patterns);

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