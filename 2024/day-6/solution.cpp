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
    pair<int, int> start;
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    void parse()
    {
        string line;
        for (int i = 0; getline(this->fin, line); i++)
        {
            this->grid.push_back(line);

            for (int j = 0; j < line.size(); j++)
            {
                if (line[j] == '^')
                {
                    this->start = {i, j};
                }
            }
        }
    }

    bool isCycle(vector<string> grid)
    {
        int direction = 0;
        map<tuple<int, int, int>, bool> visited;
        pair<int, int> current = this->start;

        while (current.first >= 0 && current.first < grid.size() && current.second >= 0 && current.second < grid[0].size())
        {
            if (visited[{current.first, current.second, direction}])
            {
                return true;
            }

            visited[{current.first, current.second, direction}] = true;

            if (
                current.first + this->directions[direction].first < 0 ||
                current.first + this->directions[direction].first >= grid.size() ||
                current.second + this->directions[direction].second < 0 ||
                current.second + this->directions[direction].second >= grid[0].size())
            {
                return false;
            }

            if (grid[current.first + this->directions[direction].first][current.second + this->directions[direction].second] == '#')
            {
                direction++;
                direction %= 4;
            }
            else
            {
                current.first += this->directions[direction].first;
                current.second += this->directions[direction].second;
            }
        }

        return false;
    }

    map<pair<int, int>, bool> run(vector<string> grid, pair<int, int> start)
    {
        pair<int, int> current = this->start;
        map<pair<int, int>, bool> visited;
        int direction = 0;

        while (current.first >= 0 && current.first < this->grid.size() && current.second >= 0 && current.second < this->grid[0].size())
        {
            visited[current] = true;
            if (
                current.first + this->directions[direction].first < 0 ||
                current.first + this->directions[direction].first >= this->grid.size() ||
                current.second + this->directions[direction].second < 0 ||
                current.second + this->directions[direction].second >= this->grid[0].size())
            {
                break;
            }

            if (this->grid[current.first + this->directions[direction].first][current.second + this->directions[direction].second] == '#')
            {
                direction++;
                direction %= 4;
            }

            current.first += this->directions[direction].first;
            current.second += this->directions[direction].second;
        }

        return visited;
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

        map<pair<int, int>, bool> visited = this->run(this->grid, this->start);

        for (int i = 0; i < this->grid.size(); i++)
        {
            for (int j = 0; j < this->grid[0].size(); j++)
            {
                if ((this->grid[i][j] == '.' || this->grid[i][j] == '^') && !visited[{i, j}] == 0)
                {
                    ++sol;
                }
            }
        }

        return sol;
    };

    auto part2() -> int
    {
        int sol = 0;

        map<pair<int, int>, bool> visited = this->run(this->grid, this->start);

        for (int i = 0; i < this->grid.size(); i++)
        {
            for (int j = 0; j < this->grid[0].size(); j++)
            {
                if (this->grid[i][j] == '^' || this->grid[i][j] == '#')
                    continue;

                if (visited[{i, j}] == 0)
                    continue;

                vector<string> grid = this->grid;
                grid[i][j] = '#';

                sol += this->isCycle(grid);
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
