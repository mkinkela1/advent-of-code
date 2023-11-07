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

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
        }
    }

public:
    Solution()
    {
        this->fin.open("input.txt", ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> int
    {
        int sol = 0;
        for (auto line : this->input)
        {
            int i = 0;
            int tmp = 0;
            while (i < line.size())
            {
                if (line[i] != '"')
                    ++tmp;
                if (line[i] == '\\')
                {
                    if (line[i + 1] == 'x')
                    {
                        i += 4;
                    }
                    else
                    {
                        i += 2;
                    }
                }
                else
                {
                    i++;
                }
            }
            sol += line.size() - tmp;
        }
        return sol;
    }

    auto part2() -> int
    {
        int sol = 0;
        for (auto line : this->input)
        {
            int i = 0;
            int tmp = 0;
            while (i < line.size())
            {
                if (line[i] == '"' || line[i] == '\\')
                    tmp++;
                i++;
            }
            sol += tmp + 2;
        }

        return sol;
    };
};

auto main() -> int
{

    Solution aoc;

    cout << "Part 1: " << aoc.part1() << endl;
    cout << "Part 2: " << aoc.part2() << endl;

    return 0;
}