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
    vector<vector<string>> data;

    void parse()
    {
        string line;
        vector<string> temp;
        while (getline(this->fin, line))
        {
            if (line.empty())
            {
                this->data.push_back(temp);
                temp.clear();
                continue;
            }
            else
                temp.push_back(line);
        }
        this->data.push_back(temp);
    }

    int check(vector<int> key, vector<int> lock, int h)
    {
        for (int i = 0; i < key.size(); i++)
            if (key[i] + lock[i] >= h - 1)
                return false;

        return true;
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
        vector<vector<int>> keys, locks;
        int h = this->data[0].size();

        for (auto grid : this->data)
        {
            vector<int> temp;
            for (int c = 0; c < grid[0].size(); c++)
            {
                int cnt = 0;
                while (cnt < grid.size() && grid[cnt][c] == grid[0][0])
                    cnt++;

                if (grid[0][0] == '#')
                    temp.push_back(cnt - 1);
                else
                    temp.push_back(grid.size() - cnt - 1);
            }

            if (grid[0][0] == '#')
                locks.push_back(temp);
            else
                keys.push_back(temp);
        }

        int sol = 0;

        for (auto key : keys)
            for (auto lock : locks)
                sol += check(key, lock, h);

        return sol;
    }

    auto part2() -> string { return "Merry Christmas!"; }
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