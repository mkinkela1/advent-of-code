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

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<string> lines;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->lines.push_back(line);
        }
    }

    auto rotateCloclwise(vector<string> &grid) -> void
    {
        vector<string> rotatedGrid;
        for (int i = 0; i < grid[0].size(); i++)
        {
            string row = "";
            for (int j = grid.size() - 1; j >= 0; j--)
            {
                row += grid[j][i];
            }
            rotatedGrid.push_back(row);
        }

        grid = rotatedGrid;
    }

    auto moveToNorth(vector<string> &grid) -> void
    {
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                if (grid[i][j] == 'O')
                {
                    int k = i - 1;
                    while (k >= 0 && grid[k][j] == '.')
                    {
                        swap(grid[k][j], grid[k + 1][j]);
                        --k;
                    }
                }
            }
        }
    }

    auto calculate(vector<string> grid) -> int
    {
        int sol = 0;

        reverse(grid.begin(), grid.end());

        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); ++j)
            {
                if (grid[i][j] == 'O')
                {
                    sol += i + 1;
                }
            }
        }

        return sol;
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

        vector<string> grid = this->lines;

        this->moveToNorth(grid);

        return this->calculate(grid);
    }
    auto part2() -> int
    {
        map<pair<vector<string>, vector<string>>, int> cycle;
        vector<int> solutions;

        vector<string> grid = this->lines;

        int cnt = 1;
        for (;; ++cnt)
        {
            vector<string> prev_grid = grid;
            for (int i = 0; i < 4; ++i)
            {
                this->moveToNorth(grid);
                this->rotateCloclwise(grid);
            }

            int tmp = cycle[{prev_grid, grid}];

            if (tmp == 2)
                break;

            solutions.push_back(this->calculate(grid));

            cycle[{prev_grid, grid}]++;
        }

        int offset = 0, cycle_len = 0;
        for (auto x : cycle)
        {
            if (x.second == 2)
                ++cycle_len;
            else if (x.second == 1)
                ++offset;
        }

        // <112433, 112456>
        return solutions[(1000000000 - 1 - offset) % cycle_len + offset];
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