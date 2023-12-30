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
    vector<int> depths;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            if (line.empty())
                continue;
            this->depths.push_back(stoi(line));
        }
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

        for (int i = 1; i < this->depths.size(); i++)
        {
            if (this->depths[i] > this->depths[i - 1])
            {
                sol++;
            }
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;
        int current = this->depths[0] + this->depths[1] + this->depths[2];

        for (int i = 0; i + 2 < this->depths.size(); i++)
        {
            if (this->depths[i] + this->depths[i + 1] + this->depths[i + 2] > current)
            {
                ++sol;
            }
            current = this->depths[i] + this->depths[i + 1] + this->depths[i + 2];
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