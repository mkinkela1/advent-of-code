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
    vector<string> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->data.push_back(line);
        }
    }

    auto slope(int dx = 1, int dy = 1) -> long long
    {
        int x = 0;
        long long trees = 0LL;
        for (int y = 0; y < this->data.size(); y += dy)
        {
            if (this->data[y][x] == '#')
            {
                trees++;
            }
            x = (x + dx) % this->data[y].size();
        }
        return trees;
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
        return this->slope(3, 1);
    }
    auto part2() -> long long
    {
        return this->slope(1, 1) * this->slope(3, 1) * this->slope(5, 1) * this->slope(7, 1) * this->slope(1, 2);
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