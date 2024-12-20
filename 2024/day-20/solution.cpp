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
#include <cmath>

using namespace std;

class Solution
{
private:
    fstream fin;
    vector<string> grid;
    pair<int, int> start;
    pair<int, int> end;
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void parse()
    {
        string line;
        int r = 0;
        while (getline(this->fin, line))
        {
            this->grid.push_back(line);
            for (int c = 0; c < line.size(); c++)
            {
                if (line[c] == 'S')
                {
                    this->start = {r, c};
                }
                else if (line[c] == 'E')
                {
                    this->end = {r, c};
                }
            }
            r++;
        }
    }

    vector<vector<int>> bfs(vector<string> grid, pair<int, int> start = {-1, -1}, pair<int, int> end = {-1, -1})
    {
        vector<vector<int>> visited(grid.size() + 1, vector<int>(grid[0].size() + 1, 0));
        vector<vector<int>> dist(grid.size() + 1, vector<int>(grid[0].size() + 1, -1));

        queue<pair<pair<int, int>, int>> q;
        q.push({start, 0});
        visited[start.first][start.second] = 1;
        dist[start.first][start.second] = 0;

        while (!q.empty())
        {
            auto [curr, d] = q.front();
            q.pop();

            if (curr == end)
                break;

            for (auto dir : this->directions)
            {
                int x = curr.first + dir.first;
                int y = curr.second + dir.second;

                if (x < 0 || x > grid.size() || y < 0 || y > grid[0].size() || visited[x][y] || grid[x][y] == '#')
                    continue;

                visited[x][y] = 1;
                dist[x][y] = d + 1;
                q.push({{x, y}, d + 1});
            }
        }

        return dist;
    }

    int manhattan(pair<int, int> a, pair<int, int> b)
    {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    int solve(int minSteps, int saved)
    {
        int sol = 0;

        int n = this->grid.size();

        vector<vector<int>> distFromStart = this->bfs(this->grid, this->start, this->end);
        vector<vector<int>> distFromEnd = this->bfs(this->grid, this->end, this->start);

        int def = distFromStart[this->end.first][this->end.second];

        map<pair<pair<int, int>, pair<int, int>>, bool> checked;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (this->grid[i][j] == '#')
                    continue;

                for (int k = max(0, i - minSteps); k <= min(n, i + minSteps); k++)
                {
                    for (int l = max(0, j - minSteps); l <= min(n, j + minSteps); l++)
                    {
                        if (k < 0 || k >= n || l < 0 || l >= n)
                            continue;

                        if (this->grid[k][l] == '#')
                            continue;

                        if (this->manhattan({i, j}, {k, l}) > minSteps)
                            continue;

                        if (distFromStart[i][j] < 0 || distFromEnd[k][l] < 0)
                            continue;

                        int cheat = distFromStart[i][j] + distFromEnd[k][l] + this->manhattan({i, j}, {k, l});
                        if (def - cheat >= saved)
                        {
                            sol++;
                        }
                    }
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

    auto part1(int minSteps, int saved) -> int
    {
        return this->solve(minSteps, saved);
    }
    auto part2(int minSteps, int saved) -> int
    {
        return this->solve(minSteps, saved);
    }
};

auto main() -> int
{

    Solution aoc = Solution("input.txt");
    Solution test1 = Solution("test1.txt");
    Solution test2 = Solution("test2.txt");

    cout << "Part 1 test: " << test1.part1(2, 2) << endl;
    cout << "Part 1: " << aoc.part1(2, 100) << endl;
    cout << "--------------------------" << endl;
    cout << "Part 2 test: " << test2.part2(20, 2) << endl;
    cout << "Part 2: " << aoc.part2(20, 100) << endl;

    return 0;
}