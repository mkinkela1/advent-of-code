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
    vector<string> input;
    vector<unordered_map<char, int>> freqs;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
            this->input.push_back(line);

        this->freqs.resize(this->input[0].size());
        for (auto line : this->input)
            for (int i = 0; i < line.size(); i++)
                this->freqs[i][line[i]]++;
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
    }

    auto part1() -> string
    {
        string sol = "";

        for (auto freq : freqs)
        {
            char maxChar = ' ';
            int maxFreq = 0;
            for (auto [c, f] : freq)
            {
                if (f > maxFreq)
                {
                    maxFreq = f;
                    maxChar = c;
                }
            }
            sol += maxChar;
        }

        return sol;
    }
    auto part2() -> string
    {
        string sol = "";

        for (auto freq : freqs)
        {
            char minChar = ' ';
            int minFreq = INT_MAX;
            for (auto [c, f] : freq)
            {
                if (f < minFreq)
                {
                    minFreq = f;
                    minChar = c;
                }
            }
            sol += minChar;
        }

        return sol;
    }
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}