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
    map<pair<int, int>, bool> visited;

    void parse()
    {
        string line;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
        }
    }

    void dfs(int r, int c, map<pair<int, int>, int> &area, int a, char ch)
    {
        if (r < 0 || r >= this->grid.size() || c < 0 || c >= this->grid[r].size())
            return;
        if (this->visited[{r, c}])
            return;

        if (this->grid[r][c] != ch)
            return;
        this->visited[{r, c}] = true;
        area[{r, c}] = a;

        dfs(r + 1, c, area, a, ch);
        dfs(r - 1, c, area, a, ch);
        dfs(r, c + 1, area, a, ch);
        dfs(r, c - 1, area, a, ch);
    }

    int countCorners(int r, int c, map<pair<int, int>, int> &area)
    {
        int sol = 0;

        int curr = area[{r, c}];

        int top = area[{r - 1, c}];
        int bottom = area[{r + 1, c}];
        int left = area[{r, c - 1}];
        int right = area[{r, c + 1}];

        int top_left = area[{r - 1, c - 1}];
        int top_right = area[{r - 1, c + 1}];
        int bottom_left = area[{r + 1, c - 1}];
        int bottom_right = area[{r + 1, c + 1}];

        if (curr != top && curr != left)
            ++sol;
        if (curr != top && curr != right)
            ++sol;
        if (curr != bottom && curr != left)
            ++sol;
        if (curr != bottom && curr != right)
            ++sol;

        if (curr == right && curr == bottom && curr != bottom_right)
            ++sol;
        if (curr == left && curr == bottom && curr != bottom_left)
            ++sol;
        if (curr == right && curr == top && curr != top_right)
            ++sol;
        if (curr == left && curr == top && curr != top_left)
            ++sol;

        return sol;
    }

public:
    Solution(string fileName)
    {
        this->fin.open(fileName, ios::in);
        this->parse();
        this->fin.close();
    }

    auto part1() -> uint64_t
    {
        uint64_t sol = 0;
        map<pair<int, int>, int> area;
        map<int, pair<int, int>> sizes;

        int a = 1;
        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                if (!this->visited[{r, c}])
                    dfs(r, c, area, a++, this->grid[r][c]);
            }
        }

        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                sizes[area[{r, c}]].first++;

                for (int j = 0; j < 4; ++j)
                {
                    int nr = r + "0121"[j] - '1';
                    int nc = c + "1210"[j] - '1';

                    if (nr < 0 || nr >= this->grid.size() || nc < 0 || nc >= this->grid[r].size())
                        sizes[area[{r, c}]].second++;
                    else if (area[{nr, nc}] != area[{r, c}])
                        sizes[area[{r, c}]].second++;
                }
            }
        }

        for (auto [k, v] : sizes)
            sol += v.first * v.second;

        return sol;
    }
    auto part2() -> uint64_t
    {

        this->visited.clear();

        uint64_t sol = 0;
        map<pair<int, int>, int> area;
        map<int, pair<int, int>> sizes;

        int a = 1;
        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                if (!this->visited[{r, c}])
                    dfs(r, c, area, a++, this->grid[r][c]);
            }
        }

        for (int r = 0; r < this->grid.size(); r++)
        {
            for (int c = 0; c < this->grid[r].size(); c++)
            {
                sizes[area[{r, c}]].first++;
                sizes[area[{r, c}]].second += this->countCorners(r, c, area);
            }
        }

        for (auto [k, v] : sizes)
            sol += v.first * v.second;

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