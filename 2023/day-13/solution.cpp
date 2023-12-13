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
    vector<vector<string>> patterns;

    void parse()
    {
        string line;
        vector<string> pattern;
        while (getline(this->fin, line))
        {
            if (line == "")
            {
                this->patterns.push_back(pattern);
                pattern.clear();
            }
            else
            {
                pattern.push_back(line);
            }
        }

        this->patterns.push_back(pattern);
    }

    auto horizontalMirroring(vector<string> pattern) -> long long
    {
        for (long long i = 0; i < pattern.size(); i++)
        {
            if (pattern[i] == pattern[i + 1])
            {

                long long ret = 1;
                for (int j = i + 1, k = i; k >= 0 && j < pattern.size(); --k, ++j)
                {
                    if (pattern[j] != pattern[k])
                    {
                        break;
                    }
                    else
                    {
                        ++ret;
                    }
                }

                if (ret != 0)
                    return ret;
            }
        }

        return 0LL;
    }

    auto verticalMirroring(vector<string> pattern) -> long long
    {
        vector<string> rotatedPattern;
        for (int i = 0; i < pattern.size(); i++)
        {
            string row = "";
            for (int j = pattern.size() - 1; j >= 0; j--)
            {
                row += pattern[j][i];
            }
            rotatedPattern.push_back(row);
        }

        return this->horizontalMirroring(rotatedPattern);
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> long long
    {
        long long sol = 0;
        int i = 0;
        for (auto pattern : this->patterns)
        {
            ++i;
            long long vm = this->verticalMirroring(pattern);
            long long hm = this->horizontalMirroring(pattern);
            if (vm != 0)
                sol += vm;
            else
                sol += 100 * hm;

            if (vm == 0 && hm == 0)
                cout << "Not found: " << i << endl;
        }

        return sol;
    }
    auto part2() -> string { return "Not solved"; }
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
    // cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}