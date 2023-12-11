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
#include <algorithm>
#include <cmath>

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<string> input;
    vector<vector<bool>> highCost;
    vector<pair<int, int>> stars;

    void parse()
    {
        string line;
        int idx = 0;
        while (getline(this->fin, line))
        {
            this->input.push_back(line);
            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == '#')
                {
                    this->stars.push_back(make_pair(idx, j));
                }
            }
            ++idx;
        }

        this->highCost = vector<vector<bool>>(this->input.size(), vector<bool>(this->input[0].size(), false));

        for (int i = 0; i < this->input.size(); i++)
        {
            bool empty = true;
            for (int j = 0; j < this->input[i].size(); j++)
            {
                if (this->input[i][j] == '#')
                {
                    empty = false;
                    break;
                }
            }

            if (empty)
            {
                for (int j = 0; j < this->input[i].size(); j++)
                {
                    this->highCost[i][j] = true;
                }
            }
        }

        for (int i = 0; i < this->input[0].size(); i++)
        {
            bool empty = true;
            for (int j = 0; j < this->input.size(); j++)
            {
                if (this->input[j][i] == '#')
                {
                    empty = false;
                    break;
                }
            }

            if (empty)
            {
                for (int j = 0; j < this->input.size(); j++)
                {
                    this->highCost[j][i] = true;
                }
            }
        }
    }

    auto distance(pair<int, int> start, pair<int, int> end, long long mult) -> long long
    {

        long long costVertical = 0;
        long long costHorizontal = 0;

        for (int i = min(start.first, end.first) + 1; i <= max(start.first, end.first); i++)
        {
            if (this->highCost[i][start.second])
            {
                costHorizontal += mult;
            }
            else
            {
                costHorizontal += 1;
            }
        }

        for (int i = min(start.second, end.second) + 1; i <= max(start.second, end.second); i++)
        {
            if (this->highCost[start.first][i])
            {
                costVertical += mult;
            }
            else
            {
                costVertical += 1;
            }
        }

        return costVertical + costHorizontal;
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
        long long result = 0;
        for (int i = 0; i < this->stars.size(); i++)
            for (int j = i + 1; j < this->stars.size(); j++)
                result += this->distance(this->stars[i], this->stars[j], 2);
        return result;
    }
    auto part2() -> long long
    {
        long long result = 0;
        for (int i = 0; i < this->stars.size(); i++)
            for (int j = i + 1; j < this->stars.size(); j++)
                result += this->distance(this->stars[i], this->stars[j], 1000000);
        return result;
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