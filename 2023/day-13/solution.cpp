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
                bool found = true;
                long long ret = 0;
                for (int j = i + 1, k = i; k >= 0 && j < pattern.size(); --k, ++j, ++ret)
                {
                    if (pattern[j] != pattern[k])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                    return i + 1;
            }
        }

        return 0LL;
    }

    auto verticalMirroring(vector<string> pattern) -> long long
    {
        vector<string> rotatedPattern;
        for (int i = 0; i < pattern[0].size(); i++)
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

    auto getMirrorsWithMistake(vector<string> pattern) -> pair<long long, long long>
    {
        long long prevHm = this->horizontalMirroring(pattern);
        long long prevVm = this->verticalMirroring(pattern);

        for (int i = 0; i < pattern.size(); i++)
        {
            for (int j = 0; j < pattern[i].size(); j++)
            {
                vector<string> newPattern = pattern;
                newPattern[i][j] = pattern[i][j] == '#' ? '.' : '#';

                long long hm = this->horizontalMirroring(newPattern);
                long long vm = this->verticalMirroring(newPattern);

                if (hm == 0 && vm == 0)
                    continue;
                if (vm == prevVm && hm != prevHm)
                    return {0, hm};
                if (hm == prevHm && vm != prevVm)
                    return {vm, 0};
            }
        }

        return {0, 0};
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
            sol += vm;
            sol += 100 * hm;
        }

        return sol;
    }
    auto part2() -> long long
    {
        long long sol = 0;
        for (auto pattern : this->patterns)
        {
            auto [vm, hm] = this->getMirrorsWithMistake(pattern);
            sol += vm;
            sol += 100 * hm;
        }

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