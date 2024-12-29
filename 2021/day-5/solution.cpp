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
    vector<tuple<int, int, int, int>> data;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            int x1, y1, x2, y2;
            sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
            this->data.push_back({x1, y1, x2, y2});
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
        map<pair<int, int>, int> freq;

        for (auto [x1, y1, x2, y2] : this->data)
        {
            if (x1 == x2)
                for (int i = min(y1, y2); i <= max(y1, y2); i++)
                    freq[{x1, i}]++;
            else if (y1 == y2)
                for (int i = min(x1, x2); i <= max(x1, x2); i++)
                    freq[{i, y1}]++;
        }

        for (auto [_, f] : freq)
            if (f > 1)
                sol++;

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;
        map<pair<int, int>, int> freq;

        for (auto [x1, y1, x2, y2] : this->data)
        {
            if (x1 == x2)
                for (int i = min(y1, y2); i <= max(y1, y2); i++)
                    freq[{x1, i}]++;
            else if (y1 == y2)
                for (int i = min(x1, x2); i <= max(x1, x2); i++)
                    freq[{i, y1}]++;
            else
            {
                int dx = x1 > x2 ? -1 : 1;
                int dy = y1 > y2 ? -1 : 1;

                for (int i = x1, j = y1; i != x2; i += dx, j += dy)
                    ++freq[{i, j}];

                ++freq[{x2, y2}];
            }
        }

        for (auto [_, f] : freq)
            if (f > 1)
                sol++;

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