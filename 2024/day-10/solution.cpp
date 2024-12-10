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
    vector<string> grid;
    vector<pair<int, int>> directions = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
        }
    }

    int trails(int r, int c)
    {
        int sol = 0;

        queue<pair<int, int>> q;
        map<pair<int, int>, bool> visited;
        q.push({r, c});

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            if (this->grid[r][c] == '9')
            {
                ++sol;
            }

            for (auto [dr, dc] : this->directions)
            {
                int nr = r + dr;
                int nc = c + dc;

                if (nr < 0 || nr >= this->grid.size() || nc < 0 || nc >= this->grid[nr].size())
                    continue;
                if (visited[{nr, nc}])
                    continue;

                if ((this->grid[nr][nc] - '0') - (this->grid[r][c] - '0') == 1)
                {
                    visited[{nr, nc}] = true;
                    q.push({nr, nc});
                }
            }
        }

        return sol;
    }

    int ratings(int r, int c)
    {
        int sol = 0;

        queue<pair<int, int>> q;
        q.push({r, c});

        while (!q.empty())
        {
            auto [r, c] = q.front();
            q.pop();

            if (this->grid[r][c] == '9')
            {
                ++sol;
            }

            for (auto [dr, dc] : this->directions)
            {
                int nr = r + dr;
                int nc = c + dc;

                if (nr < 0 || nr >= this->grid.size() || nc < 0 || nc >= this->grid[nr].size())
                    continue;

                if ((this->grid[nr][nc] - '0') - (this->grid[r][c] - '0') == 1)
                {
                    q.push({nr, nc});
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

        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                if (this->grid[r][c] == '0')
                {
                    sol += this->trails(r, c);
                }
            }
        }

        return sol;
    }
    auto part2() -> int
    {
        int sol = 0;

        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                if (this->grid[r][c] == '0')
                {
                    sol += this->ratings(r, c);
                }
            }
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